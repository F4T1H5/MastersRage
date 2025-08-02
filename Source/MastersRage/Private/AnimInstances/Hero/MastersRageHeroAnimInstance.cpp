// Copyright Ahmet Fatih Senelmis


#include "AnimInstances/Hero/MastersRageHeroAnimInstance.h"
#include "Characters/MastersRageHeroCharacter.h"

void UMastersRageHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AMastersRageHeroCharacter>(OwningCharacter);
	}
}

void UMastersRageHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}