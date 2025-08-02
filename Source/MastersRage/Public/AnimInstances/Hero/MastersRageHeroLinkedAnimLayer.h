// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MastersRageBaseAnimInstance.h"
#include "MastersRageHeroLinkedAnimLayer.generated.h"

class UMastersRageHeroAnimInstance;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageHeroLinkedAnimLayer : public UMastersRageBaseAnimInstance
{
	GENERATED_BODY()
	
public:

	// pure and thread safe has to be bc we will use this inside the property access
	// so that in order to show up
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UMastersRageHeroAnimInstance* GetHeroAnimInstance() const;

};
