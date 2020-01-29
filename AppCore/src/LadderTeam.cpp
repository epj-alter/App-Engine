#include "LadderTeam.h"

namespace Core
{
	/* Constructor / Destructor */
	LadderTeam::LadderTeam(std::map<unsigned, Hero*>* available_heroes)
	{
		mAvailableHeroes = available_heroes;
	
		printf("Team created. \n");
	}
	
	LadderTeam::~LadderTeam()
	{
		mAvailableHeroes = nullptr;
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
	
	void LadderTeam::banHero(Position position)
	{
		std::vector<unsigned> player_heroes = mPlayers.at(position)->getHatedHeroesID();
	
		bool success = false;
		unsigned count = 0;
	
		std::random_shuffle(player_heroes.begin(), player_heroes.end());
	
		do
		{
			if (!mAvailableHeroes->at(player_heroes.back())->isBanned())
			{
				mAvailableHeroes->at(player_heroes.back())->ban();
				mBannedHeroes.insert({ position, mAvailableHeroes->at(player_heroes.back()) });
	
				success = true;
				printf("%i banned.\n", mAvailableHeroes->at(player_heroes.back())->getID());
			}
			else
			{
				if (count < 5)
				{
					count++;
					std::random_shuffle(player_heroes.begin(), player_heroes.end());
					printf("%i is already banned.\n", mAvailableHeroes->at(player_heroes.back())->getID());
				}
				else
				{
					unsigned id = rand() % 24 + 1001;
					if (!mAvailableHeroes->at(id)->isBanned())
					{
						mAvailableHeroes->at(id)->ban();
						mBannedHeroes.insert({ position, mAvailableHeroes->at(id) });
						success = true;
						printf("%i banned as a last resource.\n", mAvailableHeroes->at(id)->getID());
					}
				}
			}
	
		} while (success == false);
	}
	
	void LadderTeam::selectHero(Position position)
	{
		std::vector<unsigned> player_heroes;
		bool success = false;
		unsigned count = 0;
	
		for (const auto &itr : mPlayers.at(position)->getBestHeroesID())
		{
			player_heroes.push_back(itr);
		}
	
		for (const auto &itr : mPlayers.at(position)->getFavouriteHeroesID())
		{
			player_heroes.push_back(itr);
		}
	
		for (const auto &itr : mPlayers.at(position)->getHeroesToPractice())
		{
			player_heroes.push_back(itr);
		}
	
		std::random_shuffle(player_heroes.begin(), player_heroes.end());
	
		do
		{
			if (!(mAvailableHeroes->at(player_heroes.back())->isBanned()) && !(mAvailableHeroes->at(player_heroes.back())->isSelected()))
			{
				mAvailableHeroes->at(player_heroes.back())->select();
				mSelectedHeroes.insert({ position, mAvailableHeroes->at(player_heroes.back()) });
	
				success = true;
				printf("%i selected.\n", mAvailableHeroes->at(player_heroes.back())->getID());
			}
			else
			{
				if (count < 5)
				{
					count++;
					std::random_shuffle(player_heroes.begin(), player_heroes.end());
					printf("%i is already selected or banned banned.\n", mAvailableHeroes->at(player_heroes.back())->getID());
				}
				else
				{
					unsigned id = rand() % 24 + 1001;
					if (!(mAvailableHeroes->at(id)->isBanned()) && !(mAvailableHeroes->at(id)->isSelected()))
					{
						mAvailableHeroes->at(id)->select();
						mSelectedHeroes.insert({ position, mAvailableHeroes->at(id) });
						success = true;
						printf("%i selected as a last resource.\n", mAvailableHeroes->at(id)->getID());
					}
				}
			}
	
		} while (success == false);
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
}
