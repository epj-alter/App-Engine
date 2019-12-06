#ifndef HERO_H
#define HERO_H
#include "PlayerAttributes.h"

class Hero
{
private:

	/* Creation */
	unsigned mID;
	FILE* dFile;

	/* Basic Info */
	std::string mName;
	unsigned mPriority;
	bool mBanned;
	bool mIsInGame;

	/* Attributes */
	PrimaryAttributes mPrimaryBase;
	PrimaryAttributes mPrimaryScaling;
	PrimaryAttributes mPrimaryTotal;

	IdentityAttributes mIdentityAtt;
	//IdentityAttributes mIdentityScaling; // maybe in the future.

	Overall mOverall;

	/* In Game Attributes */
	//CombatAttributes mCombatAtt;
	//CombatAttributes mBonusCombatAtt;

	InGameStats mInGameStats;

	/* Private Functions */
	void randomize();
	void calculateCombatAtt();
	void calculateTotalAtt();
	void calculateOverall();

	void updateLevel();

public:

	/* Constructor */
	Hero();
	~Hero(); // make virtual for abstract class

	/* Accessors */
	const bool banned() const;

	/* Modifiers */
	void setInGame(bool in_game);
	void setBanned(bool banned);

	/* Core Functions */
	void update();
};

#endif // !HERO_H

