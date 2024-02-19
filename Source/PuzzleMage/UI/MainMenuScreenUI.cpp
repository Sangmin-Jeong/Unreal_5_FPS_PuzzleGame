// Puzzle Mage by Arctic Moose Games


#include "MainMenuScreenUI.h"

#include "CustomButton.h"
#include "Components/Button.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"

void UMainMenuScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton->SetPlayFirstFocusSound(false);
	NewGameButton->SetIsFocused(false);
	NewGameButton->GetButton()->SetFocus();

	BindOnClickedEvents();
}

bool UMainMenuScreenUI::Initialize()
{
	return Super::Initialize();
}

void UMainMenuScreenUI::BindOnClickedEvents()
{
	NewGameButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnNewGameButtonClicked);
	//LoadGameButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnLoadGameButtonClicked);
	//AchievementsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnAchievementsButtonClicked);
	CreditsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnCreditsButtonClicked);
	//OptionsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnOptionsButtonClicked);
	QuitButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnQuitButtonClicked);
	ControlsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnControlsButtonClicked);
}

void UMainMenuScreenUI::OnNewGameButtonClicked()
{
	const UWorld* World = GetWorld();
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(World, "LevelSelectScreen",false);
}

void UMainMenuScreenUI::OnCreditsButtonClicked()
{
	const UWorld* World = GetWorld();
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(World, "CreditScreen",false);
}

void UMainMenuScreenUI::OnQuitButtonClicked()
{
	UMyBlueprintFunctionLibrary::QuitGame(GetWorld(), false);
}

void UMainMenuScreenUI::OnControlsButtonClicked()
{
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(GetWorld(), "ControlsScreen",false);

}
