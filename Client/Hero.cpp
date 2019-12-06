#include "stdafx.h"
#include "Hero.h"

void Hero::randomize()
{
	mPriority = rand() % 10 + 1;

	mPrimaryBase.Constitution = rand() % 20 + 5;
	mPrimaryBase.Dexterity = rand() % 20 + 5;
	mPrimaryBase.Intellect = rand() % 20 + 3;
	mPrimaryBase.Lethality = rand() % 20 + 1;
	mPrimaryBase.Mentallity = rand() % 20 + 3;
	mPrimaryBase.Strength = rand() % 20 + 5;

	mPrimaryScaling.Constitution = rand() % 4 + 1;
	mPrimaryScaling.Dexterity = rand() % 4;
	mPrimaryScaling.Intellect = rand() % 4 + 1;
	mPrimaryScaling.Lethality = rand() % 4;
	mPrimaryScaling.Mentallity = rand() % 4 + 1;
	mPrimaryScaling.Strength = rand() % 4;

	mIdentityAtt.AOE = rand() % 5;
	mIdentityAtt.Burst = rand() % 5;
	mIdentityAtt.CrowdControl = rand() % 5;
	mIdentityAtt.Mobility = rand() % 5;
	mIdentityAtt.Range = rand() % 5 + 1;
}

void Hero::calculateCombatAtt()
{
}

void Hero::calculateTotalAtt()
{
	mPrimaryTotal.Constitution = mPrimaryBase.Constitution + (mPrimaryScaling.Constitution * mInGameStats.Level);
	mPrimaryTotal.Dexterity = mPrimaryBase.Dexterity + (mPrimaryScaling.Dexterity * mInGameStats.Level);
	mPrimaryTotal.Intellect = mPrimaryBase.Intellect + (mPrimaryScaling.Intellect * mInGameStats.Level);
	mPrimaryTotal.Lethality = mPrimaryBase.Lethality + (mPrimaryScaling.Lethality * mInGameStats.Level);
	mPrimaryTotal.Mentallity = mPrimaryBase.Mentallity + (mPrimaryScaling.Mentallity * mInGameStats.Level);
	mPrimaryTotal.Strength = mPrimaryBase.Strength + (mPrimaryScaling.Strength * mInGameStats.Level);
}

void Hero::calculateOverall()
{
	mOverall.Assassinating = ((mIdentityAtt.Mobility * mPrimaryTotal.Intellect) + (mIdentityAtt.Mobility * mPrimaryTotal.Lethality) + (mIdentityAtt.Burst * mPrimaryTotal.Lethality) + (mIdentityAtt.Burst * mPrimaryTotal.Intellect)) / 24;
	mOverall.Laning = ((mIdentityAtt.Range * mPrimaryTotal.Dexterity) + (mIdentityAtt.AOE * mPrimaryTotal.Intellect) + (mIdentityAtt.Mobility * mPrimaryTotal.Lethality)) / 18;
	mOverall.Surviving = ((mIdentityAtt.Mobility * mPrimaryTotal.Constitution) + (mIdentityAtt.CrowdControl * mPrimaryTotal.Mentallity)) / 12;
	mOverall.Roaming = (mOverall.Assassinating + mOverall.Laning) / 2;
	mOverall.SplitPushing = (mOverall.Roaming+mOverall.Assassinating+mOverall.Laning+mOverall.Surviving) / 4;
	mOverall.TeamFighting = ((mIdentityAtt.Range*mPrimaryTotal.Dexterity)+(mIdentityAtt.CrowdControl*mPrimaryTotal.Constitution)+mOverall.Surviving)/13;
}

void Hero::updateLevel()
{
	if (mInGameStats.CurrentExp >= mInGameStats.NextLvlExp)
	{
		mInGameStats.Level++;
		mInGameStats.CurrentExp = 0;
		mInGameStats.NextLvlExp = static_cast<unsigned long long int>((50 / 3) * (pow(mInGameStats.Level, 3) - 6 * pow(mInGameStats.Level, 2) + ((double(mInGameStats.Level) * 17)) - 12));
	}
}

/* Constructor / Destructor */
Hero::Hero()
{
	mID = 0;
	mBanned = false;
	mIsInGame = false;
	mPriority = 0;

	mPrimaryBase = {};
	mPrimaryScaling = {};
	mPrimaryTotal = {};

	mIdentityAtt = {};

	mOverall = {};

	//mCombatAtt = {};
	//mBonusCombatAtt = {};

	mInGameStats = {};
	mInGameStats.Level = 1;

	randomize();
	calculateTotalAtt();
	calculateOverall();
}

Hero::~Hero()
{
}

const bool Hero::banned() const
{
	return mBanned;
}

void Hero::setInGame(bool in_game)
{
	mIsInGame = in_game;
}

void Hero::setBanned(bool banned)
{
	mBanned = banned;
}

/* Core Functions */
void Hero::update()
{
	updateLevel();
}
