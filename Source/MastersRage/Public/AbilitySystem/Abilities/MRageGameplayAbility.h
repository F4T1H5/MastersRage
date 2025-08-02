// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MastersRageTypes/MastersRageEnumTypes.h"
#include "MRageGameplayAbility.generated.h"

class UPawnCombatComponent;
class UMRageAbilitySystemComponent;

UENUM(BlueprintType)
enum class EMRageAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMRageGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface.	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface.	

	UPROPERTY(EditDefaultsOnly, Category = "WarriorAbility")
	EMRageAbilityActivationPolicy AbilityActivationPolicy = EMRageAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "MastersRage|Ability")
	UMRageAbilitySystemComponent* GetMRageAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "MastersRage|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EMastersRageSuccessType& OutSuccessType);
};
