// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"
#include "BasePlayerController.h"

ABaseGameMode::ABaseGameMode()
	: Super()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
}