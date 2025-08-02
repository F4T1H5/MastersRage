// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MRageGameplayAbility.h"
#include "MRageEnemyGameplayAbility.generated.h"

class AMastersRageEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMRageEnemyGameplayAbility : public UMRageGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	AMastersRageEnemyCharacter* GetEnemyCharacterFromActorInfo(); // Returns the enemy character from the actor info

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo(); // Returns the enemy combat component from the actor info

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:

	TWeakObjectPtr<AMastersRageEnemyCharacter> CachedMastersRageEnemyCharacter; // Cached reference to the enemy character

};
