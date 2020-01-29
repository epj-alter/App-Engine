#include "LadderMatch.h"
#include "DataHandler.h"

namespace Core
{
	void LadderMatch::pickAndBan()
	{
		// ban
		mBlueTeam->banHero(Position::TOP);
		mRedTeam->banHero(Position::TOP);
		mRedTeam->banHero(Position::JUNGLE);
		mBlueTeam->banHero(Position::JUNGLE);
		mBlueTeam->banHero(Position::MIDDLE);
		mRedTeam->banHero(Position::MIDDLE);
		mRedTeam->banHero(Position::BOTTOM);
		mBlueTeam->banHero(Position::BOTTOM);
		mBlueTeam->banHero(Position::SUPPORT);
		mRedTeam->banHero(Position::SUPPORT);
		
		// pick
		mBlueTeam->selectHero(Position::TOP);
		mRedTeam->selectHero(Position::TOP);
		mRedTeam->selectHero(Position::JUNGLE);
		mBlueTeam->selectHero(Position::JUNGLE);
		mBlueTeam->selectHero(Position::MIDDLE);
		mRedTeam->selectHero(Position::MIDDLE);
		mRedTeam->selectHero(Position::BOTTOM);
		mBlueTeam->selectHero(Position::BOTTOM);
		mBlueTeam->selectHero(Position::SUPPORT);
		mRedTeam->selectHero(Position::SUPPORT);
	}
	
	LadderMatch::LadderMatch()
	{
		for (const auto& itr : *DataHandler::instance()->getHeroesDB())
		{
			mAvailableHeroes.insert({itr.second->getID(), new Hero(itr.second)});
		}
	
		mBlueTeam = new LadderTeam(&mAvailableHeroes);
		mRedTeam = new LadderTeam(&mAvailableHeroes);
	}
	
	LadderMatch::~LadderMatch()
	{
		for (auto& itr : mAvailableHeroes)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mAvailableHeroes.clear();
	
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
	
	void LadderMatch::simulate()
	{
		pickAndBan();
	}
	
	void LadderMatch::updateTeams()
	{
		mBlueTeam->update();
		mRedTeam->update();
	}
}
