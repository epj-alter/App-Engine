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
				const rapidjson::Value& heroes = d["Heroes"];

				for (int i = 0; i < heroes.Size(); i++)
				{
					mHeroes.insert({heroes[i]["id"].GetString(),
						new Hero(
							heroes[i]["name"].GetString(), heroes[i]["id"].GetString(), 
							heroes[i]["priority"].GetUint(), heroes[i]["class"].GetUint(),
							heroes[i]["strong1"].GetUint(), heroes[i]["strong2"].GetUint(), heroes[i]["strong3"].GetUint(),
							heroes[i]["weak1"].GetUint(), heroes[i]["weak2"].GetUint(), heroes[i]["weak3"].GetUint(),
							heroes[i]["bstrength"].GetUint(), heroes[i]["bconstitution"].GetUint(), heroes[i]["bintellect"].GetUint(),
							heroes[i]["bmentality"].GetUint(), heroes[i]["bdexterity"].GetUint(), heroes[i]["blethality"].GetUint(),
							heroes[i]["sstrength"].GetUint(), heroes[i]["sconstitution"].GetUint(), heroes[i]["sintellect"].GetUint(),
							heroes[i]["smentality"].GetUint(), heroes[i]["sdexterity"].GetUint(), heroes[i]["slethality"].GetUint(),
							heroes[i]["aoe"].GetUint(), heroes[i]["burst"].GetUint(), heroes[i]["cc"].GetUint(),
							heroes[i]["mobility"].GetUint(), heroes[i]["range"].GetUint()
							)});

					if (mHeroes.at(heroes[i]["id"].GetString()) == nullptr)
					{
						printf("DATAHANDLER::initHeroes Could not load hero '%s' into array\n", heroes[i]["id"].GetString());
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
