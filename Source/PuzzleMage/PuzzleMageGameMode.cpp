// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleMageGameMode.h"

#include "GamePlayerController.h"
#include "MyGameInstance.h"
#include "PuzzleMageCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseHUD.h"
#include "UObject/ConstructorHelpers.h"

APuzzleMageGameMode::APuzzleMageGameMode()
	: Super()
{
	PlayerControllerClass = AGamePlayerController::StaticClass();
	DefaultPawnClass = APuzzleMageCharacter::StaticClass();
}

void APuzzleMageGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		if (GameInstanceRef->GetActiveControllerId() > -1)
		{
			AGamePlayerController* PC = Cast<AGamePlayerController>(UGameplayStatics::CreatePlayer(this, GameInstanceRef->GetActiveControllerId()));
			if (!PC) return;

			FInputModeGameAndUI InputMode;
			PC->SetInputMode(InputMode);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Controller ID is not set!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Game Instance is not set!"));
	}
}
