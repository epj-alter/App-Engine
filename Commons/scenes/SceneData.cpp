#include "SceneData.h"

namespace GUI
{
	SceneData* SceneData::sInstance = nullptr;

	bool SceneData::loadSupportedKeys()
	{
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Data/SupportedKeys.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);
				const rapidjson::Value& text_array = d["supported_keys"];

				for (int i = 0; i < text_array.Size(); i++)
				{
					mSupportedKeys.insert({ text_array[i]["key"].GetString(), static_cast<SDL_Scancode>(text_array[i]["id"].GetInt()) });
					if (mSupportedKeys.at(text_array[i]["key"].GetString()) == NULL)
					{
						printf("SCENEDATA::LoadSupportedKeys Could not insert key '%s' into array\n", text_array[i]["key"].GetString());
						return false;
					}
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
				else
					return false;
			}
			else
			{
				printf("SCENEDATA::LoadSupportedKeys Could not load File '%s'\n", full_path.c_str());
				return false;
			}
		}
		else
			return false;
		return true;
	}

	bool SceneData::loadSounds()
	{
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Data/Sounds.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);
				const rapidjson::Value& music_array = d["music"];
				const rapidjson::Value& sfx_array = d["sfx"];

				mNumberofAssets = d["assets"].GetInt();

				for (int i = 0; i < music_array.Size(); i++)
				{
					mAssetsHandler->loadMusic(music_array[i]["path"].GetString());
					sMusic.insert({ music_array[i]["key"].GetString(), music_array[i]["path"].GetString() });

					mAssetsLoadedCount++;
				}

				for (int i = 0; i < sfx_array.Size(); i++)
				{
					mAssetsHandler->loadSFX(music_array[i]["path"].GetString());
					sSFX.insert({ sfx_array[i]["key"].GetString(), sfx_array[i]["path"].GetString() });

					mAssetsLoadedCount++;
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
			}
			else
			{
				printf("SCENEDATA::loadSounds Could not load File '%s'\n", full_path.c_str());
				return false;
			}
		}
		else
			return false;
		return true;
	}

	bool SceneData::loadTextures()
	{
		/* Parsing File */
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Data/Textures.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);
				const rapidjson::Value& text_array = d["debug_textures"];

				for (int i = 0; i < text_array.Size(); i++)
				{
					mAssetsHandler->loadTexture(text_array[i]["path"].GetString());
					sTextures.insert({ text_array[i]["key"].GetString(), text_array[i]["path"].GetString() });

					mAssetsLoadedCount++;
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
				else
					return false;
			}
			else
			{
				printf("SCENEDATA::LoadDebugTextures Could not load File '%s'\n", full_path.c_str());
				return false;
			}
		}
		else
			return false;
		return true;
	}

	/* Constructor / Destructor */
	SceneData::SceneData()
	{
		mNumberofAssets = 0;
		mAssetsLoadedCount = 0;

		dFile = nullptr;

		mAssetsHandler = AssetsHandler::instance();

		mLoadComplete = false;

		if (loadSupportedKeys() && loadSounds() && loadTextures())
			mLoadComplete = true;
		else
			printf("SCENEDATA::ERROR Could not load assets\n");
	}

	SceneData::~SceneData()
	{
		dFile = nullptr;
		mAssetsHandler = nullptr;

		sMusic.clear();
		sSFX.clear();
		sTextures.clear();/*
		sPlayerTextures.clear();
		sNPCTextures.clear();
		sMonsterTextures.clear();*/
		mSupportedKeys.clear();
	}

	SceneData* SceneData::instance()
	{
		if (sInstance == nullptr)
			sInstance = new SceneData();

		return sInstance;
	}

	void SceneData::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	const unsigned int& SceneData::getNumberOfAssets() const
	{
		return mNumberofAssets;
	}

	const unsigned int& SceneData::getAssetsLoadedCount() const
	{
		return mAssetsLoadedCount;
	}

	const bool SceneData::loadCompleted() const
	{
		return mLoadComplete;
	}

	SDL_Scancode SceneData::getKeyCode(std::string key) const
	{
		return mSupportedKeys.at(key);
	}

	std::string SceneData::getTexture(std::string key) const
	{
		return sTextures.at(key);
	}

	std::string SceneData::getMusic(std::string key) const
	{
		return sMusic.at(key);
	}

	std::string SceneData::getSFX(std::string key) const
	{
		return sSFX.at(key);
	}
}