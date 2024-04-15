// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "CustomGameViewportClient.h"
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Data/ChapterDataAsset.h"
#include "Data/CustomSaveGame.h"
#include "Data/GameData.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "UI/ControllerDisconnectedWidget.h"
#include "UI/AutoSaveWidget.h"

class UCustomGameViewportClient;

void UMyGameInstance::Init()
{
	Super::Init();

	bShowAutoSaveTip = true;

	IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &UMyGameInstance::OnControllerChanged);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::EndLoadingScreen);

	if (UGameData* LoadedGameData = UMyBlueprintFunctionLibrary::LoadGameDataFromSlot(GameData->GetSaveSlotName(), GameData->GetUserIndex()))
	{
		GameData = LoadedGameData;
	}

	GameUserSettings = UGameUserSettings::GetGameUserSettings(); // TODO: Not implemented yet

	InitializeSoundClasses();
	InitializeConsoleCommands();

	OnSaveGameToSlotCompleteDelegate.BindUObject(this, &UMyGameInstance::OnSaveGameToSlotComplete);
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	IConsoleManager::Get().UnregisterConsoleObject(TEXT("UnlockAllLevels"));
	IConsoleManager::Get().UnregisterConsoleObject(TEXT("GiveUp"));
}

void UMyGameInstance::SetActiveControllerId(int32 ControllerId)
{
	ActiveControllerId = ControllerId;
}

int32 UMyGameInstance::GetActiveControllerId() const
{
	return ActiveControllerId;
}

UGameData* UMyGameInstance::GetGameData() const
{
	return GameData;
}

UGameUserSettings* UMyGameInstance::GetGameUserSettings() const
{
	return GameUserSettings;
}

bool UMyGameInstance::HasSaveData() const
{
	const UGameData* LoadedGameData = UMyBlueprintFunctionLibrary::LoadGameDataFromSlot(GameData->GetSaveSlotName(), GameData->GetUserIndex());
	return LoadedGameData != nullptr;
}

void UMyGameInstance::SaveGameData()
{
	//UMyBlueprintFunctionLibrary::SaveGameData(GameData);
	UCustomSaveGame* SaveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass()));
	GameData->UpdateTotalLevelsCompleted();
	SaveGameInstance->GameData = GameData;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, GameData->GetSaveSlotName(), GameData->GetUserIndex(), OnSaveGameToSlotCompleteDelegate);
}

void UMyGameInstance::ResetGameData()
{
	if (GameData)
	{
		GameData->Reset();

		SetShouldSaveGameData(true);
	}
}

FString UMyGameInstance::GetCurrentMapName() const
{
	return CurrentMapName;
}

ULevelDataAsset* UMyGameInstance::GetCurrentLevelDataAsset() const
{
	return CurrentLevelDataAsset;
}

ULevelDataAsset* UMyGameInstance::GetLastUnlockedLevelDataAsset() const
{
	if (GameData == nullptr) return nullptr;

	for (int32 ChapterIndex = GameData->GetChapterDataAssets().Num() - 1; ChapterIndex >= 0; --ChapterIndex)
	{
		if (const UChapterDataAsset* ChapterDataAsset = GameData->GetChapterDataAsset(ChapterIndex))
		{
			for (int32 LevelIndex = ChapterDataAsset->GetLevelDataAssets().Num() - 1; LevelIndex >= 0; --LevelIndex)
			{
				if (ULevelDataAsset* LevelDataAsset = ChapterDataAsset->GetLevelDataAsset(LevelIndex))
				{
					if (!LevelDataAsset->GetIsLocked())
					{
						return LevelDataAsset;
					}
				}
			}
		}
	}

	return nullptr;
}

ULevelDataAsset* UMyGameInstance::GetFirstLevelDataAsset() const
{
	if (GameData == nullptr) return nullptr;

	for (int32 ChapterIndex = 0; ChapterIndex < GameData->GetChapterDataAssets().Num(); ++ChapterIndex)
	{
		if (const UChapterDataAsset* ChapterDataAsset = GameData->GetChapterDataAsset(ChapterIndex))
		{
			for (int32 LevelIndex = 0; LevelIndex < ChapterDataAsset->GetLevelDataAssets().Num(); ++LevelIndex)
			{
				if (ULevelDataAsset* LevelDataAsset = ChapterDataAsset->GetLevelDataAsset(LevelIndex))
				{
					if (!LevelDataAsset->GetIsLocked())
					{
						return LevelDataAsset;
					}
				}
			}
		}
	}

	return nullptr;
}

