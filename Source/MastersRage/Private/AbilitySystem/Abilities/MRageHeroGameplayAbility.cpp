// Copyright Ahmet Fatih Senelmis


#include "AbilitySystem/Abilities/MRageHeroGameplayAbility.h"
#include "Characters/MastersRageHeroCharacter.h"
#include "Controllers/MastersRageHeroController.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "MastersRageGameplayTags.h"

AMastersRageHeroCharacter* UMRageHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedMastersRageHeroCharacter.IsValid())
    {
        CachedMastersRageHeroCharacter = Cast<AMastersRageHeroCharacter>(CurrentActorInfo->AvatarActor);

    }
    return CachedMastersRageHeroCharacter.IsValid() ? CachedMastersRageHeroCharacter.Get() : nullptr;
}

AMastersRageHeroController* UMRageHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedMastersRageHeroController.IsValid())
    {
        CachedMastersRageHeroController = Cast<AMastersRageHeroController>(CurrentActorInfo->PlayerController);
	}
	return CachedMastersRageHeroController.IsValid() ? CachedMastersRageHeroController.Get() : nullptr;
}

UHeroCombatComponent* UMRageHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

UHeroUIComponent* UMRageHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
}

FGameplayEffectSpecHandle UMRageHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
    check(EffectClass);

    FGameplayEffectContextHandle ContextHandle = GetMRageAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetMRageAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    // SetByCallerTagMagnitudes it is kind of a TMap key and value takes
    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        MastersRageGameplayTags::Shared_SetByCaller_BaseDamage,
        InWeaponBaseDamage
    );

    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
    }

    return EffectSpecHandle;
}

bool UMRageHeroGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
    check(InCooldownTag.IsValid());

    FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

    TArray<TPair<float, float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

    if (!TimeRemainingAndDuration.IsEmpty())
    {
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;

		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
    }

	return RemainingCooldownTime > 0.0f;
}
