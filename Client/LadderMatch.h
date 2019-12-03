#ifndef LADDERMATCH_H
#define LADDERMATCH_H
#include "Match.h"

class LadderMatch : public Match
{
private:

	LadderTeam* mBlueTeam;
	LadderTeam* mRedTeam;

public:

	/* Constructor */
	LadderMatch();
	~LadderMatch();

	/* Accessors */
	const bool hasEnoughPlayers() const;

	/* Modifiers */
	const bool addPlayer(Player* player, Position position);

	/* Core */
	void updateTeams();
};
#endif // !LADDERMATCH_H