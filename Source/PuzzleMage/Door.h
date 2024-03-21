// Puzzle Mage by Acthic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"



UCLASS()
class PUZZLEMAGE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetShouldMove(bool NewShouldMove);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door Properties")
	bool bIsFinalDoor;

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 2;
	
	bool ShouldMove = false;

	FVector OriginalLocation;

	

};
