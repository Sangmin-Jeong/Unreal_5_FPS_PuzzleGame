// Puzzle Mage by Arctic Moose Games


#include "FocusableSlider.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"

void UFocusableSlider::NativeConstruct()
{
	Super::NativeConstruct();
	
	bIsFocused = true;

	DefaultStyle = Slider->GetWidgetStyle();
}

void UFocusableSlider::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (LabelText && !LabelTextValue.IsEmptyOrWhitespace())
	{
		LabelText->SetText(LabelTextValue);
	}
}

void UFocusableSlider::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// If the button is focused, set the style to the focused style
	APlayerController* PlayerController = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
	if (!PlayerController)
	{
		return;
	}
	
	if (Slider->HasUserFocus(PlayerController) && !bIsFocused)
	{
		Slider->SetWidgetStyle(FocusedStyle);
		bIsFocused = true;

		CurrentSliderColor = FocusedStyle.NormalBarImage.TintColor.GetSpecifiedColor();

		PlaySound();
	}
	else if (!Slider->HasUserFocus(PlayerController) && bIsFocused)
	{
		Slider->SetWidgetStyle(DefaultStyle);
		bIsFocused = false;
	}

	if (Slider->HasUserFocus(PlayerController))
	{
		AnimateSlider();
	}
}

USlider* UFocusableSlider::GetSlider() const
{
	return Slider;
}

void UFocusableSlider::SetPlayFirstFocusSound(bool bValue)
{
	bPlayFirstFocusSound = bValue;
}

void UFocusableSlider::SetIsFocused(bool bValue)
{
	bIsFocused = bValue;
}

void UFocusableSlider::PlaySound()
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

void UFocusableSlider::AnimateSlider()
{
	const float Alpha = FMath::Lerp(0.4f, 1.0f, FMath::Abs(FMath::Sin(GetWorld()->GetTimeSeconds() * 2.0f)));
	CurrentSliderColor.A = Alpha;
	FSliderStyle NewStyle = Slider->GetWidgetStyle();
	NewStyle.NormalBarImage.TintColor = CurrentSliderColor;
	Slider->SetWidgetStyle(NewStyle);
}
