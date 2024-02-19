// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> LevelIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> MapReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;
};

USTRUCT(BlueprintType)
struct FChapterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ChapterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ChapterIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLevelData> Levels;
};

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChapterData> Chapters;

	UFUNCTION()
	void SetChapterIsLocked(int32 ChapterIndex, bool bIsLocked);

	UFUNCTION()
	void SetLevelIsLocked(int32 ChapterIndex, int32 LevelIndex, bool bIsLocked);
};
