#ifndef LADDERMATCH_H
#define LADDERMATCH_H
#include "Match.h"

class LadderMatch : public Match
{
private:

	std::map<unsigned, Hero*> mAvailableHeroes;

	LadderTeam* mBlueTeam;
	LadderTeam* mRedTeam;

	void pickAndBan();

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
	void simulate();

	/* Core */
	void updateTeams();
};
#endif // !LADDERMATCH_H