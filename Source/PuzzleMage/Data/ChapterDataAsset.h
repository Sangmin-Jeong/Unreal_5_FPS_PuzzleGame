// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChapterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UChapterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual void PostLoad() override;
	
	UFUNCTION()
	TArray<class ULevelDataAsset*> GetLevelDataAssets() const;

	UFUNCTION()
	ULevelDataAsset* GetLevelDataAsset(int32 LevelIndex) const;

	UFUNCTION()
	FString& GetChapterName();

	UFUNCTION()
	bool GetIsLocked();
	
	UFUNCTION()
	void SetChapterIsLocked(bool value);

	UFUNCTION()
	void SetLevelIsLocked(int32 LevelIndex, bool value);

	UFUNCTION()
	UTexture2D* GetChapterIcon();
	
	UFUNCTION()
	UTexture2D* GetLockedChapterIcon() const;
	
	UFUNCTION()
	void Reset();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ChapterIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ChapterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> ChapterIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> LockedChapterIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class ULevelDataAsset*> Levels;
	
};
