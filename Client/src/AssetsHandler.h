#ifndef ASSETSHANDLER_H
#define ASSETSHANDLER_H

namespace Engine
{
	class AssetsHandler
	{
	private:

		static AssetsHandler* sInstance;

		aTextureMap mTextures;
		aTextureMap mTexts;
		aFontMap mFont;
		aMusicMap mMusic;
		aSFXMap mSFX;

		/* Constructor / Destructor */
		AssetsHandler();
		~AssetsHandler();

		/* Functions */
		TTF_Font* getFont(std::string file_name, int size);

	public:

		/* Instance Functions */
		static AssetsHandler* instance();
		static void release();

		/* Accessors */
		SDL_Texture* getTexture(std::string file_name);
		SDL_Texture* getText(std::string text, std::string file_name, int size, SDL_Color color);
		Mix_Music* getMusic(std::string file_name);
		Mix_Chunk* getSFX(std::string file_name);

		/* Initializers */
		void loadTexture(std::string file_name);
		void loadMusic(std::string file_name);
		void loadSFX(std::string file_name);

	};
}

#endif