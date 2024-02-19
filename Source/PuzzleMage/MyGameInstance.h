// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

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

	UFUNCTION()
	class UGameData* GetGameData() const;

	UFUNCTION()
	FName GetCurrentMapName() const;

	UFUNCTION()
	void SetCurrentMapName(FName MapName);

private:
	UPROPERTY(EditAnywhere, Category = "Game Data")
	TSoftObjectPtr<class UGameData> GameDataClass;

	UPROPERTY()
	UGameData* GameData;

	UPROPERTY()
	FName CurrentMapName;
};
