// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MRageGameplayAbility.h"
#include "MRageHeroGameplayAbility.generated.h"

class AMastersRageHeroCharacter;
class AMastersRageHeroController;
class UHeroCombatComponent;
class UHeroUIComponent;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMRageHeroGameplayAbility : public UMRageGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	AMastersRageHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	AMastersRageHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	UHeroUIComponent* GetHeroUIComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);

private:

	TWeakObjectPtr<AMastersRageHeroCharacter> CachedMastersRageHeroCharacter;
	TWeakObjectPtr<AMastersRageHeroController> CachedMastersRageHeroController;

};
