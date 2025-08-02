// Copyright Ahmet Fatih Senelmis


#include "Items/PickUps/MastersRageStoneBase.h"
#include "Characters/MastersRageHeroCharacter.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "MastersRageGameplayTags.h"

void AMastersRageStoneBase::Consume(UMRageAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}

void AMastersRageStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMastersRageHeroCharacter* OverlappedHeroCharacter = Cast<AMastersRageHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetMRageAbilitySystemComponent()->TryActivateAbilityByTag(MastersRageGameplayTags::Player_Ability_PickUp_Stones);
	}

}
