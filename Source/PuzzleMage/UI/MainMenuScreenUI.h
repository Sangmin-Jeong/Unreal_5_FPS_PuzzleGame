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
	class UCustomButton* ContinueButton;
	
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* SelectLevelButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* AchievementsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* StatisticsButton;

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
	void OnContinueButtonClicked();

	UFUNCTION()
	void OnNewGameButtonClicked();
	
	UFUNCTION()
	void OnSelectLevelButtonClicked();

	UFUNCTION()
	void OnCreditsButtonClicked();

	UFUNCTION()
	void OnOptionsButtonClicked();
	
	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnControlsButtonClicked();

	UFUNCTION()
	void OnAchievementsButtonClicked();

	UFUNCTION()
	void OnStatisticsButtonClicked();
};
