// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API ULevelDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION()
	int32 GetChapterIndex() const;

	UFUNCTION()
	int32 GetLevelIndex() const;

	UFUNCTION()
	FString GetLevelName() const;

	UFUNCTION()
	UTexture2D* GetLevelIcon() const;

	UFUNCTION()
	UTexture2D* GetLockedLevelIcon() const;

	UFUNCTION()
	TSoftObjectPtr<UWorld> GetMapReference();

	UFUNCTION()
	bool GetIsLocked() const;

	UFUNCTION()
	void SetChapterIndex(int32 value);

	UFUNCTION()
	void SetLevelIndex(int32 value);
	
	UFUNCTION()
	void SetLevelIsLocked(bool value);

	UFUNCTION()
	void Reset();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ChapterIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 LevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> LevelIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> LockedLevelIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> MapReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsLocked;
};
