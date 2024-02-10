// Puzzle Mage by Arctic Moose Games


#include "MainMenuScreenUI.h"

#include "CustomButton.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
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
	//CreditsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnCreditsButtonClicked);
	//OptionsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnOptionsButtonClicked);
	QuitButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenUI::OnQuitButtonClicked);
}

void UMainMenuScreenUI::OnNewGameButtonClicked()
{
	const UWorld* World = GetWorld();

	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(World, "Cp1");
}

void UMainMenuScreenUI::OnQuitButtonClicked()
{
	UMyBlueprintFunctionLibrary::QuitGame(GetWorld(), false);
}
