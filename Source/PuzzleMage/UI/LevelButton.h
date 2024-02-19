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

private:
	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText ButtonTextValue;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FName LevelName;
	
	UPROPERTY(EditAnywhere, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle DefaultStyle;

	UPROPERTY(EditAnywhere, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle FocusedStyle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FocusSound;

	UFUNCTION()
	void OnButtonClicked();
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

	UPROPERTY()
	bool bIsFocused;

	void PlaySound();
};
