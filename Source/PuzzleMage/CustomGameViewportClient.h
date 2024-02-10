// Puzzle Mage by Acthic Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "CustomGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UCustomGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	virtual void PostRender(UCanvas* Canvas) override;

	virtual void Fade(const bool ToBlack);

private:
	void DrawScreenFade(UCanvas* Canvas);

private:
	bool bFading : 1;
	bool bToBlack : 1;
	float FadeAlpha;
	float FadeStartTime;
	float FadeDuration = 2.0f;
};
