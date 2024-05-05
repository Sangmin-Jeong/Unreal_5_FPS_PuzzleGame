// Puzzle Mage by Acthic Moose Games


#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PuzzleMage/Object/BaseObjectActor.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Get References of Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// Avoiding Nullptr
	check(PhysicsHandle);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(CheckLineTrace(HitResult))
	{
		//Highlighting
		if(HighlightingActor)
		if(HitResult.GetActor() != HighlightingActor)
		{
			HighlightingActor->UnHighlighting();
		}
		
		HighlightingActor = Cast<ABaseObjectActor>(HitResult.GetActor());
		
		if(HighlightingActor)
		{
			HighlightingActor->Highlighting();
		}
	}
	else
	{
		//UnHighlighting
		if(HighlightingActor)
		{
			if(HighlightingActor != HitResult.GetActor())
			{
				HighlightingActor->UnHighlighting();
			}
		}
	}
	
	//UE_LOG(LogTemp, Error, TEXT("Player: %s"), *GetComponentLocation().ToString());

	if(PhysicsHandle->GetGrabbedComponent())
	{
		if(isGrabbing)
		{
			FVector Direction = PhysicsHandle->GetGrabbedComponent()->GetComponentLocation() - GetComponentLocation();
			FVector TargetLocation;
			float Distance = Direction.Length();
			//UE_LOG(LogTemp, Error, TEXT("Distance: %f"), Distance);

			// Distance less than Max Hold Distance
			if(Distance < HoldDistance && Distance > MinHoldDistance)
			{
				TargetLocation = GetComponentLocation() + GetForwardVector() * Distance;
			}
			// Distance grater than Max Hold Distance
			else if(Distance > HoldDistance)
			{
				TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
			}
			// Distance less than Min Hold Distance
			else if(Distance < MinHoldDistance)
			{
				TargetLocation = GetComponentLocation() + GetForwardVector() * MinHoldDistance;
			}
			
			PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
		}

		// if(isPushing)
		// {
		// 	// Pushing the Grabbed Object
		// 	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * PushDistance;
		// 	PhysicsHandle->SetTargetLocation(TargetLocation);
		// }
	}
}

bool UGrabber::CheckLineTrace(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}

// bool UGrabber::CheckLineTraceForPush(FHitResult& OutHitResult) const
// {
// 	FVector Start = GetComponentLocation();
// 	FVector End = Start + GetForwardVector() * MaxPushDistance;
// 	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue);
//
// 	FCollisionShape Sphere = FCollisionShape::MakeSphere(PushRadius);
// 	return GetWorld()->SweepSingleByChannel(
// 		OutHitResult,
// 		Start, End,
// 		FQuat::Identity,
// 		ECC_GameTraceChannel2,
// 		Sphere
// 	);
// }


void UGrabber::Release()
{
	// If its a pushable object, ignore floating ability
	ABaseObjectActor* BaseObjectActor = Cast<ABaseObjectActor>(HitResult.GetActor());
	// if (BaseObjectActor && BaseObjectActor->IsPushable()) return; 
	
	//UE_LOG(LogTemp, Display, TEXT(" RELEASE "));
	if(PhysicsHandle->GetGrabbedComponent())
	{
		// Play SFX
		if(BaseObjectActor)
		{
			BaseObjectActor->PlayQuitInteractionSFX();
		}
		
		// Release
		if(HitResult.GetComponent())
		{
			HitResult.GetComponent()->WakeAllRigidBodies();
			HitResult.GetComponent()->SetPhysicsLinearVelocity(FVector::Zero());
		}
		PhysicsHandle->ReleaseComponent();

		isGrabbing = false;
	}
}

void UGrabber::Grab()
{
	//UE_LOG(LogTemp, Display, TEXT(" GRAB "));
	if(PhysicsHandle->GetGrabbedComponent()) return;
	
	if(CheckLineTrace(HitResult))
	{
		// If its a pushable object, ignore floating ability
		ABaseObjectActor* BaseObjectActor = Cast<ABaseObjectActor>(HitResult.GetActor());
		// if (BaseObjectActor && BaseObjectActor->IsPushable()) return; 
	
		// Debug
		// FString Name = HitResult.GetActor()->GetActorNameOrLabel();
		// //UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *Name);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		
		// Play SFX
		if(BaseObjectActor)
		{
			BaseObjectActor->PlayInteractionSFX();
			BaseObjectActor->PlayInteractionVFX();
		}
			
		
		// Grab
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
		isGrabbing = true;
	}
}

// void UGrabber::PushPull()
// {
// 	if(CheckLineTraceForPush(HitResult))
// 	{
// 		ABaseObjectActor* BaseObjectActor = Cast<ABaseObjectActor>(HitResult.GetActor());
// 		// If its not a pushable object, ignore it
//
// 		if (!BaseObjectActor) return;
// 		if (BaseObjectActor && !BaseObjectActor->IsPushable()) return;
// 	
// 		if(!BaseObjectActor->IsPushableRange())
// 		{
// 			if(PhysicsHandle->GetGrabbedComponent())
// 			{
// 				isPushing = false;
// 				PhysicsHandle->ReleaseComponent();
// 			}
// 			return;
// 		}
// 		if(PhysicsHandle->GetGrabbedComponent()) return;
// 		
// 		// Debug
// 		// FString Name = HitResult.GetActor()->GetActorNameOrLabel();
// 		// UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *Name);
// 		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Blue, false, 5);
// 		
// 		if(BaseObjectActor)
// 		{
// 			BaseObjectActor->PlayInteractionVFX();
// 			BaseObjectActor->PlayInteractionSFX();
// 			BaseObjectActor->SetTransparentMaterial();
// 			
// 			// Push
// 			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
// 			HitComponent->WakeAllRigidBodies();
// 			PhysicsHandle->GrabComponentAtLocation(
// 				HitComponent,
// 				NAME_None,
// 				HitResult.ImpactPoint
// 			);
// 		}
// 		isPushing = true;
// 	}
// }

// void UGrabber::StopPushPull()
// {
// 	if(!isPushing) return;
// 	if(!PhysicsHandle->GetGrabbedComponent()) return;
// 	
// 	// If its not a pushable object, ignore it
// 	ABaseObjectActor* BaseObjectActor = Cast<ABaseObjectActor>(HitResult.GetActor());
// 	if (!BaseObjectActor) return;
// 	if (BaseObjectActor && !BaseObjectActor->IsPushable()) return;
// 	
// 	UE_LOG(LogTemp, Display, TEXT(" Stop Pushing"));
// 	if(PhysicsHandle->GetGrabbedComponent())
// 	{
// 		if(BaseObjectActor)
// 		{
// 			// Play SFX
// 			BaseObjectActor->PlayQuitInteractionSFX();
//
// 			// Stop push or pull
// 			HitResult.GetComponent()->WakeAllRigidBodies();
// 			HitResult.GetComponent()->SetPhysicsLinearVelocity(FVector::Zero());
// 			PhysicsHandle->ReleaseComponent();
// 			
// 			// Make the movable object return to default color
// 			BaseObjectActor->SetDefaultMaterial();
// 		}
// 	}
// 	isPushing = false;
// }

// bool UGrabber::GetIsPushing() const
// {
// 	if(isPushing) return true;
// 	return false;
// }
//
bool UGrabber::GetIsGrabbing() const
{
	if(isGrabbing) return true;
	return false;
}




