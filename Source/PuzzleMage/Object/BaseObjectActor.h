// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BaseObjectActor.generated.h"

class USoundCue;
class UBoxComponent;

UCLASS()
class PUZZLEMAGE_API ABaseObjectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObjectActor();
	
	//Collision Checker
	UPROPERTY(EditAnywhere, Category="Collider")
	UBoxComponent* BoxComponent;

	//Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Static Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	// Particle Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Particle System Component")
	UNiagaraComponent* ParticleSystemComponent;
	
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// SFX
	UFUNCTION(BlueprintCallable)
	void PlayInteractionSFX();
	
	UFUNCTION(BlueprintCallable)
	void PlayQuitInteractionSFX();

	// VFX
	UFUNCTION(BlueprintCallable)
	void PlayInteractionVFX();

	UFUNCTION(BlueprintCallable)
	void StopInteractionVFX();


	UFUNCTION(BlueprintCallable, Category = "Pushable")
	bool IsPushable() { return bIsPushable; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category="SFX")
	TObjectPtr<USoundCue> InteractionSoundQue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category="SFX")
	TObjectPtr<USoundCue> QuitInteractionSoundQue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pushable")
	bool bIsPushable;

private:

};
