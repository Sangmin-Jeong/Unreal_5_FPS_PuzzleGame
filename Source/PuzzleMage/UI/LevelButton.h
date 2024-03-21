// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelButton.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API ULevelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetButtonText(const FText& Text);
	class UButton* GetButton() const;
	void SetButtonOnClick();
	
	void SetIsFocused(bool bValue);

	void SetLevelDataAsset(class ULevelDataAsset* DataAsset);

private:
	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText ButtonTextValue;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	class ULevelDataAsset* LevelDataAsset;
	
	UPROPERTY(EditAnywhere, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle DefaultStyle;

	UPROPERTY(EditAnywhere, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle FocusedStyle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FocusSound;

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void AnimateButtonOutline();

	UFUNCTION()
	void SetLockedButton();

	UFUNCTION()
	void SetUnlockedButton();
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	class UImage* LevelIcon;

	UPROPERTY(meta = (BindWidget))
	class UImage* LockedBackground;

	UPROPERTY()
	bool bIsFocused;

	void PlaySound();

	FLinearColor CurrentOutlineColor;
};
