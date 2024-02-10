// Puzzle Mage by Arctic Moose Games


#include "CustomButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"

void UCustomButton::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocused = true;

	DefaultStyle = Button->GetStyle();
	PlayAnimation(SelectBarFadeInOutAnimation, 0.0f, 0);
}

void UCustomButton::NativePreConstruct()
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

void UCustomButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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
		SelectBarImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(SelectBarFadeInOutAnimation, 0.0f, 0);
		bIsFocused = true;

		PlaySound();
	}
	else if (!Button->HasUserFocus(PlayerController) && bIsFocused)
	{
		Button->SetStyle(DefaultStyle);
		SelectBarImage->SetVisibility(ESlateVisibility::Hidden);
		StopAnimation(SelectBarFadeInOutAnimation);
		bIsFocused = false;
	}
}

void UCustomButton::PlaySound()
{
	if (FocusSound && bPlayFirstFocusSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FocusSound);
	}
	else
	{
		bPlayFirstFocusSound = true;
	}
}

void UCustomButton::SetButtonText(const FText& Text)
{
	ButtonTextValue = Text;
}

UButton* UCustomButton::GetButton() const
{
	return Button;
}

void UCustomButton::SetPlayFirstFocusSound(bool bValue)
{
	bPlayFirstFocusSound = bValue;
}

void UCustomButton::SetIsFocused(bool bValue)
{
	bIsFocused = bValue;
}
