#include "stdafx.h"
#include "LadderTeam.h"

/* Constructor / Destructor */
LadderTeam::LadderTeam()
{
	printf("Team created. \n");
}

LadderTeam::~LadderTeam()
{
	mPlayers.clear();
	mBannedHeroes.clear();
	mSelectedHeroes.clear();
	printf("Team deleted \n");
}

/* Accessors */
const Player* LadderTeam::getPlayer(Position position) const
{
	if (mPlayers.count(position) > 0)
	{
		return mPlayers.at(position);
	}
	else
		printf("There is no player assigned to that Position \n");
}

const bool LadderTeam::hasEnoughPlayers() const
{
	if (mPlayers.size() == max_players)
		return true;
	else
		return false;
}

/* Modifiers */
const bool LadderTeam::addPlayer(Player* player, Position position)
{
	if (mPlayers.count(position) > 0)
	{
		printf("There is already a player in that position. \n");
		return false;
	}
	else
	{
		mPlayers.insert({ position, player });
		printf("Player Inserted at position %i\n", static_cast<int>(position));
		return true;
	}
}

void LadderTeam::banHero(Hero* hero, Position position)
{
	if (!hero->isBanned())
	{
		hero->setBanned(true);
		mBannedHeroes.insert({ position, hero });
	}
	else
		printf("Hero is already banned.\n");
}

void LadderTeam::selectHero(Hero* hero, Position position)
{
	if (!hero->isSelected())
	{
		hero->setSelected(true);
		mSelectedHeroes.insert({ position, hero });
	}
	else
		printf("Hero is already selected.\n");
}

/* Update */
void LadderTeam::update()
{
	if (mPlayers.size() == 5)
	{
		unsigned total_ELO = 0;
		unsigned player_count = 0;

		for (auto& itr : mPlayers)
		{
			player_count++;
			total_ELO += itr.second->getPlayerAttribute().getProgressAtt().ELO;
		}

		mAvgELO = std::round(total_ELO / player_count);
	}

	printf("Team updated \n");
}
