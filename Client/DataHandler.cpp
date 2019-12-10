#include "stdafx.h"
#include "DataHandler.h"

namespace Engine
{
	/* instance to nullptr */
	DataHandler* DataHandler::sInstance = nullptr;

	void DataHandler::initHeroesData()
	{
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Data/Heroes.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);
				const rapidjson::Value& heroes_array = d["Heroes"];

				for (int i = 0; i < heroes_array.Size(); i++)
				{
					mHeroes.insert({heroes_array[i]["id"].GetString(),
						new Hero(
							heroes_array[i]["name"].GetString(), heroes_array[i]["id"].GetString(), 
							heroes_array[i]["priority"].GetUint(), heroes_array[i]["class"].GetUint(),
							heroes_array[i]["strong1"].GetUint(), heroes_array[i]["strong2"].GetUint(), heroes_array[i]["strong3"].GetUint(),
							heroes_array[i]["weak1"].GetUint(), heroes_array[i]["weak2"].GetUint(), heroes_array[i]["weak3"].GetUint(),
							heroes_array[i]["bstrength"].GetUint(), heroes_array[i]["bconstitution"].GetUint(), heroes_array[i]["bintellect"].GetUint(),
							heroes_array[i]["bmentality"].GetUint(), heroes_array[i]["bdexterity"].GetUint(), heroes_array[i]["blethality"].GetUint(),
							heroes_array[i]["sstrength"].GetUint(), heroes_array[i]["sconstitution"].GetUint(), heroes_array[i]["sintellect"].GetUint(),
							heroes_array[i]["smentality"].GetUint(), heroes_array[i]["sdexterity"].GetUint(), heroes_array[i]["slethality"].GetUint(),
							heroes_array[i]["aoe"].GetUint(), heroes_array[i]["burst"].GetUint(), heroes_array[i]["cc"].GetUint(),
							heroes_array[i]["mobility"].GetUint(), heroes_array[i]["range"].GetUint()
							)});

					if (mHeroes.at(heroes_array[i]["id"].GetString()) == nullptr)
					{
						printf("DATAHANDLER::initHeroes Could not load hero '%s' into array\n", heroes_array[i]["id"].GetString());
					}
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
			}
			else
			{
				printf("DATAHANDLER::initHeroes Could not load File '%s'\n", full_path.c_str());
			}
		}
	}

	Engine::DataHandler::DataHandler()
	{
		dFile = nullptr;
		initHeroesData();
	}

	Engine::DataHandler::~DataHandler()
	{
		for (auto & itr : mHeroes)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mHeroes.clear();

		dFile = nullptr;
	}

	DataHandler* Engine::DataHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new DataHandler();

		return sInstance;
	}

	void Engine::DataHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	const aHeroMap* DataHandler::getHeroesMap() const
	{
		return &mHeroes;
	}

	const Hero* DataHandler::getHero(std::string hero_id) const
	{
		return mHeroes.at(hero_id);
	}
}
