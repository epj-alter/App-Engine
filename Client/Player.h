#ifndef PLAYER_H
#define PLAYER_H
#include "Person.h"

class Player : public Person
{
private:

	/* Professional Info */
	RoleProgression mRoles;
	Position mPosition;
	unsigned mRank;
	unsigned mValue;

	/* Contract Info */

	/* Status */
	bool mQueuedUP;
	Position mQueuedPosition;

	/* Attributes */
	PlayerAttributes* mPlayerAtt;

	/* Statistics */
	PlayerStatistics* mPlayerStats;

	//Averages 
	PlayerAverages* mPlayerAvgs;

	/* In Game Stuff */
	Hero* mSelectedHero;

public:

	/* Constructor / Destructor */
	Player(std::string ID);
	~Player();

	/* Accessors */
	const PlayerAttributes getPlayerAttribute() const;
	const Position getPosition() const;
	const bool isQueuedUp() const;
	const Position queuedPosition() const;
	const Hero* getHero() const;

	/* Modifiers */
	void setPosition(Position position);
	void setQueueStatus(bool queue_status);
	void setQueuePosition(Position queue_position);
	void setHero(Hero* selected_hero);

	/* Update */
	void update();
};

#endif // !PLAYER_H
