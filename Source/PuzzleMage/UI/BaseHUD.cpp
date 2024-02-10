// Puzzle Mage by Acthic Moose Games


#include "BaseHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/PuzzleMageCharacter.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseHUD::SubscribePauseDelegate()
{
	APuzzleMageCharacter* Character = Cast<APuzzleMageCharacter>(UMyBlueprintFunctionLibrary::GetActivePlayerCharacter(GetWorld()));
	
	// Avoiding Nullptr
	if(Character)
	{
		Character->OnPausedDelegate.BindUObject(this, &ABaseHUD::Pause);
		UE_LOG(LogTemp, Display, TEXT(" Character Set For Pause "));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT(" Character class doesn't set up yet ! "));
	}

	PlayerController = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
}

void ABaseHUD::Pause()
{
	if(!WidgetClass) return;

	UE_LOG(LogTemp, Display, TEXT(" PAUSE "));
	
	if(bIsDisplayed)
	{
		// Hide Widget
		Widget->RemoveFromParent();
		bIsDisplayed = false;
		
		// Set Controller
		if(PlayerController)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), bIsDisplayed);
			SetControllerGameOnly();
		}
	}
	else
	{
		// Display Pause Widget
		Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		Widget->AddToViewport();
		bIsDisplayed = true;
		
		// Set Controller
		if(PlayerController)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), bIsDisplayed);
			SetControllerGameAndUIOnly();
		}
	}
	
}

void ABaseHUD::SetControllerUIOnly()
{
	if(PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}
}

void ABaseHUD::SetControllerGameOnly()
{
	if(PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}

void ABaseHUD::SetControllerGameAndUIOnly()
{
	if(PlayerController)
	{
		FInputModeGameAndUI InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}
