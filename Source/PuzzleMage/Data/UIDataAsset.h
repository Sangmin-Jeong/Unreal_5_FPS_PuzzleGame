// Puzzle Mage by Arctic Moose Games

#pragma once

UENUM()
enum EIconType
{
	Select,
	Back,
	TabLeft,
	TabRight
};

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UUIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon(EIconType IconType) const;

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetControlSchemeImage() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> SelectIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> BackIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> TabLeftIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> TabRightIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Controls", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> ControlSchemeImage;
};
