// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetWidgetForInput(UUserWidget* Widget);
	
	UFUNCTION()
	void RemoveWidgetForInput();

private:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* UIInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* TabLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* TabRightAction;

	UFUNCTION()
	void TabLeft();

	UFUNCTION()
	void TabRight();

	UUserWidget* CurrentActivatedWidget;
};
