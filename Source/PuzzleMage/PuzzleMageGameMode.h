// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "PuzzleMageGameMode.generated.h"

UCLASS(minimalapi)
class APuzzleMageGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	APuzzleMageGameMode();

	virtual void BeginPlay() override;
};



