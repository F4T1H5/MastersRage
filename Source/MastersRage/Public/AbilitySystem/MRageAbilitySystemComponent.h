// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MastersRageTypes/MastersRageStructTypes.h"
#include "MRageAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMRageAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FMastersRageHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FMastersRageHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Ability")
	void RemovedGrantHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
	
	UFUNCTION(BlueprintCallable, Category = "MastersRage|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
