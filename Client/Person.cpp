#include "stdafx.h"
#include "Person.h"

/* Constructor Destructor */
Person::Person(std::string ID)
{
	mID = ID;
	mAge = 0;
	mTeam = nullptr;
}

Person::~Person()
{
	mTeam = nullptr;
}

/* Accessors */
const std::string Person::getID() const
{
	return mID;
}

const std::string Person::getName() const
{
	return mName;
}

const std::string Person::getAlias() const
{
	return mAlias;
}

const unsigned Person::getAge() const
{
	return mAge;
}

const Team* Person::getTeam() const
{
	return mTeam;
}

/* Modifiers */
void Person::setTeam(Team* team)
{
	mTeam = team;
}

/* Update */
void Person::update()
{
}
