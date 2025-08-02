// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MastersRageTypes/MastersRageEnumTypes.h"
#include "MastersRageBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API AMastersRageBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMastersRageBaseGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	EMastersRageGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EMastersRageGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
