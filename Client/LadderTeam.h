#ifndef LADDERTEAM_H
#define LADDERTEAM_H
#include "Team.h"

class LadderTeam : public Team
{
private:

	const size_t max_players = 5;
	std::map<Position, Player*> mPlayers;

public:

	/* Constructor */
	LadderTeam();
	~LadderTeam();

	/* Accessors */
	const Player* getPlayer(Position position) const;
	const bool hasEnoughPlayers() const;

	/* Modifiers */
	const bool addPlayer(Player* player, Position position);

	/* update */
	void update();
};

#endif // !LADDERTEAM_H