// Puzzle Mage by Arctic Moose Games


#include "LevelButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"

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

		PlaySound();
	}
	else if (!Button->HasUserFocus(PlayerController) && bIsFocused)
	{
		Button->SetStyle(DefaultStyle);
		bIsFocused = false;
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

void ULevelButton::OnButtonClicked()
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(World, LevelName, true);
}

void ULevelButton::PlaySound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), FocusSound);
}
