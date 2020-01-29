#ifndef MATCH_H
#define MATCH_H
#include "ProTeam.h"

namespace Core
{
	class Match
	{
	protected:

		/* Basic info*/
		std::string mID;
		MatchType mType;
		unsigned mDuration;

		/* Team infos */

	public:

		/* Constructor / Destructor */
		Match();
		virtual ~Match() = 0;

		/* Modifiers */
		void setID(std::string ID);
	};
}

#endif
