#ifndef PERSONHANDLER_H
#define PERSONHANDLER_H
#include "Player.h"

class PlayerBase
{
private:

	std::vector<Player*> mPlayerBase;

public:

	PlayerBase(unsigned players_count);
	~PlayerBase();

	/* Accessors */
	const std::vector<Player*> & getPlayerBase() const;

	/* Modifiers */
	void shuffle();

	/* Core Functions */
	void update();
};

#endif //

