// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "CustomGameViewportClient.h"
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

class UCustomGameViewportClient;

void UMyGameInstance::Init()
{
	Super::Init();

	IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &UMyGameInstance::OnControllerChanged);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::EndLoadingScreen);
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMyGameInstance::SetActiveControllerId(int32 ControllerId)
{
	ActiveControllerId = ControllerId;
}

int32 UMyGameInstance::GetActiveControllerId() const
{
	return ActiveControllerId;
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
				// ControllerDisconnectedWidget->RemoveFromParent();
			}
			else
			{
				// TODO: Delete this after adding a widget
				if (!UGameplayStatics::IsGamePaused(this))
				{
					UGameplayStatics::SetGamePaused(this, true);
					bDidControllerDisconnectPauseGame = true;
				}		
		
				// if (ControllerDisconnectedWidgetClass)
				// {
				// 	if (!UGameplayStatics::IsGamePaused(this))
				// 	{
				// 		UGameplayStatics::SetGamePaused(this, true);
				// 		bDidControllerDisconnectPauseGame = true;
				// 	}
				// 	ControllerDisconnectedWidget = CreateWidget<UControllerDisconnectedWidget>(ActivePC, ControllerDisconnectedWidgetClass);
				// 	ControllerDisconnectedWidget->AddToViewport();
				// }
				// else
				// {
				// 	UE_LOG(LogTemp, Warning, TEXT("ControllerDisconnectedWidgetClass is nullptr"));
				// }
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
}