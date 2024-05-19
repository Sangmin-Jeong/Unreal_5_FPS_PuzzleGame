// Puzzle Mage by Arctic Moose Games


#include "DoorClass.h"

#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/PuzzleMageGameMode.h"

ADoorClass::ADoorClass()
{
}

void ADoorClass::BeginPlay()
{
	Super::BeginPlay();

	if(bIsFinalDoor)
	{
		if(UGameInstance* GameInstance = GetGameInstance())
		{
			if(APuzzleMageGameMode* GameMode = Cast<APuzzleMageGameMode>(UGameplayStatics::GetGameMode(GameInstance)))
			{
				GameMode->DoorClass = this;
			}
		}
	}

	FOnTimelineFloat TimelineUpdate;
	TimelineUpdate.BindUFunction(this, FName("MovingDoor"));
}

void ADoorClass::MovingDoor()
{
	UE_LOG(LogTemp, Display, TEXT("moving"));
}

void ADoorClass::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Opend !!"));
}

void ADoorClass::ResetDoor()
{
}
