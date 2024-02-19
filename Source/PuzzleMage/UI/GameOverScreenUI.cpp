// Puzzle Mage by Arctic Moose Games


#include "GameOverScreenUI.h"

#include "CustomButton.h"
#include "Components/Button.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"

void UGameOverScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAgainButton->SetPlayFirstFocusSound(false);
	PlayAgainButton->SetIsFocused(false);
	PlayAgainButton->GetButton()->SetFocus();

	BindOnClickedEvents();
}

void UGameOverScreenUI::BindOnClickedEvents()
{
	//PlayAgainButton->GetButton()->OnClicked.AddDynamic(this, &UGameOverScreenUI::OnPlayAgainButtonClicked);
	//MainMenuButton->GetButton()->OnClicked.AddDynamic(this, &UGameOverScreenUI::OnMainMenuButtonClicked);
	QuitButton->GetButton()->OnClicked.AddDynamic(this, &UGameOverScreenUI::OnQuitButtonClicked);
}

void UGameOverScreenUI::OnQuitButtonClicked()
{
	UMyBlueprintFunctionLibrary::QuitGame(GetWorld(), false);
}
