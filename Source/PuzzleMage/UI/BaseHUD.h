// Puzzle Mage by Acthic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "PauseScreenUI.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class APuzzleMageCharacter;
/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UPauseScreenUI* PauseWidget;

	UPROPERTY(EditAnywhere, Category="Pause Screen")
	TSubclassOf<UUserWidget> PauseWidgetClass;
	
	void SubscribePauseDelegate();
	
	void Pause();

	void UnPause();

	UFUNCTION(Exec)
	void SetControllerUIOnly();

	UFUNCTION(Exec)
	void SetControllerGameOnly();

	UFUNCTION(Exec)
	void SetControllerGameAndUIOnly();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category="Pause Screen")
	bool bIsDisplayed;

	APlayerController* PlayerController;


private:


	
	
	
};
