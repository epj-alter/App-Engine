#ifndef PROTEAM_H
#define PROTEAM_H
#include "LadderTeam.h"

namespace Core
{
	class ProTeam : public Team
	{
	private:

		/* Squad / Selection */
		// std::vector<Staff*> mStaff
		std::vector<Player*> mSquad;
		std::map<TeamSelection, Player*> mTeamSelection;

		bool mSelectionDone;

	public:

		/* Constructor */
		ProTeam();
		~ProTeam();

		/* Accessors */
		const Player* getPlayer(TeamSelection position) const;

		/* Modifiers */
		void addPlayer(Player* player);
		void setSelection(Player* player, TeamSelection position);

		/* Update */
		void update();
	};
}
#endif // !#PROTEAM_H