// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UMRageEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:

	virtual void GiveToAbilitySystemComponent(UMRageAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UMRageEnemyGameplayAbility>> EnemyCombatAbilities;
};
