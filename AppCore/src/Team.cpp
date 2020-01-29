#include "Team.h"

namespace Core
{
	/* Constructor / Destructor */
	Team::Team()
	{
		mID = 25; //DEBUG
		mAvgELO = 0;
	}
	
	Team::~Team()
	{
	}
	
	/* Accessors */
	const unsigned Team::getID() const
	{
		return mID;
	}
	
	const TeamType Team::getType() const
	{
		return mType;
	}
	
	const std::string Team::getName() const
	{
		return mName;
	}
	
	const unsigned Team::getELO() const
	{
		return mAvgELO;
	}
	
	/* Modifiers */
	void Team::setName(std::string name)
	{
		mName = name;
	}
	
	void Team::setTeamType(TeamType type)
	{
		mType = type;
	}
	
	/* Update */
	void Team::update()
	{
	}
}
