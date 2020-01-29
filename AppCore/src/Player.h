#ifndef PLAYER_H
#define PLAYER_H
#include "Person.h"

namespace Core
{
	class Player : public Person
	{
	private:


		/* Professional Info */
		Position mPosition;
		unsigned mRank;
		unsigned mValue;

		/* Contract Info */

		/* Status */
		bool mQueuedUP;
		Position mQueuedPosition;

		/* Statistics */
		PlayerAttributes* mPlayerAtt;
		PlayerStatistics* mPlayerStats;
		PlayerAverages* mPlayerAvgs;

		/* Hero related */
		std::map<unsigned, unsigned, std::greater<unsigned>> mHeroProgression;	//(hero_id, experience_with_hero)
		std::map<unsigned, unsigned, std::greater<unsigned>> mFavouriteHeroes;	//(hero_id, times played with hero)
		std::map<unsigned, unsigned, std::greater<unsigned>> mHatedHeroes;		//(hero_id, times played against hero)
		std::map<unsigned, unsigned, std::greater<unsigned>> mHeroesToPractice;	//(hero_id, priority of training)

	public:

		/* Constructor / Destructor */
		Player(std::string ID);
		~Player();

		/* Accessors */
		const PlayerAttributes getPlayerAttribute() const;
		const Position getPosition() const;
		const bool isQueuedUp() const;
		const Position queuedPosition() const;
		const std::vector<unsigned> getBestHeroesID() const;
		const std::vector<unsigned> getFavouriteHeroesID() const;
		const std::vector<unsigned> getHatedHeroesID() const;
		const std::vector<unsigned> getHeroesToPractice() const;

		/* Modifiers */
		void setPosition(Position position);
		void setQueueStatus(bool queue_status);
		void setQueuePosition(Position queue_position);

		/* Pick & Ban Phase */
		void insertHeroPractice(unsigned hero_id, unsigned priority);
		void removeHeroPractice(unsigned hero_id);

		/* Update */
		void update();
	};
}

#endif // !PLAYER_H
