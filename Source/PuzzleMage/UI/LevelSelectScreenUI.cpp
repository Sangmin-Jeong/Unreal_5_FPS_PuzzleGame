// Puzzle Mage by Arctic Moose Games


#include "LevelSelectScreenUI.h"

#include "LevelButton.h"
#include "Components/Button.h"


void ULevelSelectScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	Chapter1Button->SetFocus();

	BindOnClickedEvents();
}

void ULevelSelectScreenUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void ULevelSelectScreenUI::BindOnClickedEvents()
{
	Level1Button->SetButtonOnClick();
	Level2Button->SetButtonOnClick();
	Level3Button->SetButtonOnClick();
	Level4Button->SetButtonOnClick();
	Level5Button->SetButtonOnClick();
}