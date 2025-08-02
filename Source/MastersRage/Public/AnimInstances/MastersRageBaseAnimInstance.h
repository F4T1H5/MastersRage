// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "MastersRageBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;
};
