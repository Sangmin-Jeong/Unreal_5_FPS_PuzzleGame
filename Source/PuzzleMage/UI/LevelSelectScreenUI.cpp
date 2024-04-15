// Puzzle Mage by Arctic Moose Games


#include "LevelSelectScreenUI.h"

#include "LevelButton.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "PuzzleMage/BasePlayerController.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/Data/ChapterDataAsset.h"
#include "PuzzleMage/Data/UIDataAsset.h"


class UScrollBoxSlot;

void ULevelSelectScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	ChapterDataAssets = GameData->GetChapterDataAssets();

	if (ChapterDataAssets.Num() > 0)
	{
		CurrentChapterIndex = 0;
		UpdateChapterTitle();

		GenerateLevelButtons(CurrentChapterIndex);
	}

	if (ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetOwningPlayer()))
	{
		BasePlayerController->SetWidgetForInput(this);
	}

	if (UUIDataAsset* UIDataAsset = UMyBlueprintFunctionLibrary::GetUIDataAsset(GetWorld()))
	{
		TabLeftIcon->SetBrushFromTexture(UIDataAsset->GetIcon(EIconType::TabLeft));
		TabRightIcon->SetBrushFromTexture(UIDataAsset->GetIcon(EIconType::TabRight));
	}
}

void ULevelSelectScreenUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void ULevelSelectScreenUI::NativeDestruct()
{
	Super::NativeDestruct();

	if (ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetOwningPlayer()))
	{
		BasePlayerController->RemoveWidgetForInput();
	}
}

void ULevelSelectScreenUI::TabLeft()
{
	if (CurrentChapterIndex > 0)
	{
		CurrentChapterIndex--;

		UpdateChapterTitle();
		GenerateLevelButtons(CurrentChapterIndex);
	}
}

void ULevelSelectScreenUI::TabRight()
{
	if (CurrentChapterIndex < ChapterDataAssets.Num() - 1)
	{
		CurrentChapterIndex++;

		UpdateChapterTitle();
		GenerateLevelButtons(CurrentChapterIndex);
	}
}

void ULevelSelectScreenUI::GenerateLevelButtons(int ChapterIndex)
{
	LevelButtonsContainer->ClearChildren();
	
	TArray<ULevelDataAsset*> LevelDataAssets = ChapterDataAssets[ChapterIndex]->GetLevelDataAssets();

	for (int i = 0; i < LevelDataAssets.Num(); i++)
	{
		ULevelDataAsset* LevelDataAsset = LevelDataAssets[i];
		ULevelButton* LevelButton = CreateWidget<ULevelButton>(this, LevelButtonClass);
		LevelButton->SetLevelDataAsset(LevelDataAsset);
		UVerticalBoxSlot* ContainerSlot = Cast<UVerticalBoxSlot>(LevelButtonsContainer->AddChild(LevelButton));
		ContainerSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 10.f));
		ContainerSlot->SetSize(ESlateSizeRule::Fill);

		if (i == 0)
		{
			LevelButton->SetIsFocused(false);
			LevelButton->GetButton()->SetFocus();
		}
	}
}

void ULevelSelectScreenUI::UpdateChapterTitle()
{
	if (!ChapterDataAssets.IsValidIndex(CurrentChapterIndex)) return;
	
	ChapterTitle->SetText(FText::FromString(ChapterDataAssets[CurrentChapterIndex]->GetChapterName()));
}
