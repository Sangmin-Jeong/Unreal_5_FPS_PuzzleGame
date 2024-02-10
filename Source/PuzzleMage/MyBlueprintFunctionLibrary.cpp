// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "AchievementSubSystem.h"
#include "AsyncLoadingScreenLibrary.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

int32 UMyBlueprintFunctionLibrary::GetLastMaxPlayerIndex()
{
	return UMyGameInstance::MAX_CONTROLLERS - 1;
}

void UMyBlueprintFunctionLibrary::SetActiveControllerId(const UObject* WorldContextObject, int32 ControllerId)
{
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		GameInstanceRef->SetActiveControllerId(ControllerId);
	}
}

int32 UMyBlueprintFunctionLibrary::GetActiveControllerId(const UObject* WorldContextObject)
{
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		return GameInstanceRef->GetActiveControllerId();
	}

	return -1;
}

void UMyBlueprintFunctionLibrary::RemoveAllPlayers(const UObject* WorldContextObject)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerController::StaticClass(), FoundActors);

	for (AActor* Actor: FoundActors)
	{
		APlayerController* PC = Cast<APlayerController>(Actor);
		if (PC)
		{
			UGameplayStatics::RemovePlayer(PC, true);
		}
	}
}

APlayerController* UMyBlueprintFunctionLibrary::GetActivePlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerControllerFromID(WorldContextObject, GetActiveControllerId(WorldContextObject));
}

ACharacter* UMyBlueprintFunctionLibrary::GetActivePlayerCharacter(const UObject* WorldContextObject)
{
	return GetActivePlayerController(WorldContextObject)->GetCharacter();
}

void UMyBlueprintFunctionLibrary::SetupActiveControllerId(const UObject* WorldContextObject, FKey Key,
	EStatusReturnType& Status)
{
	if (Key.IsGamepadKey())
	{
		for (int32 ControllerIndex = 0; ControllerIndex < UMyGameInstance::MAX_CONTROLLERS; ++ControllerIndex)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, ControllerIndex);
			if (PC->WasInputKeyJustPressed(Key))
			{
				SetActiveControllerId(WorldContextObject, ControllerIndex);
				RemoveAllPlayers(WorldContextObject);
				Status = EStatusReturnType::Success;
				return;
			}
		}
	}

	Status = EStatusReturnType::Fail;
}

void UMyBlueprintFunctionLibrary::UnlockAchievement(const UObject* WorldContextObject, FName AchievementName)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UAchievementSubSystem* AchievementSubsystem = GameInstance->GetSubsystem<UAchievementSubSystem>();

	if (AchievementSubsystem->AchievementExists(AchievementName))
	{
		AchievementSubsystem->Unlock(AchievementName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Achievement does not exist!"));
	}
}

void UMyBlueprintFunctionLibrary::AddAchievementProgress(const UObject* WorldContextObject, FName AchievementName,
	float Progress)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);

	if (UAchievementSubSystem* AchievementSubsystem = GameInstance->GetSubsystem<UAchievementSubSystem>())
	{
		AchievementSubsystem->AddAchievementProgress(AchievementName, Progress);
	}
}

void UMyBlueprintFunctionLibrary::SetAchievementProgress(const UObject* WorldContextObject, FName AchievementName,
	float Progress)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);

	if (UAchievementSubSystem* AchievementSubsystem = GameInstance->GetSubsystem<UAchievementSubSystem>())
	{
		AchievementSubsystem->SetAchievementProgress(AchievementName, Progress);
	}
}

void UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(const UObject* WorldContextObject, FName MapName, bool EnableLoadingScreen ,const float Delay)
{
	UWorld* World = const_cast<UWorld*>(WorldContextObject->GetWorld());

	UAsyncLoadingScreenLibrary::SetEnableLoadingScreen(EnableLoadingScreen);
	
	// Add a delay to allow the button click sound to play
	FTimerHandle TimerHandle;

	World->GetTimerManager().SetTimer(TimerHandle, [World, MapName]()
	{
		RemoveAllPlayers(World);
		UGameplayStatics::OpenLevel(World, MapName);
	}, Delay, false);
}

FName UMyBlueprintFunctionLibrary::GetCurrentMapName(const UObject* WorldContextObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	
	return FName(GameInstance->GetWorld()->GetMapName());
}

void UMyBlueprintFunctionLibrary::QuitGame(const UObject* WorldContextObject, bool bIgnorePlatformRestrictions)
{
	APlayerController* PlayerController = GetActivePlayerController(WorldContextObject);
	
	UKismetSystemLibrary::QuitGame(WorldContextObject, PlayerController, EQuitPreference::Quit, bIgnorePlatformRestrictions);
}

