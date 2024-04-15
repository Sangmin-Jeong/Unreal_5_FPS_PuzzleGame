// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LevelDataAsset.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.generated.h"

UENUM()
enum class EAudioType
{
	Master,
	Music,
	SFX
};

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()	

	int32 ActiveControllerId = -1;

	bool bDidControllerDisconnectPauseGame = false;
	
	UPROPERTY()
	class UControllerDisconnectedWidget* ControllerDisconnectedWidget;
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UControllerDisconnectedWidget> ControllerDisconnectedWidgetClass;

	UPROPERTY()
	class UAutoSaveWidget* AutoSaveWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UAutoSaveWidget> AutoSaveWidgetClass;

	UFUNCTION()
	void OnControllerChanged(EInputDeviceConnectionState ConnectionState, FPlatformUserId UserId, FInputDeviceId InputDeviceId);

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoaderWorld);
	
public:
	static const int32 MAX_CONTROLLERS = 4;
	
	virtual void Init() override;
	virtual void Shutdown() override;

	void SetActiveControllerId(int32 ControllerId);
	int32 GetActiveControllerId() const;

	UFUNCTION(BlueprintCallable)
	class UGameData* GetGameData() const;

	UFUNCTION(BlueprintCallable)
	class UUIDataAsset* GetUIDataAsset() const;

	UFUNCTION()
	class UGameUserSettings* GetGameUserSettings() const;

	UFUNCTION()
	bool HasSaveData() const;

	UFUNCTION(BlueprintCallable)
	void SaveGameData();

	UFUNCTION()
	void ResetGameData();

	UFUNCTION()
	FString GetCurrentMapName() const;

	UFUNCTION(BlueprintCallable)
	ULevelDataAsset* GetCurrentLevelDataAsset() const;

	UFUNCTION()
	ULevelDataAsset* GetLastUnlockedLevelDataAsset() const;

	UFUNCTION()
	ULevelDataAsset* GetFirstLevelDataAsset() const;

	UFUNCTION(BlueprintCallable)
	ULevelDataAsset* GetNextLevelDataAsset() const;
	
	UFUNCTION()
	void SetCurrentMapName(FString MapName);

	UFUNCTION()
	void SetCurrentLevelDataAsset(ULevelDataAsset* LevelDataAsset);
	
	void InitializeSoundClasses();

	UFUNCTION()
	float GetAudioVolume(EAudioType AudioType) const;

	UFUNCTION()
	void SetAudioVolume(EAudioType AudioType, float Volume);

	UFUNCTION(BlueprintCallable)
	bool GetShouldSaveGameData() const;

	UFUNCTION(BlueprintCallable)
	void SetShouldSaveGameData(bool bShouldSave);
private:
	UPROPERTY(EditAnywhere, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	UGameData* GameData;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundClass* MasterSoundClass;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundClass* MusicSoundClass;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundClass* SFXSoundClass;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* XboxUIDataAsset;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* PS5UIDataAsset;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* SwitchUIDataAsset;

	UPROPERTY()
	FString CurrentMapName;

	UPROPERTY()
	ULevelDataAsset* CurrentLevelDataAsset;

	UPROPERTY()
	UGameUserSettings* GameUserSettings;

	FTimerHandle AutoSaveTimerHandle;
	FAsyncSaveGameToSlotDelegate OnSaveGameToSlotCompleteDelegate;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bShowAutoSaveTip;

	UPROPERTY()
	bool bShouldSaveGameData;

	UFUNCTION()
	void OnSaveGameToSlotComplete(const FString& SlotName, int32 UserIndex, const bool bSuccess);

	void InitializeConsoleCommands();

	UFUNCTION()
	void UnlockAllLevels();

	UFUNCTION()
	void GiveUp();
};
