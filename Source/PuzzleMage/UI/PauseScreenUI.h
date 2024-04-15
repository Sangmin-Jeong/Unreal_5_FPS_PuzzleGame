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

	UFUNCTION()
	bool IsAtPauseMenu();

	UFUNCTION()
	void ShowPauseMenuPanel();

private:
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* PauseMenuPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* OptionsPanel;

	UPROPERTY(meta = (BindWidget))
	class UOptionsUI* OptionsUI;

	UFUNCTION()
	void BindOnClickedEvents();

	UFUNCTION()
	void OnOptionsButtonClicked();

	UFUNCTION()
	void OnRestartButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();
	
	UFUNCTION()
	void OnQuitButtonClicked();
};
