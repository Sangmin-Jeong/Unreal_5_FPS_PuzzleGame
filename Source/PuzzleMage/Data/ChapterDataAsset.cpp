// Puzzle Mage by Arctic Moose Games


#include "ChapterDataAsset.h"

#include "LevelDataAsset.h"

void UChapterDataAsset::PostLoad()
{
	Super::PostLoad();

	// Set each levels index to be the same as the index in the array
	for (int i = 0; i < Levels.Num(); i++)
	{
		Levels[i]->SetChapterIndex(ChapterIndex);
		Levels[i]->SetLevelIndex(i);
	}
}

TArray<ULevelDataAsset*> UChapterDataAsset::GetLevelDataAssets() const
{
	return Levels;
}

ULevelDataAsset* UChapterDataAsset::GetLevelDataAsset(int32 LevelIndex) const
{
	return Levels[LevelIndex];
}

FString& UChapterDataAsset::GetChapterName()
{
	return ChapterName;
}

bool UChapterDataAsset::GetIsLocked()
{
	return bIsLocked;
}

void UChapterDataAsset::SetChapterIsLocked(bool value)
{
	bIsLocked = value;
}

void UChapterDataAsset::SetLevelIsLocked(int32 LevelIndex, bool value)
{
	if (Levels.IsValidIndex(LevelIndex))
	{
		Levels[LevelIndex]->SetLevelIsLocked(value);
	}
}

UTexture2D* UChapterDataAsset::GetChapterIcon()
{
	return ChapterIcon.LoadSynchronous();
}

UTexture2D* UChapterDataAsset::GetLockedChapterIcon() const
{
	return LockedChapterIcon.LoadSynchronous();
}

void UChapterDataAsset::Reset()
{
	bIsLocked = true;
	
	for (ULevelDataAsset* LevelDataAsset : Levels)
	{
		LevelDataAsset->Reset();
	}
}
