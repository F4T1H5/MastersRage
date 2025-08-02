// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "MastersRageGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FMastersRageGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

protected:
	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMastersRageGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;

};
