// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MastersRageHeroController.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API AMastersRageHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AMastersRageHeroController();

	//~ Begin IGenericTeamAgentInterface Interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface

private:
	FGenericTeamId HeroTeamId;

};
