#ifndef LADDERTEAM_H
#define LADDERTEAM_H
#include "Team.h"

class LadderTeam : public Team
{
private:

	std::map<unsigned, Hero*>* mAvailableHeroes;

	const size_t max_players = 5;
	std::map<Position, Player*> mPlayers;
	std::map<Position, Hero* > mBannedHeroes;
	std::map<Position, Hero* > mSelectedHeroes;

public:

	/* Constructor */
	LadderTeam(std::map<unsigned, Hero*>* available_heroes);
	~LadderTeam();

	/* Accessors */
	const Player* getPlayer(Position position) const;
	const bool hasEnoughPlayers() const;

	/* Modifiers */
	const bool addPlayer(Player* player, Position position);

	/* Pick and Ban Phase */
	void banHero(Position position);
	void selectHero(Position position);

	/* update */
	void update();
};

#endif // !LADDERTEAM_H