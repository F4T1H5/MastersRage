// Copyright Ahmet Fatih Senelmis


#include "AbilitySystem/Abilities/HeroGameplayAbility_PickUpStones.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/MastersRageHeroCharacter.h"
#include "Items/PickUps/MastersRageStoneBase.h"
#include "Components/UI/HeroUIComponent.h"

void UHeroGameplayAbility_PickUpStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetHeroUIComponentFromActorInfo()->OnStoneInteractedDelegate.Broadcast(true);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_PickUpStones::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetHeroUIComponentFromActorInfo()->OnStoneInteractedDelegate.Broadcast(false);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_PickUpStones::CollectStones()
{
	CollectedStones.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + -GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		(-GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (AMastersRageStoneBase* FoundStone = Cast<AMastersRageStoneBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UHeroGameplayAbility_PickUpStones::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AMastersRageStoneBase* CollectedStone : CollectedStones)
	{
		if (CollectedStone)
		{
			CollectedStone->Consume(GetMRageAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}

}
