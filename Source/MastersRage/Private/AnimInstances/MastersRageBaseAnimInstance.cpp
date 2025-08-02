// Copyright Ahmet Fatih Senelmis


#include "AnimInstances/MastersRageBaseAnimInstance.h"
#include "MastersRageFunctionLibrary.h"

bool UMastersRageBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UMastersRageFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
