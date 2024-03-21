// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AutoSaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UAutoSaveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	float GetAutoSaveTime() const { return AutoSaveTime; }

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* AutoSaveImage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	float AutoSaveTime = 2.0f;
};
