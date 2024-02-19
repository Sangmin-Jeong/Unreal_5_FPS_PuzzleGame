// Puzzle Mage by Arctic Moose Games


#include "GameData.h"

void UGameData::SetChapterIsLocked(int32 ChapterIndex, bool bIsLocked)
{
	if (Chapters.IsValidIndex(ChapterIndex))
	{
		Chapters[ChapterIndex].bIsLocked = bIsLocked;
	}
}

void UGameData::SetLevelIsLocked(int32 ChapterIndex, int32 LevelIndex, bool bIsLocked)
{
	if (Chapters.IsValidIndex(ChapterIndex) && Chapters[ChapterIndex].Levels.IsValidIndex(LevelIndex))
	{
		Chapters[ChapterIndex].Levels[LevelIndex].bIsLocked = bIsLocked;
	}
}
