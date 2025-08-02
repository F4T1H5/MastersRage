// Copyright Ahmet Fatih Senelmis


#include "MastersRageTypes/MastersRageStructTypes.h"
#include "AbilitySystem/Abilities/MRageHeroGameplayAbility.h"


bool FMastersRageHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}