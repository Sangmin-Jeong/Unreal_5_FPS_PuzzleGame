// Puzzle Mage by Arctic Moose Games


#include "MagicRune.h"

#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/PuzzleMageCharacter.h"




void AMagicRune::BeginPlay()
{
	GameMode = Cast<APuzzleMageGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->MagicRuneActors.Add(this);
		GameMode->Door = Door;
	}
}

void AMagicRune::ResetMagicRune()
{
	IsActive = false;
	StaticMeshComponent->SetMaterial(0,InactiveMaterial);
	PlayQuitInteractionSFX();
}

void AMagicRune::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(!MagicRuneAchievementUnlocked)
	{
		UMyBlueprintFunctionLibrary::UnlockAchievement(this,"MagicRune");
		MagicRuneAchievementUnlocked = true;
	}
	
	if(IsActive) return;
		
	AActor* Actor = Cast<APuzzleMageCharacter>(OtherActor);
	if(Actor)
	{
		if(MagicRuneIndex == GameMode->NextMagicRuneIndex)
		{
			// 1. Set Next Magic Rune
			GameMode->NextMagicRuneIndex++;
			// 2. Set Activated , Change Material
			IsActive = true;
			StaticMeshComponent->SetMaterial(0,ActiveMaterial);
			// 3. Play Sound , Particle
			PlayInteractionSFX();
			PlayInteractionVFX();
			// 4. Check if is All Magic Rune activated
			if(MagicRuneIndex == GameMode->MagicRuneActors.Num() - 1)
			{
				GameMode->bIsAllMagicRuneActivated = true;
				GameMode->OpenDoor();
			}
		}
		else
		{
			//1. Reset All Magic Rune
			for (AActor* actor : GameMode->MagicRuneActors)
			{
				Cast<AMagicRune>(actor)->ResetMagicRune();
			}
			//2. Reset Next Magic Rune
			GameMode->NextMagicRuneIndex = 0;
			//3. Reload the current map
			const UWorld* World = GetWorld();
			if (World == nullptr) return;
			
			UMyBlueprintFunctionLibrary::RestartLevelAfterDelay(World, false);
		}
	}
}
