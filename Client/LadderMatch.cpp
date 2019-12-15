#include "stdafx.h"
#include "LadderMatch.h"

LadderMatch::LadderMatch()
{
	for (const auto& itr : *DataHandler::instance()->getHeroesDB())
	{
		mHeroesAvailale.insert({itr.second->getID(), new Hero(itr.second)});
	}

	mBlueTeam = new LadderTeam();
	mRedTeam = new LadderTeam();
}

LadderMatch::~LadderMatch()
{
	for (auto& itr : mHeroesAvailale)
	{
		delete itr.second;
		itr.second = nullptr;
	}
	mHeroesAvailale.clear();

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

const LadderTeam* LadderMatch::getBlueTeam() const
{
	return mBlueTeam;
}

const LadderTeam* LadderMatch::getRedTeam() const
{
	return mRedTeam;
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

void LadderMatch::pickAndBan()
{
}

void LadderMatch::updateTeams()
{
	mBlueTeam->update();
	mRedTeam->update();
}
