// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MastersRageTypes/MastersRageEnumTypes.h"
#include "MastersRageSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	EMastersRageGameDifficulty SavedCurrentGameDifficulty;

};
