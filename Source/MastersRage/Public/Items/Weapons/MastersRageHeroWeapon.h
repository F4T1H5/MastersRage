// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/MastersRageWeaponBase.h"
#include "MastersRageTypes/MastersRageStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "MastersRageHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API AMastersRageHeroWeapon : public AMastersRageWeaponBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FMastersRageHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:

	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

};
