// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UOptionsUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void SetFocusToWidget();

private:
	UPROPERTY(meta = (BindWidget))
	class UFocusableSlider* MasterVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class UFocusableSlider* MusicVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class UFocusableSlider* SFXVolumeSlider;

private:
	void InitializeSliders(const class UMyGameInstance* GameInstance);
	void SetInitialVolumes();
	
	UFUNCTION()
	void OmMasterVolumeChanged(float Value);

	UFUNCTION()
	void OnMusicVolumeChanged(float Value);

	UFUNCTION()
	void OnSFXVolumeChanged(float Value);
};
