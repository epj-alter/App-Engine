#ifndef LADDERMATCH_H
#define LADDERMATCH_H
#include "Match.h"

class LadderMatch : public Match
{
private:

	std::map<unsigned, Hero*> mHeroesAvailale;

	LadderTeam* mBlueTeam;
	LadderTeam* mRedTeam;

public:

	/* Constructor */
	LadderMatch();
	~LadderMatch();

	/* Accessors */
	const bool hasEnoughPlayers() const;
	const LadderTeam* getBlueTeam() const;
	const LadderTeam* getRedTeam() const;


	/* Modifiers */
	const bool addPlayer(Player* player, Position position);

	/* Simulation */
	void pickAndBan();


	/* Core */
	void updateTeams();
};
#endif // !LADDERMATCH_H