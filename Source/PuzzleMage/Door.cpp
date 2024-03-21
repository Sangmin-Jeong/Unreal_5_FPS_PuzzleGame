// Puzzle Mage by Acthic Moose Games


#include "Door.h"

#include "PuzzleMageGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();
	if(bIsFinalDoor)
	{
		if(UGameInstance* GameInstance = GetGameInstance())
		{
			if(APuzzleMageGameMode* GameMode = Cast<APuzzleMageGameMode>(UGameplayStatics::GetGameMode(GameInstance)))
			{
				GameMode->Door = this;
			}
		}
	}
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector TargetLocation = OriginalLocation;
	if(ShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}
	FVector CurrentLocation = GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;
	
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	SetActorLocation(NewLocation);

}

void ADoor::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

