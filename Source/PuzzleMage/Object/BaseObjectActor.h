// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SphereComponent.h"
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

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Movable Object Properties")
	TObjectPtr<UMaterialInterface> TransparentMaterial;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Movable Object Properties")
	TObjectPtr<UMaterialInterface> DefaultMaterial;

	// Particle Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Particle System Component")
	UNiagaraComponent* ParticleSystemComponent;

	// Post Process for Highlighting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Post Process Component")
	UPostProcessComponent* PostProcessComponent;
	
	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndBoxOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
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

	// Highlighting
	UFUNCTION(BlueprintCallable)
	void Highlighting();

	UFUNCTION(BlueprintCallable)
	void UnHighlighting();

	//For movable object
	UFUNCTION(BlueprintCallable, Category = "Pushable")
	bool IsPushable() { return bIsPushable; }
	
	UFUNCTION(BlueprintCallable, Category = "Pushable")
	bool IsPushableRange() {return bIsPushableRange; }
	
	UFUNCTION(BlueprintCallable, Category = "Pushable")
	void SetPushableRange(bool newValue);

	UFUNCTION(BlueprintCallable, Category = "Pushable")
	void SetTransparentMaterial();

	UFUNCTION(BlueprintCallable, Category = "Pushable")
	void SetDefaultMaterial();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Object Properties")
	float InitialZPosition;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category="SFX")
	TObjectPtr<USoundCue> InteractionSoundQue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category="SFX")
	TObjectPtr<USoundCue> QuitInteractionSoundQue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pushable")
	bool bIsPushable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PushableRange")
	bool bIsPushableRange;



private:

};
