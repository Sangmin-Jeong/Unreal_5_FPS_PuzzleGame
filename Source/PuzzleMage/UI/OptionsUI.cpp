// Puzzle Mage by Arctic Moose Games


#include "OptionsUI.h"

#include "FocusableSlider.h"
#include "Components/Slider.h"
#include "PuzzleMage/MyBlueprintFunctionLibrary.h"
#include "PuzzleMage/MyGameInstance.h"

void UOptionsUI::NativeConstruct()
{
	Super::NativeConstruct();

	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld());
	if (GameInstance == nullptr) return;
	
	InitializeSliders(GameInstance);
}

void UOptionsUI::SetFocusToWidget()
{
	SetInitialVolumes();
	
	MasterVolumeSlider->SetIsFocused(false);
	MasterVolumeSlider->GetSlider()->SetFocus();
}

void UOptionsUI::InitializeSliders(const UMyGameInstance* GameInstance)
{
	MasterVolumeSlider->SetPlayFirstFocusSound(false);

	SetInitialVolumes();

	MasterVolumeSlider->GetSlider()->OnValueChanged.AddDynamic(this, &UOptionsUI::OmMasterVolumeChanged);
	MusicVolumeSlider->GetSlider()->OnValueChanged.AddDynamic(this, &UOptionsUI::OnMusicVolumeChanged);
	SFXVolumeSlider->GetSlider()->OnValueChanged.AddDynamic(this, &UOptionsUI::OnSFXVolumeChanged);
}

void UOptionsUI::SetInitialVolumes()
{
	const UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld());
	if (GameInstance == nullptr) return;
	
	MasterVolumeSlider->GetSlider()->SetValue(GameInstance->GetAudioVolume(EAudioType::Master));
	MusicVolumeSlider->GetSlider()->SetValue(GameInstance->GetAudioVolume(EAudioType::Music));
	SFXVolumeSlider->GetSlider()->SetValue(GameInstance->GetAudioVolume(EAudioType::SFX));
}

void UOptionsUI::OmMasterVolumeChanged(float Value)
{
	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld());
	if (GameInstance == nullptr) return;

	GameInstance->SetAudioVolume(EAudioType::Master, Value);
}

void UOptionsUI::OnMusicVolumeChanged(float Value)
{
	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld());
	if (GameInstance == nullptr) return;

	GameInstance->SetAudioVolume(EAudioType::Music, Value);
}

void UOptionsUI::OnSFXVolumeChanged(float Value)
{
	UMyGameInstance* GameInstance = UMyBlueprintFunctionLibrary::GetGameInstance(GetWorld());
	if (GameInstance == nullptr) return;

	GameInstance->SetAudioVolume(EAudioType::SFX, Value);
}
