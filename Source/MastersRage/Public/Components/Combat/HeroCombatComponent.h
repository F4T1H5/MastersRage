// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AMastersRageHeroWeapon;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	AMastersRageHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	AMastersRageHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	float GetHeroCurrentEquipWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
