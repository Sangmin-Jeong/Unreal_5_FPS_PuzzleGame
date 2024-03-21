// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleMageCharacter.h"

#include "AchievementSaveGame.h"
#include "AchievementSubSystem.h"
#include "CineCameraActor.h"
#include "PuzzleMageProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "GamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PuzzleMageGameMode.h"
#include "Component/Grabber.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseHUD.h"
#include "UI/PauseScreenUI.h"
#include "AchievementSystem.h"

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

	// Grabber
	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	Grabber->SetupAttachment(FirstPersonCameraComponent);

}

void APuzzleMageCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Bind Final Door Opened Delegate
	if(UGameInstance* GameInstance = GetGameInstance())
	{
		if(APuzzleMageGameMode* GameMode = Cast<APuzzleMageGameMode>(UGameplayStatics::GetGameMode(GameInstance)))
		{
			GameMode->FinalDoorOpenedDelegate.BindUObject(this, &APuzzleMageCharacter::ActiveCineCamera);
		}
	}
}

void APuzzleMageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(StayStillAchievementUnlocked == false)
	{
		StayStillTimeCounter += DeltaTime;
		if(StayStillTimeCounter > StayStillAchievementTime)
		{
			UMyBlueprintFunctionLibrary::UnlockAchievement(this,"Still");
			StayStillAchievementUnlocked = true;
		}
	}
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

#if PLATFORM_SWITCH
		EnhancedInputComponent->BindAction(BackActionBottom, ETriggerEvent::Completed, this, &APuzzleMageCharacter::Back);
#else
		EnhancedInputComponent->BindAction(BackActionRight, ETriggerEvent::Completed, this, &APuzzleMageCharacter::Back);
#endif

		//Change Camera Key Press
		EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Triggered, this, &APuzzleMageCharacter::ChangeToMapCamera);
		EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Completed, this, &APuzzleMageCharacter::ChangeToDefaultCamera);
	}

	// Bind to HUD
	AGamePlayerController* PlayerController = Cast<AGamePlayerController>(Controller);
	if (!PlayerController) return;
	
	if (ABaseHUD* BaseHUD = Cast<ABaseHUD>(PlayerController->GetHUD()))
	{
		BaseHUD->SubscribePauseDelegate();
	}
}

void APuzzleMageCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//If player is pushing, disable left and right movement
		if(Grabber->GetIsPushing())
		{
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		}

		else
		{
			// add movement
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
	ResetStillAchievementTimer();
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
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::Grab()
{
	Grabber->Grab();
	
	if(!GrabAchievementUnlocked)
	{
		if(Grabber->GetIsGrabbing())
		{
			UMyBlueprintFunctionLibrary::UnlockAchievement(this, "FloatingBlock");
			GrabAchievementUnlocked = true;
		}
	}
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::Release()
{
	Grabber->Release();

	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::Pause()
{
	if(Grabber->GetIsPushing()) return;
	
	OnPausedDelegate.ExecuteIfBound();

	if(!PauseAchievementUnlocked)
	{
		UMyBlueprintFunctionLibrary::UnlockAchievement(this,"Pause");
		PauseAchievementUnlocked = true;
	}
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::PushPull()
{
	Grabber->PushPull();

	if(!PushAchievementUnlocked)
	{
		if(Grabber->GetIsPushing())
		{
			UMyBlueprintFunctionLibrary::UnlockAchievement(this, "Push");
			PushAchievementUnlocked = true;
		}
	}
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::StopPushPull()
{
	Grabber->StopPushPull();
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::Back()
{
	OnUnPausedDelegate.ExecuteIfBound();
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::ChangeToMapCamera()
{
	if(Grabber->GetIsPushing()) return;
	
	//Change to map camera
	ChangeCameraView();
}

void APuzzleMageCharacter::ChangeToDefaultCamera()
{
	if(Grabber->GetIsPushing()) return;
	
	//Change back to 1st person camera view
	ResetCameraView();
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::ChangeCameraView()
{
}

void APuzzleMageCharacter::ResetCameraView()
{
}

void APuzzleMageCharacter::ActiveCineCamera()
{
	
	CineCamera = Cast<ACineCameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), CameraActorClass));
	if(CineCamera)
	{
		// Disable Input and Release Block
		StopPushPull();
		Release();
		DisableInput(UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()));

		// Change View Camera to Cine Camera 
		UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld())->SetViewTargetWithBlend(
		CineCamera, 1.0f, EViewTargetBlendFunction::VTBlend_Linear
		);

		// Set Timer for above Camera Movement
		GetWorldTimerManager().SetTimer(TimerHandle, [this]
		{
			// Change back View Camera to default 
			UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld())->SetViewTargetWithBlend(
			this, 1.0f, EViewTargetBlendFunction::VTBlend_Linear
			);

				// Set Timer for above Camera Movement
				GetWorldTimerManager().SetTimer(TimerHandle, [this]
				{
					// Enable Input
					EnableInput(UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()));
				}, 1.5f, false);
			
		}, DelayTime, false);
		
	}
	ResetStillAchievementTimer();
}

void APuzzleMageCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool APuzzleMageCharacter::GetHasRifle()
{
	return bHasRifle;
}

void APuzzleMageCharacter::ResetStillAchievementTimer()
{
	// Reset timer for Still achievement
	if(StayStillAchievementUnlocked == false)
	{
		StayStillTimeCounter = 0;
	}
}

