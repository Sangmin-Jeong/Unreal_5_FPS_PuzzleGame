// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObjectActor.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include "PuzzleMage/PuzzleMageCharacter.h"
#include "PuzzleMage/Component/Grabber.h"

// Sets default values
ABaseObjectActor::ABaseObjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Static Mesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMeshComponent);
	
	// Collider
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(GetRootComponent());

	// Set Particle System
	ParticleSystemComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle System Component"));
	ParticleSystemComponent->SetupAttachment(GetRootComponent());

	// Set Post Process
	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Process Component"));
	PostProcessComponent->SetupAttachment(GetRootComponent());
	
	// bIsPushable = false;
	// bIsPushableRange = false;
}

// Called when the game starts or when spawned
void ABaseObjectActor::BeginPlay()
{
	Super::BeginPlay();
	// BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseObjectActor::OnBoxOverlap);
	// BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseObjectActor::EndBoxOverlap);
	
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetMassScale(NAME_None,5);

	InitialZPosition = GetActorLocation().Z - 2.0f;

	UnHighlighting();
}

void ABaseObjectActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(InitialZPosition > GetActorLocation().Z)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, InitialZPosition));
	}
}

void ABaseObjectActor::PlayInteractionSFX()
{
	if(InteractionSoundQue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InteractionSoundQue);
	}
}

void ABaseObjectActor::PlayQuitInteractionSFX()
{
	if(QuitInteractionSoundQue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), QuitInteractionSoundQue);
	}
}

void ABaseObjectActor::PlayInteractionVFX()
{
	if(ParticleSystemComponent)
	{
		ParticleSystemComponent->Activate(true);
	}
}

void ABaseObjectActor::StopInteractionVFX()
{
	if(ParticleSystemComponent)
	{
		ParticleSystemComponent->Activate(false);
	}
}

void ABaseObjectActor::Highlighting()
{
	PostProcessComponent->bEnabled = true;
	StaticMeshComponent->SetRenderCustomDepth(true);
}

void ABaseObjectActor::UnHighlighting()
{
	PostProcessComponent->bEnabled = false;
	StaticMeshComponent->SetRenderCustomDepth(false);
}

// void ABaseObjectActor::OnBoxOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
//                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	AActor* Actor = Cast<APuzzleMageCharacter>(OtherActor);
// 	if(Actor)
// 	{
// 		//UE_LOG(LogTemp, Display, TEXT("PLAYER IN     - Box!!!!"));
// 	
// 		if(IsPushable())
// 		{
// 			SetPushableRange(true);
// 		}
// 	}
// }

// void ABaseObjectActor::EndBoxOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	AActor* Actor = Cast<APuzzleMageCharacter>(OtherActor);
// 	if(Actor)
// 	{
// 		//UE_LOG(LogTemp, Display, TEXT("PLAYER OUT    - Box!!!!"));
// 		
// 		if(IsPushable())
// 		{
// 			SetPushableRange(false);
// 		}
// 	}
// }

// void ABaseObjectActor::SetPushableRange(bool newValue)
// {
// 	bIsPushableRange = newValue;
//
// 	if(bIsPushableRange)
// 	UE_LOG(LogTemp, Display, TEXT("Within PushableRange "));
//
// 	if(!bIsPushableRange)
// 		UE_LOG(LogTemp, Display, TEXT("Out of PushableRange "));
// }
// void ABaseObjectActor::SetTransparentMaterial()
// {
// 	StaticMeshComponent->SetMaterial(0,TransparentMaterial);
// }
//
// void ABaseObjectActor::SetDefaultMaterial()
// {
// 	StaticMeshComponent->SetMaterial(0,DefaultMaterial);
// }





