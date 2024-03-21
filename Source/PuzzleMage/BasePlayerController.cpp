// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "UI/LevelSelectScreenUI.h"

class UEnhancedInputLocalPlayerSubsystem;

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(UIInputMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TabLeftAction, ETriggerEvent::Triggered, this, &ABasePlayerController::TabLeft);
		EnhancedInputComponent->BindAction(TabRightAction, ETriggerEvent::Triggered, this, &ABasePlayerController::TabRight);
	}
}

void ABasePlayerController::TabLeft()
{
	if (ULevelSelectScreenUI* LevelSelectScreenUI = Cast<ULevelSelectScreenUI>(CurrentActivatedWidget))
	{
		LevelSelectScreenUI->TabLeft();
	}
}

void ABasePlayerController::TabRight()
{
	if (ULevelSelectScreenUI* LevelSelectScreenUI = Cast<ULevelSelectScreenUI>(CurrentActivatedWidget))
	{
		LevelSelectScreenUI->TabRight();
	}
}

void ABasePlayerController::SetWidgetForInput(UUserWidget* Widget)
{
	CurrentActivatedWidget = Widget;
}

void ABasePlayerController::RemoveWidgetForInput()
{
	CurrentActivatedWidget = nullptr;
}
