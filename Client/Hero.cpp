#include "stdafx.h"
#include "Hero.h"

void Hero::randomize()
{
	mPriority = rand() % 10 + 1;

	mPrimaryBase.Constitution = rand() % 20 + 5;
	mPrimaryBase.Dexterity = rand() % 20 + 5;
	mPrimaryBase.Intellect = rand() % 20 + 3;
	mPrimaryBase.Lethality = rand() % 20 + 1;
	mPrimaryBase.Mentality = rand() % 20 + 3;
	mPrimaryBase.Strength = rand() % 20 + 5;

	mPrimaryScaling.Constitution = rand() % 4 + 1;
	mPrimaryScaling.Dexterity = rand() % 4;
	mPrimaryScaling.Intellect = rand() % 4 + 1;
	mPrimaryScaling.Lethality = rand() % 4;
	mPrimaryScaling.Mentality = rand() % 4 + 1;
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
	mPrimaryTotal.Mentality = mPrimaryBase.Mentality + (mPrimaryScaling.Mentality * mInGameStats.Level);
	mPrimaryTotal.Strength = mPrimaryBase.Strength + (mPrimaryScaling.Strength * mInGameStats.Level);
}

void Hero::calculateOverall()
{
	mOverall.Assassinating = ((mIdentityAtt.Mobility * mPrimaryTotal.Intellect) + (mIdentityAtt.Mobility * mPrimaryTotal.Lethality) + (mIdentityAtt.Burst * mPrimaryTotal.Lethality) + (mIdentityAtt.Burst * mPrimaryTotal.Intellect)) / 24;
	mOverall.Laning = ((mIdentityAtt.Range * mPrimaryTotal.Dexterity) + (mIdentityAtt.AOE * mPrimaryTotal.Intellect) + (mIdentityAtt.Mobility * mPrimaryTotal.Lethality)) / 18;
	mOverall.Surviving = ((mIdentityAtt.Mobility * mPrimaryTotal.Constitution) + (mIdentityAtt.CrowdControl * mPrimaryTotal.Mentality)) / 12;
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
}

Hero::Hero(std::string name, std::string id, unsigned priority, unsigned hero_class, 
	unsigned strong1, unsigned strong2, unsigned strong3, unsigned weak1, unsigned weak2, unsigned weak3, 
	unsigned bstrength, unsigned bconstitution, unsigned bintellect, unsigned bmentality, unsigned bdexterity, unsigned blethality, 
	unsigned sstrength, unsigned sconstitution, unsigned sintellect, unsigned smentality, unsigned sdexterity, unsigned slethality, 
	unsigned aoe, unsigned burst, unsigned cc, unsigned mobility, unsigned range)
{
	mID = id;
	mName = name;
	mClass = static_cast<HeroClass>(hero_class);

	mBanned = false;
	mIsInGame = false;
	mPriority = priority;

	mPrimaryBase.Constitution = bconstitution;
	mPrimaryBase.Dexterity = bdexterity;
	mPrimaryBase.Intellect = bintellect;
	mPrimaryBase.Lethality = blethality;
	mPrimaryBase.Mentality = bmentality;
	mPrimaryBase.Strength = bstrength;

	mPrimaryScaling.Constitution = sconstitution;
	mPrimaryScaling.Dexterity = sdexterity;
	mPrimaryScaling.Intellect = sintellect;
	mPrimaryScaling.Lethality = slethality;
	mPrimaryScaling.Mentality = smentality;
	mPrimaryScaling.Strength = sstrength;

	mIdentityAtt.AOE = aoe;
	mIdentityAtt.Burst = burst;
	mIdentityAtt.CrowdControl = cc;
	mIdentityAtt.Mobility = mobility;
	mIdentityAtt.Range = range;

	mInGameStats = {};
	mInGameStats.Level = 1;

	calculateTotalAtt();
	calculateOverall();
}

Hero::Hero(Hero* existing_hero)
{
	memcpy(existing_hero, this, sizeof(this));
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
