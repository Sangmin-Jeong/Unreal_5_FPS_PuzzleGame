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
	virtual void NativeDestruct() override;
	
	void TabLeft();
	void TabRight();
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ChapterTitle;
	
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* LevelButtonsContainer;

	UPROPERTY(meta = (BindWidget))
	class UImage* TabLeftIcon;

	UPROPERTY(meta = (BindWidget))
	class UImage* TabRightIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ULevelButton> LevelButtonClass;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UGameData* GameData;

	TArray<class UChapterDataAsset*> ChapterDataAssets;

	int CurrentChapterIndex;

private:
	UFUNCTION()
	void GenerateLevelButtons(int ChapterIndex);

	UFUNCTION()
	void UpdateChapterTitle();
};
