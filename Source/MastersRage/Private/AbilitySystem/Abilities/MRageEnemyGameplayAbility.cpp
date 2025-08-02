// Copyright Ahmet Fatih Senelmis


#include "AbilitySystem/Abilities/MRageEnemyGameplayAbility.h"
#include "Characters/MastersRageEnemyCharacter.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "MastersRageGameplayTags.h"

AMastersRageEnemyCharacter* UMRageEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedMastersRageEnemyCharacter.IsValid())
    {
        CachedMastersRageEnemyCharacter = Cast<AMastersRageEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedMastersRageEnemyCharacter.IsValid() ? CachedMastersRageEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UMRageEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UMRageEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
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

    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        MastersRageGameplayTags::Shared_SetByCaller_BaseDamage,
        InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
    );

    return EffectSpecHandle;
}
