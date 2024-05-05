// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraActor.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraActor.h"
#include "PuzzleMageCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UGrabber;

DECLARE_DELEGATE(FOnPausedDelegate)
DECLARE_DELEGATE(FOnUnPausedDelegate)

UCLASS(config=Game)
class APuzzleMageCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* GrabAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;

	// /** Push and Pull Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// class UInputAction* PushPullAction;

	/** Back Right Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* BackActionRight;

	/** Back Bottom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* BackActionBottom;

	// /** Change Camera View Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// class UInputAction* ChangeCameraAction;
	
public:
	APuzzleMageCharacter();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** Delegate */
	FOnPausedDelegate OnPausedDelegate;
	FOnUnPausedDelegate OnUnPausedDelegate;

	//
	// UFUNCTION(BlueprintCallable, Category = "Change Camera")
	// void ChangeCameraView();
	//
	// UFUNCTION(BlueprintCallable, Category = "Change Camera")
	// void ResetCameraView();

	UFUNCTION(BlueprintCallable, Category = "Change Camera")
	void ActiveCineCamera();
	
	UPROPERTY(VisibleAnywhere, Category = "Change Camera")
	TSubclassOf<ACameraActor> CameraActorClass = ACameraActor::StaticClass();

	UPROPERTY(VisibleAnywhere, Category = "Change Camera")
	TObjectPtr<ACineCameraActor> CineCamera;

	UPROPERTY(EditAnywhere, Category = "Change Camera")
	float DelayTime = 2.0f;
	
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Achievement, meta = (AllowPrivateAccess = "true"))
	float StayStillAchievementTime = 30.0f;
	float StayStillTimeCounter = 0;
	bool StayStillTimeCounterStart = false;
	bool StayStillAchievementUnlocked = false;
	bool PauseAchievementUnlocked = false;
	// bool PushAchievementUnlocked = false;
	bool GrabAchievementUnlocked = false;
	bool MagicRuneAchievementUnlocked = false;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	void ResetStillAchievementTimer();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Grabbing input */
	void Grab();

	/** Called for Release input */
	void Release();

	/** Called for Pause input */
	void Pause();

	// /** Called for Push and pull input */
	// void PushPull();
	//
	// /** Called for stop Push and pull input */
	// void StopPushPull();

	/** Called for Back input */
	void Back();

	/** Called for Change camera input */
	// void ChangeToMapCamera();
	// void ChangeToDefaultCamera();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	
public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UGrabber> Grabber;
};

