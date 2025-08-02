// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UMRageGameplayAbility;
class UMRageAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:

	virtual void GiveToAbilitySystemComponent(UMRageAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UMRageGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UMRageGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UMRageGameplayAbility>>& InAbilitiesToGive, UMRageAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
