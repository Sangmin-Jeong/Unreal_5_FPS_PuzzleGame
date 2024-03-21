// Puzzle Mage by Arctic Moose Games


#include "PauseScreenUI.h"

#include "CustomButton.h"
#include "OptionsUI.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/MyGameInstance.h"

void UPauseScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	PauseMenuPanel->SetVisibility(ESlateVisibility::Visible);
	OptionsPanel->SetVisibility(ESlateVisibility::Hidden);

	OptionsButton->SetPlayFirstFocusSound(false);
	OptionsButton->SetIsFocused(false);
	OptionsButton->GetButton()->SetFocus();

	BindOnClickedEvents();
}

bool UPauseScreenUI::IsAtPauseMenu()
{
	return PauseMenuPanel->GetVisibility() == ESlateVisibility::Visible;
}

void UPauseScreenUI::ShowPauseMenuPanel()
{
	PauseMenuPanel->SetVisibility(ESlateVisibility::Visible);
	OptionsPanel->SetVisibility(ESlateVisibility::Hidden);
	
	OptionsButton->SetIsFocused(false);
	OptionsButton->GetButton()->SetFocus();

	// Save the game
	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld());
	if (GameInstance == nullptr) return;

	GameInstance->SaveGameData();
}

void UPauseScreenUI::BindOnClickedEvents()
{
	OptionsButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnOptionsButtonClicked);
	RestartButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnRestartButtonClicked);
	MainMenuButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnMainMenuButtonClicked);
	QuitButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnQuitButtonClicked);
}

void UPauseScreenUI::OnOptionsButtonClicked()
{
	PauseMenuPanel->SetVisibility(ESlateVisibility::Hidden);
	OptionsPanel->SetVisibility(ESlateVisibility::Visible);

	OptionsUI->SetFocusToWidget();
}

void UPauseScreenUI::OnRestartButtonClicked()
{
	const UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	UMyBlueprintFunctionLibrary::RestartLevelAfterDelay(World, false);
}

void UPauseScreenUI::OnMainMenuButtonClicked()
{
	UMyBlueprintFunctionLibrary::LoadLevelByNameAfterDelay(GetWorld(), "MainMenuScreen");
}

void UPauseScreenUI::OnQuitButtonClicked()
{
	UMyBlueprintFunctionLibrary::QuitGame(GetWorld(), false);
}
