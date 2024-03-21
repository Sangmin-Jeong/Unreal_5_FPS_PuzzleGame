// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomButton.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UCustomButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetButtonText(const FText& Text);

	UFUNCTION(BlueprintCallable)
	UButton* GetButton() const;

	void SetPlayFirstFocusSound(bool bValue);

	UFUNCTION(BlueprintCallable)
	void SetIsFocused(bool bValue);

private:
	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText ButtonTextValue;
	
	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool bPlayFirstFocusSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle DefaultStyle;

	UPROPERTY(EditDefaultsOnly, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle FocusedStyle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FocusSound;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	class UImage* SelectBarImage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* SelectBarFadeInOutAnimation;

	UPROPERTY()
	bool bIsFocused;

	void PlaySound();
};
