#include "stdafx.h"
#include "LadderMatch.h"

LadderMatch::LadderMatch()
{
	mBlueTeam = new LadderTeam();
	mRedTeam = new LadderTeam();
}

LadderMatch::~LadderMatch()
{
	delete mBlueTeam;
	mBlueTeam = nullptr;

	delete mRedTeam;
	mRedTeam = nullptr;
}

const bool LadderMatch::hasEnoughPlayers() const
{
	if (mBlueTeam->hasEnoughPlayers() && mRedTeam->hasEnoughPlayers())
		return true;
	else
		return false;
}

/* Modifiers */
const bool LadderMatch::addPlayer(Player* player, Position position)
{
	if (mBlueTeam->addPlayer(player, position))
		return true;
	else if (mRedTeam->addPlayer(player, position))
		return true;
	else
	{
		return false;
		printf("Match Lobby is complete. \n");
	}
}

void LadderMatch::updateTeams()
{
	mBlueTeam->update();
	mRedTeam->update();
}
