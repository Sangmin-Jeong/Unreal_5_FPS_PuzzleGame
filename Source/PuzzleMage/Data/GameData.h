// Puzzle Mage by Arctic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "GameStats.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

enum class EAudioType;
/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UGameData();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UChapterDataAsset*> Chapters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 UserIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MasterVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SFXVolume;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UGameStats* GameStats;

public:
	UFUNCTION()
	TArray<class UChapterDataAsset*> GetChapterDataAssets() const;

	UFUNCTION()
	class UChapterDataAsset* GetChapterDataAsset(int32 ChapterIndex) const;

	UFUNCTION()
	TArray<class ULevelDataAsset*> GetLevelDataAssets(int32 ChapterIndex) const;
	
	UFUNCTION()
	void SetChapterIsLocked(int32 ChapterIndex, bool bIsLocked);

	UFUNCTION()
	void SetLevelIsLocked(int32 ChapterIndex, int32 LevelIndex, bool bIsLocked);

	UFUNCTION()
	FString GetSaveSlotName() const;

	UFUNCTION()
	int32 GetUserIndex() const;

	UFUNCTION()
	float GetMasterVolume() const;

	UFUNCTION()
	float GetMusicVolume() const;

	UFUNCTION()
	float GetSFXVolume() const;

	UFUNCTION()
	void SetAudioVolume(EAudioType AudioType, float Volume);

	UFUNCTION(BlueprintCallable)
	class UGameStats* GetGameStats() const;

	UFUNCTION()
	void UpdateTotalLevelsCompleted();

	UFUNCTION()
	int32 CalculateTotalLevelsCompleted();
	
	UFUNCTION()
	void Reset();
};
