// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameStats.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UGameStats : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void IncrementTotalDoorsOpened();

	UFUNCTION()
	int32 GetTotalDoorsOpened() const;

	UFUNCTION(BlueprintCallable)
	void SetTotalLevelsUnlocked(int32 Value);

	UFUNCTION()
	int32 GetTotalLevelsUnlocked() const;

	UFUNCTION(BlueprintCallable)
	void IncrementTotalJump();

	UFUNCTION()
	int32 GetTotalJump() const;

	UFUNCTION(BlueprintCallable)
	void IncrementTotalDeath();

	UFUNCTION()
	int32 GetTotalDeath() const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 TotalDoorsOpened;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 TotalLevelsUnlocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 TotalJump;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 TotalDeath;
};