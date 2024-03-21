// Puzzle Mage by Arctic Moose Games


#include "LevelDataAsset.h"

int32 ULevelDataAsset::GetChapterIndex() const
{
	return ChapterIndex;
}

int32 ULevelDataAsset::GetLevelIndex() const
{
	return LevelIndex;
}

FString ULevelDataAsset::GetLevelName() const
{
	return LevelName;
}

UTexture2D* ULevelDataAsset::GetLevelIcon() const
{
	return LevelIcon.LoadSynchronous();
}

UTexture2D* ULevelDataAsset::GetLockedLevelIcon() const
{
	return LockedLevelIcon.LoadSynchronous();
}

TSoftObjectPtr<UWorld> ULevelDataAsset::GetMapReference()
{
	return MapReference;
}

bool ULevelDataAsset::GetIsLocked() const
{
	return bIsLocked;
}

void ULevelDataAsset::SetChapterIndex(int32 value)
{
	ChapterIndex = value;
}

void ULevelDataAsset::SetLevelIndex(int32 value)
{
	LevelIndex = value;
}

void ULevelDataAsset::SetLevelIsLocked(bool value)
{
	bIsLocked = value;
}

void ULevelDataAsset::Reset()
{
	bIsLocked = true;
}
