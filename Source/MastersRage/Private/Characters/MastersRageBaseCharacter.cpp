// Copyright Ahmet Fatih Senelmis


#include "Characters/MastersRageBaseCharacter.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "AbilitySystem/MRageAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
AMastersRageBaseCharacter::AMastersRageBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	MRageAbilitySystemComponent = CreateDefaultSubobject<UMRageAbilitySystemComponent>(TEXT("MRageAbilitySystemComponent"));
	
	MRageAttributeSet = CreateDefaultSubobject<UMRageAttributeSet>(TEXT("MRageAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* AMastersRageBaseCharacter::GetAbilitySystemComponent() const
{
	return GetMRageAbilitySystemComponent();
}

UPawnCombatComponent* AMastersRageBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AMastersRageBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}


void AMastersRageBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (MRageAbilitySystemComponent)
	{
		MRageAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}