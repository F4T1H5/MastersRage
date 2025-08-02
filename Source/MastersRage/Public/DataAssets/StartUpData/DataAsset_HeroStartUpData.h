// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "MastersRageTypes/MastersRageStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:

	virtual void GiveToAbilitySystemComponent(UMRageAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FMastersRageHeroAbilitySet> HeroStartUpAbilitySets;
};
