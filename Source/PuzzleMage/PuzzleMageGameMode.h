// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "PuzzleMageGameMode.generated.h"

DECLARE_DELEGATE(FOnFinalDoorOpenedSignature)

class ADoor;
class ADoorClass;

UCLASS(minimalapi)
class APuzzleMageGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	APuzzleMageGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	TArray<AActor*> MagicRuneActors;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	int NextMagicRuneIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,  meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	bool bIsAllMagicRuneActivated;

	UPROPERTY()
	TObjectPtr<ADoor> Door;

	UPROPERTY()
	TObjectPtr<ADoorClass> DoorClass;
	
	UFUNCTION()
	void OpenDoor();

	UFUNCTION(BlueprintCallable)
	void ExecuteFinalDoorDelegate();

	FOnFinalDoorOpenedSignature FinalDoorOpenedDelegate;

private:
	void InitializeMagicRune();



};