ULevelDataAsset* UMyGameInstance::GetNextLevelDataAsset() const
{
	if (GameData == nullptr) return nullptr;

	if (CurrentLevelDataAsset == nullptr)
	{
		return GetLastUnlockedLevelDataAsset();
	}

	const int32 ChapterIndex = CurrentLevelDataAsset->GetChapterIndex();
	const int32 LevelIndex = CurrentLevelDataAsset->GetLevelIndex();

	if (const UChapterDataAsset* CurrentChapterDataAsset = GameData->GetChapterDataAsset(ChapterIndex))
	{
		if (CurrentChapterDataAsset->GetLevelDataAssets().IsValidIndex(LevelIndex + 1))
		{
			return CurrentChapterDataAsset->GetLevelDataAsset(LevelIndex + 1);
		}

		if (GameData->GetChapterDataAssets().IsValidIndex(ChapterIndex + 1))
		{
			if (GameData->GetChapterDataAsset(ChapterIndex + 1)->GetIsLocked())
			{
				GameData->GetChapterDataAsset(ChapterIndex + 1)->SetChapterIsLocked(false);
			}
			
			if (const UChapterDataAsset* NextChapterDataAsset = GameData->GetChapterDataAsset(ChapterIndex + 1))
			{
				if (NextChapterDataAsset->GetLevelDataAssets().IsValidIndex(0))
				{
					return NextChapterDataAsset->GetLevelDataAsset(0);
				}
			}
		}
	}

	return nullptr;
}

void UMyGameInstance::SetCurrentMapName(FString MapName)
{
	CurrentMapName = MapName;
}

void UMyGameInstance::SetCurrentLevelDataAsset(ULevelDataAsset* LevelDataAsset)
{
	CurrentLevelDataAsset = LevelDataAsset;

	if (LevelDataAsset->GetIsLocked())
	{
		LevelDataAsset->SetLevelIsLocked(false);
	}
}

void UMyGameInstance::InitializeSoundClasses()
{
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = GameData->GetMasterVolume();
	}

	if (MusicSoundClass)
	{
		MusicSoundClass->Properties.Volume = GameData->GetMusicVolume();
	}

	if (SFXSoundClass)
	{
		SFXSoundClass->Properties.Volume = GameData->GetSFXVolume();
	}
}

float UMyGameInstance::GetAudioVolume(EAudioType AudioType) const
{
	switch (AudioType)
	{
	case EAudioType::Master:
		if (MasterSoundClass)
		{
			return MasterSoundClass->Properties.Volume;
		}
		break;
	case EAudioType::Music:
		if (MusicSoundClass)
		{
			return MusicSoundClass->Properties.Volume;
		}
		break;
	case EAudioType::SFX:
		if (SFXSoundClass)
		{
			return SFXSoundClass->Properties.Volume;
		}
		break;
	}
	
	return 0.0f;
}

void UMyGameInstance::SetAudioVolume(EAudioType AudioType, float Volume)
{
	switch (AudioType)
	{
	case EAudioType::Master:
		if (MasterSoundClass)
		{
			MasterSoundClass->Properties.Volume = Volume;
			GameData->SetAudioVolume(AudioType, Volume);
		}
		break;
	case EAudioType::Music:
		if (MusicSoundClass)
		{
			MusicSoundClass->Properties.Volume = Volume;
			GameData->SetAudioVolume(AudioType, Volume);
		}
		break;
	case EAudioType::SFX:
		if (SFXSoundClass)
		{
			SFXSoundClass->Properties.Volume = Volume;
			GameData->SetAudioVolume(AudioType, Volume);
		}
		break;
	default:
		break;
	}
}

bool UMyGameInstance::GetShouldSaveGameData() const
{
	return bShouldSaveGameData;
}

void UMyGameInstance::SetShouldSaveGameData(bool bShouldSave)
{
	bShouldSaveGameData = bShouldSave;
}

void UMyGameInstance::OnSaveGameToSlotComplete(const FString& SlotName, int32 UserIndex, const bool bSuccess)
{
	if (bSuccess)
	{
		AutoSaveTimerHandle.Invalidate();
		
		GetTimerManager().SetTimer(AutoSaveTimerHandle, [this]()
		{
			if (AutoSaveWidget)
			{
				AutoSaveWidget->RemoveFromParent();
			}
		}, AutoSaveWidget->GetAutoSaveTime(), false);
	}
}

void UMyGameInstance::InitializeConsoleCommands()
{
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("UnlockAllLevels"),
		TEXT("Unlocks all levels and chapters."),
		FConsoleCommandDelegate::CreateUObject(this, &UMyGameInstance::UnlockAllLevels)
	);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("GiveUp"),
		TEXT("Goes to the next level."),
		FConsoleCommandDelegate::CreateUObject(this, &UMyGameInstance::GiveUp)
	);
}

