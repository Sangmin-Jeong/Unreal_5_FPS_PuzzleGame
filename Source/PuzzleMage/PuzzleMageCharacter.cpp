// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleMageCharacter.h"
#include "PuzzleMageProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "GamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "UI/BaseHUD.h"

//////////////////////////////////////////////////////////////////////////
// APuzzleMageCharacter

APuzzleMageCharacter::APuzzleMageCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void APuzzleMageCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void APuzzleMageCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APuzzleMageCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APuzzleMageCharacter::Look);

		//Grabbing
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Ongoing, this, &APuzzleMageCharacter::Grab);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Completed, this, &APuzzleMageCharacter::Release);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Canceled, this, &APuzzleMageCharacter::Release);

		//Pause Key Press
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APuzzleMageCharacter::Pause);
		
		//Push pull Key Press
		EnhancedInputComponent->BindAction(PushPullAction, ETriggerEvent::Ongoing, this, &APuzzleMageCharacter::PushPull);
		EnhancedInputComponent->BindAction(PushPullAction, ETriggerEvent::Completed, this, &APuzzleMageCharacter::StopPushPull);
		EnhancedInputComponent->BindAction(PushPullAction, ETriggerEvent::Canceled, this, &APuzzleMageCharacter::StopPushPull);

	}
}

void APuzzleMageCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APuzzleMageCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APuzzleMageCharacter::Grab()
{
	OnGrabbedDelegate.ExecuteIfBound();
}

void APuzzleMageCharacter::Release()
{
	OnReleasedDelegate.ExecuteIfBound();
}

void APuzzleMageCharacter::Pause()
{
	UE_LOG(LogTemp, Display, TEXT(" Execute PAUSE "));
	OnPausedDelegate.ExecuteIfBound();
}

void APuzzleMageCharacter::PushPull()
{
	OnPushPullDelegate.ExecuteIfBound();
}

void APuzzleMageCharacter::StopPushPull()
{
	OnStopPushPullDelegate.ExecuteIfBound();
}

void APuzzleMageCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool APuzzleMageCharacter::GetHasRifle()
{
	return bHasRifle;
}