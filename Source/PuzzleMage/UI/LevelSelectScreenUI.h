// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuzzleMage/Data/GameData.h"
#include "LevelSelectScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API ULevelSelectScreenUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Chapter1Button;

	UPROPERTY(meta = (BindWidget))
	class ULevelButton* Level1Button;

	UPROPERTY(meta = (BindWidget))
	class ULevelButton* Level2Button;

	UPROPERTY(meta = (BindWidget))
	class ULevelButton* Level3Button;

	UPROPERTY(meta = (BindWidget))
	class ULevelButton* Level4Button;

	UPROPERTY(meta = (BindWidget))
	class ULevelButton* Level5Button;

private:
	UFUNCTION()
	void BindOnClickedEvents();
};
