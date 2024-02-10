// Puzzle Mage by Arctic Moose Games


#include "PauseScreenUI.h"

#include "CustomButton.h"
#include "Components/Button.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"

void UPauseScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	OptionsButton->SetPlayFirstFocusSound(false);
	OptionsButton->SetIsFocused(false);
	OptionsButton->GetButton()->SetFocus();

	BindOnClickedEvents();
}

void UPauseScreenUI::BindOnClickedEvents()
{
	//OptionsButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnOptionsButtonClicked);
	//RestartButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnRestartButtonClicked);
	//MainMenuButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnMainMenuButtonClicked);
	QuitButton->GetButton()->OnClicked.AddDynamic(this, &UPauseScreenUI::OnQuitButtonClicked);
}

void UPauseScreenUI::OnQuitButtonClicked()
{
	UMyBlueprintFunctionLibrary::QuitGame(GetWorld(), false);
}
