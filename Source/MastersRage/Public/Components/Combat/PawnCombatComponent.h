// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AMastersRageWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:

	// Register a weapon that has been spawned in the world
	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AMastersRageWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	// Allows us to retrieve a specific weapon by its tag
	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	AMastersRageWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "MastersRage|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	AMastersRageWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	TArray<AActor*> OverlappedActors;

private:

	TMap<FGameplayTag, AMastersRageWeaponBase*> CharacterCarriedWeaponMap;

};
