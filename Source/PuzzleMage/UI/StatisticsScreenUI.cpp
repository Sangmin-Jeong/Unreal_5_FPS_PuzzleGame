// Puzzle Mage by Arctic Moose Games


#include "StatisticsScreenUI.h"

#include "Components/TextBlock.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/MyGameInstance.h"

void UStatisticsScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (const UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld()); GameInstance != nullptr)
	{
		if(const UGameStats* GameStats = GameInstance->GetGameData()->GetGameStats(); GameStats != nullptr)
		{
			TotalDoorsOpenedText->SetText(FText::FromString(FString::FromInt(GameStats->GetTotalDoorsOpened())));
			TotalLevelsUnlockedText->SetText(FText::FromString(FString::FromInt(GameStats->GetTotalLevelsUnlocked())));
			TotalJumpText->SetText(FText::FromString(FString::FromInt(GameStats->GetTotalJump())));
			TotalDeathText->SetText(FText::FromString(FString::FromInt(GameStats->GetTotalDeath())));
		}
	}
	else
	{
		TotalDoorsOpenedText->SetText(FText::FromString("0"));
		TotalLevelsUnlockedText->SetText(FText::FromString("0"));
		TotalJumpText->SetText(FText::FromString("0"));
		TotalDeathText->SetText(FText::FromString("0"));
	}
}
