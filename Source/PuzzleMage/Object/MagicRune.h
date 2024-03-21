// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "BaseObjectActor.h"
#include "PuzzleMage/PuzzleMageGameMode.h"
#include "BaseObjectActor.h"
#include "PuzzleMage/Door.h"
#include "MagicRune.generated.h"
/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API AMagicRune : public ABaseObjectActor
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	int MagicRuneIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	bool IsActive;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	TObjectPtr<UMaterialInterface> ActiveMaterial;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	TObjectPtr<UMaterialInterface> InactiveMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category="Magic Rune Properties")
	TObjectPtr<ADoor> Door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Achievement")
	bool MagicRuneAchievementUnlocked = false;
	
	UPROPERTY(BlueprintReadOnly)
	APuzzleMageGameMode* GameMode;

	

	void ResetMagicRune();

private:
	virtual void BeginPlay() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	



};
