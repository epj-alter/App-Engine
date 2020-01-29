#include "ProTeam.h"

namespace Core
{
	/* Constructor / Destructor */
	ProTeam::ProTeam()
	{
		mSelectionDone = false;
	}
	
	ProTeam::~ProTeam()
	{
		mTeamSelection.clear();
		mSquad.clear();
	}
	
	const Player* ProTeam::getPlayer(TeamSelection position) const
	{
		if (mTeamSelection.count(position) > 0)
		{
			return mTeamSelection.at(position);
		}
		else
			printf("There is no player assigned to that Position \n");
	}
	
	void ProTeam::addPlayer(Player* player)
	{
		mSquad.push_back(player);
		player->setTeam(this);
	
		update();
	}
	
	void ProTeam::setSelection(Player* player, TeamSelection position)
	{
		if (mTeamSelection.count(position) > 0)
		{
			mTeamSelection.erase(position);
			mTeamSelection.insert({ position, player });
		}
		else
			mTeamSelection.insert({ position, player });
	}
	
	/* Update */
	void ProTeam::update()
	{
		unsigned total_ELO = 0;
		unsigned player_count = 0;
	
		for (auto& itr : mSquad)
		{
			player_count++;
			total_ELO += itr->getPlayerAttribute().getProgressAtt().ELO;
		}
	
		mAvgELO = std::round(total_ELO / player_count);
	}
}
