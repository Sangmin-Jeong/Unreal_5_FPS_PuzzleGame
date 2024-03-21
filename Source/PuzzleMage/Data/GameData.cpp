// Puzzle Mage by Arctic Moose Games


#include "GameData.h"

#include "ChapterDataAsset.h"
#include "LevelDataAsset.h"
#include "PuzzleMage/MyGameInstance.h"

TArray<UChapterDataAsset*> UGameData::GetChapterDataAssets() const
{
	return Chapters;
}

UChapterDataAsset* UGameData::GetChapterDataAsset(int32 ChapterIndex) const
{
	return Chapters.IsValidIndex(ChapterIndex) ? Chapters[ChapterIndex] : nullptr;
}

TArray<ULevelDataAsset*> UGameData::GetLevelDataAssets(int32 ChapterIndex) const
{
	return Chapters.IsValidIndex(ChapterIndex) ? Chapters[ChapterIndex]->GetLevelDataAssets() : TArray<ULevelDataAsset*>();
}

void UGameData::SetChapterIsLocked(int32 ChapterIndex, bool bIsLocked)
{
	if (Chapters.IsValidIndex(ChapterIndex))
	{
		Chapters[ChapterIndex]->SetChapterIsLocked(bIsLocked);
	}
}

void UGameData::SetLevelIsLocked(int32 ChapterIndex, int32 LevelIndex, bool bIsLocked)
{
	if (Chapters.IsValidIndex(ChapterIndex) && Chapters[ChapterIndex]->GetLevelDataAssets().IsValidIndex(LevelIndex))
	{
		Chapters[ChapterIndex]->SetLevelIsLocked(LevelIndex, bIsLocked);
	}
}

FString UGameData::GetSaveSlotName() const
{
	return SaveSlotName;
}

int32 UGameData::GetUserIndex() const
{
	return UserIndex;
}

float UGameData::GetMasterVolume() const
{
	return MasterVolume;
}

float UGameData::GetMusicVolume() const
{
	return MusicVolume;
}

float UGameData::GetSFXVolume() const
{
	return SFXVolume;
}

void UGameData::SetAudioVolume(EAudioType AudioType, float Volume)
{
	switch (AudioType)
	{
		case EAudioType::Master:
		{
			MasterVolume = Volume;
			break;
		}
		case EAudioType::Music:
		{
			MusicVolume = Volume;
			break;
		}
		case EAudioType::SFX:
		{
			SFXVolume = Volume;
			break;
		}
	}
}


void UGameData::Reset()
{
	for (UChapterDataAsset* ChapterDataAsset : Chapters)
	{
		ChapterDataAsset->Reset();
	}

	for (int i = 0; i < Chapters.Num(); i++)
	{
		if (i == 0)
		{
			Chapters[i]->SetChapterIsLocked(false);

			for (int j = 0; j < Chapters[i]->GetLevelDataAssets().Num(); j++)
			{
				if (j == 0)
				{
					Chapters[i]->SetLevelIsLocked(j, false);
				}
			}
		}
	}
}
