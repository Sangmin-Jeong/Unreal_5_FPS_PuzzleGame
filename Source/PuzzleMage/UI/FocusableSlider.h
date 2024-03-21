// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FocusableSlider.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UFocusableSlider : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	class USlider* GetSlider() const;

	void SetPlayFirstFocusSound(bool bValue);
	void SetIsFocused(bool bValue);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FSliderStyle DefaultStyle;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FSliderStyle FocusedStyle;

	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText LabelTextValue;

	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FocusSound;

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	bool bPlayFirstFocusSound;
private:
	UPROPERTY(meta = (BindWidget))
	class USlider* Slider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LabelText;
	
	UPROPERTY()
	bool bIsFocused;

	UPROPERTY()
	FLinearColor CurrentSliderColor;

private:
	void PlaySound();

	void AnimateSlider();
};
