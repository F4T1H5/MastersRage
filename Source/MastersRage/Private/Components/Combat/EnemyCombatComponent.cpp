// Copyright Ahmet Fatih Senelmis


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MastersRageGameplayTags.h"
#include "MastersRageFunctionLibrary.h"
#include "Characters/MastersRageEnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "MastersRageDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//TODO: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UMastersRageFunctionLibrary::NativeDoesActorHaveTag(HitActor, MastersRageGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UMastersRageFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), MastersRageGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UMastersRageFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			MastersRageGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			MastersRageGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AMastersRageEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AMastersRageEnemyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
