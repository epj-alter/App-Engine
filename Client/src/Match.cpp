#include "stdafx.h"
#include "Match.h"

/* Constructor / Destructor */
Match::Match()
{
	mDuration = 0;
}

Match::~Match()
{
}

/* Modifiers */
void Match::setID(std::string ID)
{
	mID = ID;
}
