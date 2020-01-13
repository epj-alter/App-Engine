#ifndef HERO_H
#define HERO_H
#include "PlayerAttributes.h"

class Hero
{
protected:

	/* Creation */
	unsigned mID;
	std::string mName;
	HeroClass mClass;

	/* Basic Info */
	unsigned mPriority;
	bool mBanned;
	bool mSelected;
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
	Hero(std::string name, unsigned id, unsigned priority, unsigned hero_class, 
		unsigned strong1, unsigned strong2, unsigned strong3, unsigned weak1, unsigned weak2, unsigned weak3,
		unsigned bstrength, unsigned bconstitution, unsigned bintellect, unsigned bmentality, unsigned bdexterity, unsigned blethality,
		unsigned sstrength, unsigned sconstitution, unsigned sintellect, unsigned smentality, unsigned sdexterity, unsigned slethality,
		unsigned aoe, unsigned burst, unsigned cc, unsigned mobility, unsigned range);

	Hero(Hero* existing_hero);
	~Hero(); // make virtual for abstract class

	/* Accessors */
	const unsigned getID() const;
	const bool isBanned() const;
	const bool isSelected() const;

	/* Modifiers */
	void setInGame(bool in_game);
	void ban();
	void select();

	/* Core Functions */
	void update();
};

#endif // !HERO_H
