#include "stdafx.h"
#include "Player.h"

/* Constructor / Destructor */
Player::Player(std::string ID)
	: Person(ID)
{
	/* Professional Info */
	mRank = 0;
	mValue = 0;

	/* Status */
	mQueuedUP = false;

	/* Statistics */
	mPlayerStats = new PlayerStatistics();
	mPlayerAvgs = new PlayerAverages();

	/* Attributes */
	mPlayerAtt = new PlayerAttributes();

	mSelectedHero = nullptr;

	mPosition = static_cast<Position>(rand() % 5); //DEBUG
	mQueuedUP = true;
	mQueuedPosition = mPosition;
}

Player::~Player()
{
	mSelectedHero = nullptr;

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

const Hero* Player::getHero() const
{
	return mSelectedHero;
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

void Player::setHero(Hero* selected_hero)
{
	mSelectedHero = selected_hero;
}

/* Update */
void Player::update()
{
}
