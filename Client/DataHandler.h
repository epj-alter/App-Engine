#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "LadderSimulation.h"

namespace Engine
{
	typedef std::map<unsigned, Hero*> aHeroMap;

	class DataHandler
	{
	private:

		static DataHandler* sInstance;

		/* Heroes Data Base loading and parsing */
		FILE* dFile;
		aHeroMap mHeroes;

		/* Players DataBase and variables */
		std::vector<Player*> mPlayers;
		unsigned mDataBaseSize;

		/* Initializer Functions */
		void initHeroesData();
		void initPlayersDataBase();

		/* Constructor / Destructor */
		DataHandler();
		~DataHandler();

	public:

		/* Instance Functions */
		static DataHandler* instance();
		static void release();

		/* Accessors */
		aHeroMap* getHeroesDB();
		std::vector<Player*>* getPlayersDB();
		const Hero* getHero(unsigned hero_id) const;

		/* Modifier Functions */
		void setDatabaseSize(unsigned db_size);
		void shuffle();
		void update();
	};
}

#endif // !DATAHANDLER_H