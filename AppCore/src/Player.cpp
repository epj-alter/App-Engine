#include "Player.h"
#include "DataHandler.h"

namespace Core
{
	/* Constructor / Destructor */
	Player::Player(std::string ID)
		: Person(ID)
	{
		/* Professional Info */
		mPosition = static_cast<Position>(rand() % 5); //DEBUG
		mRank = 0;
		mValue = 0;
	
		/* Status */
		mQueuedUP = false;
		mQueuedUP = true;  // DEBUG
		mQueuedPosition = mPosition;
	
		/* Statistics */
		mPlayerStats = new PlayerStatistics();
		mPlayerAvgs = new PlayerAverages();
		mPlayerAtt = new PlayerAttributes();
	
		/* Progression */
		for (const auto& itr : *DataHandler::instance()->getHeroesDB())
		{
			mHeroProgression.insert({itr.second->getID(), rand() % 100});
		}
	
		for (const auto& itr : *DataHandler::instance()->getHeroesDB())
		{
			mFavouriteHeroes.insert({itr.second->getID(), rand() % 15});
		}
	
		for (const auto& itr : *DataHandler::instance()->getHeroesDB())
		{
			mHatedHeroes.insert({itr.second->getID(), rand() % 15});
		}
	}
	
	Player::~Player()
	{
		mHeroesToPractice.clear();
		mHeroProgression.clear();
		mFavouriteHeroes.clear();
		mHatedHeroes.clear();
	
		delete mPlayerAvgs;
		mPlayerAvgs = nullptr;
	
		delete mPlayerStats;
		mPlayerStats = nullptr;
	
		delete mPlayerAtt;
		mPlayerAtt = nullptr;
	}
	
	/* Accessors */
	const PlayerAttributes Player::getPlayerAttribute() const
	{
		return *mPlayerAtt;
	}
	
	const Position Player::getPosition() const
	{
		return mPosition;
	}
	
	const bool Player::isQueuedUp() const
	{
		return mQueuedUP;
	}
	
	const Position Player::queuedPosition() const
	{
		return mQueuedPosition;
	}
	
	const std::vector<unsigned> Player::getBestHeroesID() const
	{
		std::vector<unsigned> best_heroes_id;
	
		for (const auto& itr : mHeroProgression)
		{
			if (best_heroes_id.size() >= 5)
				break;
			else
				best_heroes_id.push_back(itr.first);
		}
	
		return best_heroes_id;
	}
	
	const std::vector<unsigned> Player::getFavouriteHeroesID() const
	{
		std::vector<unsigned> favourite_heroes_id;
	
		for (const auto& itr : mFavouriteHeroes)
		{
			if (favourite_heroes_id.size() >= 5)
				break;
			else
				favourite_heroes_id.push_back(itr.first);
		}
	
		return favourite_heroes_id;
	}
	
	const std::vector<unsigned> Player::getHatedHeroesID() const
	{
		std::vector<unsigned> hated_heroes_id;
	
		for (const auto& itr : mHatedHeroes)
		{
			if (hated_heroes_id.size() >= 5)
				break;
			else
				hated_heroes_id.push_back(itr.first);
		}
	
		return hated_heroes_id;
	}
	
	const std::vector<unsigned> Player::getHeroesToPractice() const
	{
		std::vector<unsigned> heroes_to_practice;
	
		for (const auto& itr : mHeroesToPractice)
		{
			if (heroes_to_practice.size() >= 5)
				break;
			else
				heroes_to_practice.push_back(itr.first);
		}
	
		return heroes_to_practice;
	}
	
	/* Modifiers */
	void Player::setPosition(Position position)
	{
		mPosition = position;
	}
	
	void Player::setQueueStatus(bool queue_status)
	{
		mQueuedUP = queue_status;
	}
	
	void Player::setQueuePosition(Position queue_position)
	{
		mQueuedPosition = queue_position;
	}
	
	void Player::insertHeroPractice(unsigned hero_id, unsigned priority)
	{
		if (mHeroesToPractice.size() >= 5)
			printf("You can't add more heroes to practice. \n");
		else
			mHeroesToPractice.insert({hero_id, priority});
	}
	
	void Player::removeHeroPractice(unsigned hero_id)
	{
		mHeroesToPractice.erase(hero_id);
	}
	
	/* Update */
	void Player::update()
	{
	}
}
