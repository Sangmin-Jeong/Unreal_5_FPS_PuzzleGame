// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UMainMenuScreenUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* LoadGameButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* AchievementsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* ControlsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* OptionsButton;
	
	
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* QuitButton;

	UFUNCTION()
	void BindOnClickedEvents();

	UFUNCTION()
	void OnNewGameButtonClicked();

	UFUNCTION()
	void OnCreditsButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnControlsButtonClicked();
	
};
