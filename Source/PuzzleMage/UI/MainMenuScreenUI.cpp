// Puzzle Mage by Arctic Moose Games


#include "MainMenuScreenUI.h"

#include "CustomButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/MyGameInstance.h"

void UMainMenuScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (GameInstance->HasSaveData())
		{
			ContinueButton->SetVisibility(ESlateVisibility::Visible);
			ContinueButton->SetPlayFirstFocusSound(false);
			ContinueButton->SetIsFocused(false);
			ContinueButton->GetButton()->SetFocus();
		}
		else
		{
			ContinueButton->SetVisibility(ESlateVisibility::Collapsed);
			NewGameButton->SetPlayFirstFocusSound(false);
			NewGameButton->SetIsFocused(false);
			NewGameButton->GetButton()->SetFocus();
		}
	}

	BindOnClickedEvents();
}

bool UMainMenuScreenUI::Initialize()
{
	return Super::Initialize();
}

void UMainMenuScreenUI::BindOnClickedEvents()
{
	ContinueButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnContinueButtonClicked);
	NewGameButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnNewGameButtonClicked);
	SelectLevelButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnSelectLevelButtonClicked);
	AchievementsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnAchievementsButtonClicked);
	CreditsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnCreditsButtonClicked);
	OptionsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnOptionsButtonClicked);
	QuitButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnQuitButtonClicked);
	ControlsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnControlsButtonClicked);
}

void UMainMenuScreenUI::OnContinueButtonClicked()
{
	const UWorld* World = GetWorld();
	if (const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World)))
	{
		if (ULevelDataAsset* LastLevelDataAsset = GameInstance->GetLastUnlockedLevelDataAsset())
		{
			UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(World, LastLevelDataAsset);
		}
	}
}

void UMainMenuScreenUI::OnNewGameButtonClicked()
{
	const UWorld* World = GetWorld();
	if (UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World)))
	{
		GameInstance->ResetGameData();
		ULevelDataAsset* FirstLevelDataAsset = GameInstance->GetFirstLevelDataAsset();
		UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(World, FirstLevelDataAsset);
	}
}

void UMainMenuScreenUI::OnSelectLevelButtonClicked()
{
	const UWorld* World = GetWorld();
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(World, "LevelSelectScreen", false);
}

void UMainMenuScreenUI::OnCreditsButtonClicked()
{
	const UWorld* World = GetWorld();
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(World, "CreditScreen", false);
}

void UMainMenuScreenUI::OnOptionsButtonClicked()
{
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(GetWorld(), "OptionsScreen", false);
}

void UMainMenuScreenUI::OnQuitButtonClicked()
{
	UMyBlueprintFunctionLibrary::QuitGame(GetWorld(), false);
}

void UMainMenuScreenUI::OnControlsButtonClicked()
{
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(GetWorld(), "ControlsScreen", false);

}
void UMainMenuScreenUI::OnAchievementsButtonClicked()
{
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(GetWorld(), "AchievementsScreen", false);
}
