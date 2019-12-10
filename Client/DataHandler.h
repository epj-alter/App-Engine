#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "LadderSimulation.h"

namespace Engine
{
	typedef std::map<std::string, Hero*> aHeroMap;

	class DataHandler
	{
	private:

		static DataHandler* sInstance;

		/* Heroes Data loading and parsing */
		FILE* dFile;
		aHeroMap mHeroes;


		/* Initializer Functions */
		void initHeroesData();

		/* Constructor / Destructor */
		DataHandler();
		~DataHandler();

	public:

		static DataHandler* instance();
		static void release();

		const aHeroMap* getHeroesMap() const;
		const Hero* getHero(std::string hero_id) const;
	};
}

#endif // !DATAHANDLER_H