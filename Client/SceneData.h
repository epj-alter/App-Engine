#ifndef SCENEDATA_H
#define SCENEDATA_H

namespace Engine
{
	class SceneData
	{
	public:

	private:
		/* Instance Variable */
		static SceneData* sInstance;
		FILE* dFile;

		bool mLoadComplete;

		unsigned int mNumberofAssets;
		unsigned int mAssetsLoadedCount;

		/* private */
		AssetsHandler* mAssetsHandler;

		/* Input Map */
		aKeyMap mSupportedKeys;

		/* Audio Maps */
		aStringMap sMusic;
		aStringMap sSFX;

		/* Texture Maps */
		aStringMap sTextures;/*
		aStringMap sPlayerTextures;
		aStringMap sNPCTextures;
		aStringMap sMonsterTextures;*/

		/* Audio Maps */

		/* Loader Functions */
		bool loadSupportedKeys();
		bool loadSounds();
		bool loadTextures();

		/* Constructor / Destructor */
		SceneData();
		~SceneData();

	public:

		/* Instance Functions */
		static SceneData* instance();
		static void release();

		/* Accessors */
		const unsigned int & getNumberOfAssets() const;
		const unsigned int & getAssetsLoadedCount() const;
		const bool loadCompleted() const;
		SDL_Scancode getKeyCode(std::string key) const;
		std::string getTexture(std::string key) const;
		std::string getMusic(std::string key) const;
		std::string getSFX(std::string key) const;
	};
}

#endif // !SCENEDATA_H
