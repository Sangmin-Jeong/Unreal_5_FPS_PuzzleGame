// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UGameOverScreenUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* PlayAgainButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* QuitButton;

	UFUNCTION()
	void BindOnClickedEvents();

	UFUNCTION()
	void OnQuitButtonClicked();
};
