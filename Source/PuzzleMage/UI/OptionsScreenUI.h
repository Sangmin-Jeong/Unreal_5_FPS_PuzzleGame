// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuzzleMage/MyGameInstance.h"
#include "OptionsScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UOptionsScreenUI : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UGameUserSettings* UserSettings; // TODO: Not implemented yet

	UPROPERTY(meta = (BindWidget))
	class UOptionsUI* OptionsUI;
};
