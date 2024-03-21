// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UCustomSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UCustomSaveGame();
	
	UPROPERTY()
	class UGameData* GameData;
	
	UPROPERTY()
	int32 UserIndex;

	UPROPERTY()
	FString SaveSlotName;
};
