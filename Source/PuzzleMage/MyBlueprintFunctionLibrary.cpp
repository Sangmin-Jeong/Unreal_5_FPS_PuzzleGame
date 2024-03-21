// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "AchievementSubSystem.h"
#include "AsyncLoadingScreenLibrary.h"
#include "MyGameInstance.h"
#include "Data/CustomSaveGame.h"
#include "Data/LevelDataAsset.h"
#include "Kismet/GameplayStatics.h"

bool UMyBlueprintFunctionLibrary::IsMapIsLoading = false;

UMyBlueprintFunctionLibrary::UMyBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer)
{
	IsMapIsLoading = false;
}

void UMyBlueprintFunctionLibrary::BeginDestroy()
{
	Super::BeginDestroy();

	IsMapIsLoading = false;
}

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

void UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(const UObject* WorldContextObject, FString MapName, bool EnableLoadingScreen ,const float Delay)
{
	if (IsMapIsLoading) return;
	
	IsMapIsLoading = true;
	UWorld* World = const_cast<UWorld*>(WorldContextObject->GetWorld());
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World));
	GameInstance->SetCurrentMapName(MapName);

	// Unpause the game
	UGameplayStatics::SetGamePaused(World, false);

	UAsyncLoadingScreenLibrary::SetEnableLoadingScreen(EnableLoadingScreen);
	
	// Add a delay to allow the button click sound to play
	FTimerHandle TimerHandle;
	
	World->GetTimerManager().SetTimer(TimerHandle, [World, MapName]()
	{
		RemoveAllPlayers(World); 
		UGameplayStatics::OpenLevel(World, *MapName);
		IsMapIsLoading = false;
	}, Delay, false);
}

void UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(const UObject* WorldContextObject,
	ULevelDataAsset* LevelDataAsset, bool EnableLoadingScreen, float Delay)
{
	if (IsMapIsLoading) return;

	IsMapIsLoading = true;
	UWorld* World = const_cast<UWorld*>(WorldContextObject->GetWorld());
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World));
	GameInstance->SetCurrentLevelDataAsset(LevelDataAsset);
	
	// Unpause the game
	UGameplayStatics::SetGamePaused(World, false);

	UAsyncLoadingScreenLibrary::SetEnableLoadingScreen(EnableLoadingScreen);
	
	// Add a delay to allow the button click sound to play
	FTimerHandle TimerHandle;
	
	World->GetTimerManager().SetTimer(TimerHandle, [World, LevelDataAsset]()
	{
		RemoveAllPlayers(World); 
		UGameplayStatics::OpenLevelBySoftObjectPtr(World, LevelDataAsset->GetMapReference());
		IsMapIsLoading = false;
	}, Delay, false);
}

void UMyBlueprintFunctionLibrary::RestartLevelAfterDelay(const UObject* WorldContextObject, bool EnableLoadingScreen,
	float Delay)
{
	const UMyGameInstance* GameInstance = GetGameInstance(WorldContextObject);
	
	if (ULevelDataAsset* LevelDataAsset = GameInstance->GetCurrentLevelDataAsset())
	{
		LoadLevelByReferenceAfterDelay(WorldContextObject, LevelDataAsset, EnableLoadingScreen, Delay);
	}
	else
	{
		LoadLevelByNameAfterDelay(WorldContextObject, GetCurrentMapName(WorldContextObject), EnableLoadingScreen, Delay);
	}
}

UMyGameInstance* UMyBlueprintFunctionLibrary::GetGameInstance(const UObject* WorldContextObject)
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	return GameInstance ? GameInstance : nullptr;
}

UGameData* UMyBlueprintFunctionLibrary::LoadGameDataFromSlot(const FString& SaveSlotName, int32 UserIndex)
{
	const UCustomSaveGame* SaveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (!SaveGameInstance) return nullptr;
	
	return SaveGameInstance->GameData;
}

FString UMyBlueprintFunctionLibrary::GetCurrentMapName(const UObject* WorldContextObject)
{
	const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	
	return GameInstance->GetCurrentMapName();
}

void UMyBlueprintFunctionLibrary::QuitGame(const UObject* WorldContextObject, bool bIgnorePlatformRestrictions)
{
	APlayerController* PlayerController = GetActivePlayerController(WorldContextObject);
	
	UKismetSystemLibrary::QuitGame(WorldContextObject, PlayerController, EQuitPreference::Quit, bIgnorePlatformRestrictions);
}

UUIDataAsset* UMyBlueprintFunctionLibrary::GetUIDataAsset(const UObject* WorldContextObject)
{
	const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (!GameInstance) return nullptr;
	
	return GameInstance->GetUIDataAsset();
}