void UMyGameInstance::UnlockAllLevels()
{
	for (UChapterDataAsset* ChapterDataAsset : GameData->GetChapterDataAssets())
	{
		ChapterDataAsset->SetChapterIsLocked(false);
		for (ULevelDataAsset* LevelDataAsset : ChapterDataAsset->GetLevelDataAssets())
		{
			LevelDataAsset->SetLevelIsLocked(false);
		}
	}
}

void UMyGameInstance::GiveUp()
{
	ULevelDataAsset* NextLevelDataAsset = GetNextLevelDataAsset();
	UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(GetWorld(), NextLevelDataAsset);
}

void UMyGameInstance::OnControllerChanged(EInputDeviceConnectionState ConnectionState, FPlatformUserId UserId,
                                          FInputDeviceId InputDeviceId)
{
	FString UserId_Text;
	if (UserId == PLATFORMUSERID_NONE)
	{
		UserId_Text = TEXT("None");
	}
	else
	{
		UserId_Text = FString::Printf(TEXT("%d"), UserId.GetInternalId());
	}

	if (ConnectionState == EInputDeviceConnectionState::Disconnected)
	{
		const FString Message = FString::Printf(TEXT("Controler connection changed - UserIdx:%d, UserId:%s, Disconnected"), InputDeviceId.GetId(), *UserId_Text);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Message);
	}
	else if (ConnectionState == EInputDeviceConnectionState::Connected)
	{
		const FString Message = FString::Printf(TEXT("Controler connection changed - UserIdx:%d, UserId:%s, Connected"), InputDeviceId.GetId(), *UserId_Text);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Message);
	}

	if (GetActiveControllerId() == InputDeviceId.GetId())
	{
		if (APlayerController* ActivePC = UMyBlueprintFunctionLibrary::GetActivePlayerController(this))
		{
			if (ConnectionState == EInputDeviceConnectionState::Connected)
			{
				if (bDidControllerDisconnectPauseGame)
				{
					UGameplayStatics::SetGamePaused(this, false);
					bDidControllerDisconnectPauseGame = false;
				}
				ControllerDisconnectedWidget->RemoveFromParent();
			}
			else
			{
				// TODO: Delete this after adding a widget
				if (!UGameplayStatics::IsGamePaused(this))
				{
					UGameplayStatics::SetGamePaused(this, true);
					bDidControllerDisconnectPauseGame = true;
				}		
		
				if (ControllerDisconnectedWidgetClass)
				{
					if (!UGameplayStatics::IsGamePaused(this))
					{
						UGameplayStatics::SetGamePaused(this, true);
						bDidControllerDisconnectPauseGame = true;
					}
					ControllerDisconnectedWidget = CreateWidget<UControllerDisconnectedWidget>(ActivePC, ControllerDisconnectedWidgetClass);
					ControllerDisconnectedWidget->AddToViewport();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ControllerDisconnectedWidgetClass is nullptr"));
				}
			}
		}
	}
}

void UMyGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		// Fade in from black
		const UWorld* World = GetWorld();
		if (World)
		{
			UCustomGameViewportClient* CustomViewport = Cast<UCustomGameViewportClient>(World->GetGameViewport());
			if (CustomViewport)
			{
				CustomViewport->Fade(true);
			}
		}
	}
}

void UMyGameInstance::EndLoadingScreen(UWorld* InLoaderWorld)
{
	// Fade out from black
	const UWorld* World = GetWorld();
	if (World)
	{
		UCustomGameViewportClient* CustomViewport = Cast<UCustomGameViewportClient>(World->GetGameViewport());
		if (CustomViewport)
		{
			CustomViewport->Fade(false);
		}
	}

	// Save Game Data if needed after loading screen
	if (bShouldSaveGameData == false) return;

	if (AutoSaveWidgetClass)
	{
		AutoSaveWidget = CreateWidget<UAutoSaveWidget>(this, AutoSaveWidgetClass);
		AutoSaveWidget->AddToViewport();
	}
	
	SaveGameData();

	bShouldSaveGameData = false;
}

UUIDataAsset* UMyGameInstance::GetUIDataAsset() const
{
	// Get current Platform
	FString PlatformName = UGameplayStatics::GetPlatformName();

	if (PlatformName == "WINDOWS")
	{
		return XboxUIDataAsset;
	}
	else if (PlatformName == "PS5")
	{
		return PS5UIDataAsset;
	}
	else if (PlatformName == "SWITCH")
	{
		return SwitchUIDataAsset;
	}
	else
	{
		return XboxUIDataAsset;
	}
}
