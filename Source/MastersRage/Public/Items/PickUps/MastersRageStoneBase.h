// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/MastersRagePickUpBase.h"
#include "MastersRageStoneBase.generated.h"

class UMRageAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API AMastersRageStoneBase : public AMastersRagePickUpBase
{
	GENERATED_BODY()
	
public:

	void Consume(UMRageAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:

	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
