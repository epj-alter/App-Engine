#ifndef TEAM_H
#define TEAM_H
#include "PersonHandler.h"

class Team
{
protected:

	/* Team Variables */
	unsigned mID;
	TeamType mType; //TODO
	std::string mName;


	/* Attributes */
	unsigned mAvgELO;

public:

	/* Constructor / Destructor */
	Team();
	virtual ~Team() = 0;

	/* Accessors */
	const unsigned getID() const;
	const TeamType getType() const;
	const std::string getName() const;
	const unsigned getELO() const;

	/* Modifiers */
	void setName(std::string name);
	void setTeamType(TeamType type);

	virtual void update() = 0;
};

#endif // !TEAM_H

