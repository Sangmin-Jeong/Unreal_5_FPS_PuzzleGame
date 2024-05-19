// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "BaseObjectActor.h"
#include "Components/TimelineComponent.h"
#include "DoorClass.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API ADoorClass : public ABaseObjectActor
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

	FTimeline DoorTimeline;

public:
	ADoorClass();

	void MovingDoor();
	void OpenDoor();
	void ResetDoor();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door Properties")
	bool bIsFinalDoor;
	
	FTimeline GetTimeline() const {return DoorTimeline;}
	
};
