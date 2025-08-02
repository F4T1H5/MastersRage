// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MastersRageCharacterAnimInstance.h"
#include "MastersRageHeroAnimInstance.generated.h"

class AMastersRageHeroCharacter;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageHeroAnimInstance : public UMastersRageCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	AMastersRageHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElapsedTime;
};
