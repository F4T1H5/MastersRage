// Copyright Ahmet Fatih Senelmis


#include "Controllers/MastersRageHeroController.h"

AMastersRageHeroController::AMastersRageHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AMastersRageHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}