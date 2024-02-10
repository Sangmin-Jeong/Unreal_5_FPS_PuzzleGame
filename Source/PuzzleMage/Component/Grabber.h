// Puzzle Mage by Acthic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"


class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEMAGE_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Floating Setting")
	float MaxGrabDistance = 400.0;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.0;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Floating Setting")
	float HoldDistance = 400.0;

	//Push and pull setting
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Push Setting")
	float MaxPushDistance = 100.0;

	UPROPERTY(EditAnywhere)
	float PushRadius = 100.0;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Push Setting")
	float PushDistance = 100.0;

public:

	
	// Sets default values for this component's properties
	UGrabber();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FHitResult HitResult;

	UPhysicsHandleComponent* PhysicsHandle;

	bool isGrabbing;
	bool isPushing;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	bool CheckLineTrace(FHitResult& OutHitResult) const;
	
	bool CheckLineTraceForPush(FHitResult& OutHitResult) const;
	
	// UPROPERTY(BlueprintCallable)
	void Release();
	
	// UPROPERTY(BlueprintCallable)
	void Grab();

	// UPROPERTY(BlueprintCallable)
	void PushPull();

	// UPROPERTY(BlueprintCallable)
	void StopPushPull();
};
