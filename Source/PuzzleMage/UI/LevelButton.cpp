// Puzzle Mage by Arctic Moose Games


#include "LevelButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/Data/LevelDataAsset.h"

void ULevelButton::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonText->SetText(ButtonTextValue);

	bIsFocused = true;

	DefaultStyle = Button->GetStyle();
}

void ULevelButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonTextValue.IsEmptyOrWhitespace())
	{
		ButtonTextValue = FText::FromString("Button");
	}
	else
	{
		ButtonText->SetText(ButtonTextValue);
	}
}

void ULevelButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
	// If the button is focused, set the style to the focused style
	APlayerController* PlayerController = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
	if (!PlayerController)
	{
		return;
	}
	
	if (Button->HasUserFocus(PlayerController) && !bIsFocused)
	{
		Button->SetStyle(FocusedStyle);
		bIsFocused = true;

		CurrentOutlineColor = FocusedStyle.Normal.OutlineSettings.Color.GetSpecifiedColor();

		PlaySound();
	}
	else if (!Button->HasUserFocus(PlayerController) && bIsFocused)
	{
		Button->SetStyle(DefaultStyle);
		bIsFocused = false;
	}

	if (Button->HasUserFocus(PlayerController))
	{
		AnimateButtonOutline();
	}
}

void ULevelButton::SetButtonText(const FText& Text)
{
	ButtonTextValue = Text;
}

UButton* ULevelButton::GetButton() const
{
	return Button;
}

void ULevelButton::SetButtonOnClick()
{
	Button->OnClicked.AddDynamic(this, &ULevelButton::OnButtonClicked);
}

void ULevelButton::SetIsFocused(bool bValue)
{
	bIsFocused = bValue;
}

void ULevelButton::SetLevelDataAsset(ULevelDataAsset* DataAsset)
{
	LevelDataAsset = DataAsset;

	SetButtonText(FText::FromString(LevelDataAsset->GetLevelName()));

	if (LevelDataAsset->GetIsLocked())
	{
		SetLockedButton();
	}
	else
	{
		SetUnlockedButton();
	}

	SetButtonOnClick();
}

void ULevelButton::OnButtonClicked()
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(World, LevelDataAsset, true);
}

void ULevelButton::AnimateButtonOutline()
{
	// Change the alpha of the outline color between 0.4 and 1
	const float Alpha = FMath::Lerp(0.4f, 1.0f, FMath::Abs(FMath::Sin(GetWorld()->GetTimeSeconds() * 2.0f)));
	CurrentOutlineColor.A = Alpha;
	FButtonStyle NewStyle = Button->GetStyle();
	NewStyle.Normal.OutlineSettings.Color = CurrentOutlineColor;
	Button->SetStyle(NewStyle);
}

void ULevelButton::SetLockedButton()
{
	Button->SetIsEnabled(false);
	Button->SetVisibility(ESlateVisibility::Hidden);

	// Set level icon to the locked icon
	FSlateBrush Brush = LevelIcon->GetBrush();
	Brush.SetResourceObject(LevelDataAsset->GetLockedLevelIcon());
	LevelIcon->SetBrush(Brush);

	ButtonText->SetOpacity(0.5f);
	LockedBackground->SetRenderOpacity(1.0f);
}

void ULevelButton::SetUnlockedButton()
{
	Button->SetIsEnabled(true);
	Button->SetVisibility(ESlateVisibility::Visible);

	// Set level icon to the unlocked icon
	FSlateBrush Brush = LevelIcon->GetBrush();
	Brush.SetResourceObject(LevelDataAsset->GetLevelIcon());
	LevelIcon->SetBrush(Brush);
	LockedBackground->SetRenderOpacity(0.0f);
}

void ULevelButton::PlaySound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), FocusSound);
}
