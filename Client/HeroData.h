#ifndef HERODATA_H
#define HERODATA_H
#include "Definitions.h"

enum class HeroClass {Assassin, Controller, Duelist, Enchanter, Marksman, Nuker, Raider, Warden, Warlord};

/* Constants */
const unsigned MaxInGameLevel = 20;
const unsigned long long ExpLimit = 18446644073709551615;

/* Primary Attributes */
typedef struct PrimaryAttributes
{
	unsigned Strength;
	unsigned Constitution;
	unsigned Intellect;
	unsigned Mentality;
	unsigned Dexterity;
	unsigned Lethality;
};

typedef struct IdentityAttributes
{
	unsigned Range;
	unsigned AOE;
	unsigned Mobility;
	unsigned CrowdControl;
	unsigned Burst;
};

typedef struct CombatAttributes
{
	int Health;
	int HealthRecovery;
	int Energy;
	int EnergyRecovery;
	int Endurance;
	int Protection;
	int PhysicalDamage;
	int MagicalDamage;
	int CriticalDamage;
	float AttackSpeed;
	int MoveSpeed;
	int CriticalChance;
};

typedef struct InGameStats
{
	unsigned GoldEarned;
	unsigned CreepScore;
	unsigned Kills;
	unsigned Deaths;
	unsigned Assists;
	unsigned DamageDealt;
	unsigned DamageReceived;

	unsigned Level = 1;
	unsigned CurrentExp = 0;
	unsigned NextLvlExp = static_cast<unsigned>((50 / 3)* (pow(Level, 3) - 6 * pow(Level, 2) + ((double(Level) * 17)) - 12));

};

#endif // !HERODATA_H
