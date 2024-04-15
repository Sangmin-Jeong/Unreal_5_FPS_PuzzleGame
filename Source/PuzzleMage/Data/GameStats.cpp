// Puzzle Mage by Arctic Moose Games

#pragma once

#include "GameStats.h"

void UGameStats::IncrementTotalDoorsOpened()
{
	TotalDoorsOpened++;
}

int32 UGameStats::GetTotalDoorsOpened() const
{
	return TotalDoorsOpened;
}

void UGameStats::SetTotalLevelsUnlocked(const int32 Value)
{
	TotalLevelsUnlocked = Value;
}

int32 UGameStats::GetTotalLevelsUnlocked() const
{
	return TotalLevelsUnlocked;
}

void UGameStats::IncrementTotalJump()
{
	TotalJump++;
}

int32 UGameStats::GetTotalJump() const
{
	return TotalJump;
}

void UGameStats::IncrementTotalDeath()
{
	TotalDeath++;
}

int32 UGameStats::GetTotalDeath() const
{
	return TotalDeath;
}
