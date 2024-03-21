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
		Character->OnUnPausedDelegate.BindUObject(this, &ABaseHUD::UnPause);
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
	if(!PauseWidgetClass) return;
	
	if(bIsDisplayed)
	{
		UnPause();
	}
	else
	{
		// Display Pause Widget
		PauseWidget = CreateWidget<UPauseScreenUI>(GetWorld(), PauseWidgetClass);
		PauseWidget->AddToViewport();
		bIsDisplayed = true;
		
		// Set Controller
		if(PlayerController)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), bIsDisplayed);
			SetControllerGameAndUIOnly();
		}
	}
	
}

void ABaseHUD::UnPause()
{
	if (!PauseWidget) return;
	
	// Hide Widget
	if (!PauseWidget->IsAtPauseMenu())
	{
		PauseWidget->ShowPauseMenuPanel();
		return;
	}
	
	PauseWidget->RemoveFromParent();
	PauseWidget = nullptr;
	bIsDisplayed = false;
	
	// Set Controller
	if(PlayerController)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), bIsDisplayed);
		SetControllerGameOnly();
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
