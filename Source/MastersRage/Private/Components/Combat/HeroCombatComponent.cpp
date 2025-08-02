// Copyright Ahmet Fatih Senelmis


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/MastersRageHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MastersRageGameplayTags.h"

#include "MastersRageDebugHelper.h"

AMastersRageHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AMastersRageHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AMastersRageHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
    return Cast<AMastersRageHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquipWeaponDamageAtLevel(float InLevel) const
{
    return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
		return; // Already hit this actor so that we don't apply damage multiple times per once attack
    }

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        MastersRageGameplayTags::Shared_Event_MeleeHit,
        Data
    );

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        MastersRageGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
    );
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        MastersRageGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}
