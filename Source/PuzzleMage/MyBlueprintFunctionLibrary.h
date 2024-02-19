// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class EStatusReturnType : uint8
{
	Success UMETA(DisplayName = "On Success"),
	Fail UMETA(DisplayName = "On Failure")
};

/**
 * 
 */
UCLASS()
class PUZZLEMAGE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary")
	static int32 GetLastMaxPlayerIndex();

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void SetActiveControllerId(const UObject* WorldContextObject, int32 ControllerId);

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static int32 GetActiveControllerId(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void RemoveAllPlayers(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static class APlayerController* GetActivePlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static class ACharacter* GetActivePlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject", ExpandEnumAsExecs = "Status"))
	static void SetupActiveControllerId(const UObject* WorldContextObject, FKey Key, EStatusReturnType& Status);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void UnlockAchievement(const UObject* WorldContextObject, FName AchievementName);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void AddAchievementProgress(const UObject* WorldContextObject, FName AchievementName, float Progress);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void SetAchievementProgress(const UObject* WorldContextObject, FName AchievementName, float Progress);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void LoadLevelByNameAfterDelay(const UObject* WorldContextObject, FName MapName, bool EnableLoadingScreen = true ,float Delay = 0.2f);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static FName GetCurrentMapName(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void QuitGame(const UObject* WorldContextObject, bool bIgnorePlatformRestrictions = false);
};