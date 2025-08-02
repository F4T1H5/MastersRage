// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MastersRageTypes/MastersRageEnumTypes.h"
#include "MastersRageFunctionLibrary.generated.h"

class UMRageAbilitySystemComponent;
class UPawnCombatComponent;
struct FScalableFloat;
class UMastersRageGameInstance;
/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Purpose is to help us to retrieve the MRage Ability System Component from the actor that filled in.
	static UMRageAbilitySystemComponent* NativeGetMRageASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EMastersRageConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EMastersRageValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "MastersRage|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "MastersRage|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "MastersRage|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "MastersRage|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
		float& OutRemainingTime, EMastersRageCountDownActionInput CountDownInput,
		UPARAM(DisplayName = "Output") EMastersRageCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category = "MastersRage|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UMastersRageGameInstance* GetMastersRageGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EMastersRageInputMode InInputMode);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary")
	static void SaveCurrentGameDifficulty(EMastersRageGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(EMastersRageGameDifficulty& OutSavedDifficulty);
};
