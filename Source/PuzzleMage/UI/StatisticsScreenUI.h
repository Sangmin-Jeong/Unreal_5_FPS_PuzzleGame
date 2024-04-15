// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatisticsScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UStatisticsScreenUI : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TotalDoorsOpenedText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TotalLevelsUnlockedText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TotalJumpText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TotalDeathText;
};
