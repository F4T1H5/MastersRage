// Copyright Ahmet Fatih Senelmis


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/MRageGameplayAbility.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MRageHeroGameplayAbility.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UMRageAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FMastersRageHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);


		InASCToGive->GiveAbility(AbilitySpec);
	}
}