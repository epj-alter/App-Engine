#ifndef PLAYERDATA_H
#define PLAYERDATA_H
#include "HeroData.h"

/*----------------- ATTRIBUTES --------------------*/

/* Progress */
typedef struct Progress
{
	unsigned ELO;
	unsigned Level;
	unsigned long long CurrentExp;
	unsigned long long NextLevelExp;
};

/* Technical */	
typedef struct Technical
{
	unsigned accuracy;
	unsigned awareness;
	unsigned dodging;
	unsigned eliminating;
	unsigned flair;
	unsigned harassing;
	unsigned lasthitting;
	unsigned positioning;
	unsigned trading;
	unsigned survivability;
};

/* Mental */
typedef struct Mental
{
	unsigned aggression;
	unsigned anticipation;
	unsigned bravery;
	unsigned composure;
	unsigned concentration;
	unsigned creativity;
	unsigned decisions;
	unsigned leadership;
	unsigned teamwork;
	unsigned workrate;
};

/* Personality */
typedef struct Personality
{
	unsigned adaptability;
	unsigned ambition;
	unsigned controversy;
	unsigned consistency;
	unsigned loyalty;
	unsigned pressurehandling;
	unsigned professionalism;
	unsigned sportsmanship;
	unsigned temperament;
	unsigned versatility;
};

/* Overall */
typedef struct Overall
{
	float Surviving;
	float Laning;
	float TeamFighting;
	float Roaming;
	float Assassinating;
	float SplitPushing;
};

#endif // !PLAYERDATA_H
