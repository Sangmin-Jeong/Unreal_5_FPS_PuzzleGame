// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UPauseScreenUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RunningTimeText;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* QuitButton;

	UFUNCTION()
	void BindOnClickedEvents();

	UFUNCTION()
	void OnRestartButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();
	
	UFUNCTION()
	void OnQuitButtonClicked();
};
