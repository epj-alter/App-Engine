#ifndef PERSON_H
#define PERSON_H
#include "Hero.h"
class Team;

class Person
{
protected:
	
	/* Essential */
	std::string mID;

	/* Basic Info */
	std::string mName;
	std::string mAlias;
	unsigned mAge;
	Calendar mBirthday;
	//Languages mLanguages;
	Nation mNationality;
	Nation mCitizenship;

	/* Contract Info */
	Team* mTeam; //DEBUG

public:

	/* Constructor / Destructor */
	Person(std::string ID);
	virtual ~Person() = 0;

	/* Accessors */
	const std::string getID() const;
	const std::string getName() const;
	const std::string getAlias() const;
	const unsigned getAge() const;
	const Team* getTeam() const;

	/* Modifiers */
	void setTeam(Team* team);

	/* Update */
	virtual void update() = 0;
};


#endif // !PERSON_H

