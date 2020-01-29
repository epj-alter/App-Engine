#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include "Scene.h"

class Person;

namespace Core
{
	/* Tiers & ELO */
	const unsigned Bronze = 0;
	const unsigned Silver = 430;
	const unsigned Gold = 860;
	const unsigned Platinum = 1290;
	const unsigned Diamond = 1720;
	const unsigned Master = 2150;
	const unsigned Challenger = 2580;
	const unsigned ELO_MAX = 3000;

	enum class Nation { GERMANY, KOREA, USA };
	enum class MatchType {SOLO, SCRIMMAGE, TOURNAMENT};
	enum class TeamType {RANDOM, YOUTH, PROFESSIONAL};
	enum class Profession {MANAGER, COACH, PLAYER };
	enum class Position {TOP, JUNGLE, MIDDLE, BOTTOM, SUPPORT};
	enum class Role { NO_ROLE, WARDEN, WARLORD, DUELIST, RAIDER, NUKER, CONTROLLER, ASSASSIN, MARKSMAN };
	enum class TeamSelection {NO_POSITION, TOP, JUNGLE, MIDDLE, BOTTON, SUPPORT, SUB1, SUB2};

	typedef struct Calendar
	{
		unsigned day = 0, month = 0, year= 0;
	};

	typedef struct LanguageProgression //DEBUG
	{
		bool English;
		bool Korean;
		bool Spanish;
	};

	typedef union CitizenshipProgression //DEBUG
	{
		unsigned NA;
		unsigned EU;
		unsigned KR;
	};

	typedef struct RoleProgression
	{
		unsigned top = 0, jungle = 0, middle = 0, bottom = 0, support = 0;
	};

	typedef struct PlayerStatistics
	{
		unsigned mGamesPlayed;
		unsigned mGamesWon;
		unsigned mGamesLost;
		unsigned mAssists;
		unsigned mDeaths;
		unsigned mKills;
		unsigned mFirstBloods;
		unsigned mPentakills;
	};

	typedef struct PlayerAverages
	{
		double mAvgDamageMinute;
		double mAvgDamageShare;
		double mAvgDamageTotal;
		double mAvgGoldMinute;
		double mAvgGoldShare;
		double mAvgGoldTotal;
		double mAvgKillParticipation;
		double mAvgKillShare;
		double mAvgKillsTotal;
		double mAvgTroopersKill;
		double mAvgTroopersMinute;
		double mAvgGoldDifferenceTen;
		double mFirstBloodRate;
		double mWinRate;
		double mKDA;
	};
}
#endif // !DEFINITIONS_H

