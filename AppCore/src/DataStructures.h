#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

namespace Core
{
	enum personalities { NO_PERSONALITY, PERFECTIONIST, PROFESSIONAL, AMBITIOUS, LEADER, OPTIMISTIC, JOVIAL, LOYAL, HONEST, REALIST, BALANCED, SLACK, CASUAL, TEMPERAMENTAL, UNAMBITIOUS, PESSIMISTIC };
	enum roles { NO_ROLE, WARDEN, WARLORD, DUELIST, RAIDER, NUKER, CONTROLLER, ASSASSIN, MARKSMAN};
	
	enum reputations {WORLD_CLASS, INTERNATIONAL, PRO, SEMI_PRO, ROOKIE};
	enum descriptions {NO_DESCRIPTION, WONDERKID, HOT_PROSPECT, CLIMBER, ENTERTAINER};

	typedef struct BasicInfo
	{
		std::string name;
		unsigned age = 0;
		roles role = NO_ROLE;
		roles role2 = NO_ROLE;
		unsigned rank = 0;

	} BasicInfo;
	
	
	typedef struct ContractInfo
	{
		//complete calendar beforehand

	} ContractInfo;
	
	typedef struct TechnicalAtt
	{
		unsigned accuracy = 0;
		unsigned dodging = 0;
		unsigned positioning = 0;
		unsigned awareness = 0;
		unsigned pace = 0;
		unsigned lasthitting = 0;
		unsigned harassing = 0;
		unsigned trading = 0;
		unsigned surviving = 0;
		unsigned eliminating = 0;
		unsigned flair = 0;

		float overall = (accuracy + dodging + positioning + awareness + pace + lasthitting + harassing + trading + surviving + eliminating + flair) / 11.f;

	} TechnicalAtt;

	typedef struct MentalAtt
	{
		unsigned aggression = 0;
		unsigned composure = 0;
		unsigned bravery = 0;
		unsigned concentration = 0;
		unsigned decisions = 0;
		unsigned leadership = 0;
		unsigned creativity = 0;
		unsigned anticipation = 0;
		unsigned teamwork = 0;
		unsigned workrate = 0;

		float overall = (aggression + composure + bravery + concentration + decisions + leadership + creativity + anticipation + teamwork + workrate) / 10.f;

	} MentalAtt;
	
	typedef struct GeneralAtt
	{
		personalities personality = NO_PERSONALITY;
		descriptions mediadescription = NO_DESCRIPTION;
		reputations reputation = ROOKIE;
		std::string prefavatar;
		std::string trait1;
		std::string trait2;
		std::string trait3;

	} GeneralAtt;
		
	typedef struct KnowledgeAtt
	{
		unsigned laneknowledge = 0;
		unsigned avatarknowledge = 0;
		unsigned matchupknowledge = 0;
		unsigned macroknowledge = 0;

		float overall = (laneknowledge + avatarknowledge + matchupknowledge + macroknowledge) / 4.f;

	} KnowledgeAtt;
	
	typedef struct PersonalityAtt
	{
		unsigned ambition = 0;
		unsigned controversy = 0;
		unsigned loyalty = 0;
		unsigned pressurehandling = 0;
		unsigned professionalism = 0;
		unsigned sportsmanship = 0;
		unsigned temperament = 0;

		unsigned adaptability = 0;
		unsigned versatility = 0;
		unsigned consistency = 0;

		float overall = (adaptability + versatility + consistency + pressurehandling) / 10.f;

	} PersonalityAtt;

	typedef struct PrimaryAtt
	{
		unsigned laning = 0;
		unsigned splitpushing = 0;
		unsigned assassinating = 0;
		unsigned roaming = 0;
		unsigned teamfighting = 0;
		unsigned surviving = 0;

		PrimaryAtt(TechnicalAtt& technical, MentalAtt& mental)
		{

		}

	} PrimaryAtt;
}

#endif // !DATASTRUCTURES_H
