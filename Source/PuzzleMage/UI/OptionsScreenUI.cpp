// Puzzle Mage by Arctic Moose Games


#include "OptionsScreenUI.h"

#include "FocusableSlider.h"
#include "OptionsUI.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/MyGameInstance.h"

void UOptionsScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	const UWorld* World = GetWorld();
	const UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(World);
	
	if (GameInstance == nullptr) return;
	
	UserSettings = GameInstance->GetGameUserSettings();

	OptionsUI->SetFocusToWidget();
}
