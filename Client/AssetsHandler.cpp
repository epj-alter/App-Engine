#include "stdafx.h"
#include "AssetsHandler.h"

namespace Engine
{
	/* instance to nullptr */
	AssetsHandler* AssetsHandler::sInstance = nullptr;

	/* Constructor / Destructor */
	AssetsHandler::AssetsHandler()
	{
	}

	AssetsHandler::~AssetsHandler()
	{
		//textures
		for (auto textures : this->mTextures)
		{
			if (textures.second != nullptr)
			{
				SDL_DestroyTexture(textures.second);
			}
		}

		this->mTextures.clear();

		//texts
		for (auto text : this->mTexts)
		{
			if (text.second != nullptr)
			{
				SDL_DestroyTexture(text.second);
			}
		}

		this->mTexts.clear();

		//fonts
		for (auto font : this->mFont)
		{
			if (font.second != nullptr)
			{
				TTF_CloseFont(font.second);
			}
		}

		this->mFont.clear();

		//music
		for (auto music : this->mMusic)
		{
			if (music.second != nullptr)
			{
				Mix_FreeMusic(music.second);
			}
		}

		this->mMusic.clear();

		//SFX
		for (auto sfx : this->mSFX)
		{
			if (sfx.second != nullptr)
			{
				Mix_FreeChunk(sfx.second);
			}
		}

		this->mSFX.clear();
	}

	/* Functions */
	TTF_Font* AssetsHandler::getFont(std::string file_name, int size)
	{
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + file_name);

		std::string key = fullpath + static_cast<char>(size);

		if (this->mFont[key] == nullptr)
		{
			this->mFont.at(key) = TTF_OpenFont(fullpath.c_str(), size);
			if (this->mFont[key] == nullptr)
			{
				printf("Font Loading Error: %s\n", TTF_GetError());
				return nullptr;
			}
		}

		return this->mFont.at(key);
	}

	/* Instance Functions */
	AssetsHandler* AssetsHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new AssetsHandler();

		return sInstance;
	}

	void AssetsHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	/* Accessors */
	SDL_Texture* AssetsHandler::getTexture(std::string file_name)
	{
		std::string full_path = SDL_GetBasePath();
		full_path.append("Assets/" + file_name);

		if (this->mTextures[full_path] == nullptr)
		{
			this->mTextures.at(full_path) = Graphics::Instance()->loadTexture(full_path);
			if (this->mTextures[full_path] == nullptr)
			{
				printf("Texture Loading Error: Texture-%s\n Error-%s\n", full_path.c_str(), SDL_GetError());
				return nullptr;
			}
		}

		return this->mTextures.at(full_path);
	}

	SDL_Texture* AssetsHandler::getText(std::string text, std::string file_name, int size, SDL_Color color)
	{

		TTF_Font* font = getFont(file_name, size);

		std::string key =
			text + file_name +
			static_cast<char>(size) +
			static_cast<char>(color.r) +
			static_cast<char>(color.g) +
			static_cast<char>(color.b);

		if (this->mTexts[key] == nullptr)
		{
			this->mTexts.at(key) = Graphics::Instance()->createTextTexture(font, text, color);
			if (this->mTexts[key] == nullptr)
			{
				printf("Text Loading Error: text-%s\n Error-%s\n", key.c_str(), TTF_GetError());
				return nullptr;
			}

		}

		return this->mTexts.at(key);
	}

	Mix_Music* AssetsHandler::getMusic(std::string file_name)
	{
		std::string full_path = SDL_GetBasePath();
		full_path.append("Assets/" + file_name);

		if (this->mMusic[full_path] == nullptr)
		{
			this->mMusic.at(full_path) = Mix_LoadMUS(full_path.c_str());
			if (this->mMusic[full_path] == nullptr)
			{
				printf("Music Loading Error: Music File-%s\n Error-%s\n", file_name.c_str(), Mix_GetError());
				return nullptr;
			}
		}

		return this->mMusic.at(full_path);
	}

	Mix_Chunk* AssetsHandler::getSFX(std::string file_name)
	{
		std::string full_path = SDL_GetBasePath();
		full_path.append("Assets/" + file_name);

		if (this->mSFX[full_path] == nullptr)
		{
			this->mSFX.at(full_path) = Mix_LoadWAV(full_path.c_str());
			if (this->mSFX[full_path] == nullptr)
			{
				printf("SFX Loading Error: SFX File-%s\n Error-%s\n", file_name.c_str(), Mix_GetError());
				return nullptr;
			}
		}

		return this->mSFX.at(full_path);
	}

	/* Initializers */
	void AssetsHandler::loadTexture(std::string file_name)
	{
		std::string full_path = SDL_GetBasePath();
		full_path.append("Assets/" + file_name);

		if (this->mTextures[full_path] == nullptr)
		{
			this->mTextures.at(full_path) = Graphics::Instance()->loadTexture(full_path);
			if (this->mTextures[full_path] == nullptr)
			{
				printf("Texture Loading Error: Texture-%s\n Error-%s\n", full_path.c_str(), SDL_GetError());
			}
		}
	}

	void AssetsHandler::loadMusic(std::string file_name)
	{
		std::string full_path = SDL_GetBasePath();
		full_path.append("Assets/" + file_name);

		if (this->mMusic[full_path] == nullptr)
		{
			this->mMusic.at(full_path) = Mix_LoadMUS(full_path.c_str());
			if (this->mMusic[full_path] == nullptr)
			{
				printf("Music Loading Error: Music File-%s\n Error-%s\n", file_name.c_str(), Mix_GetError());
			}
		}
	}

	void AssetsHandler::loadSFX(std::string file_name)
	{
		std::string full_path = SDL_GetBasePath();
		full_path.append("Assets/" + file_name);

		if (this->mSFX[full_path] == nullptr)
		{
			this->mSFX.at(full_path) = Mix_LoadWAV(full_path.c_str());
			if (this->mSFX[full_path] == nullptr)
			{
				printf("SFX Loading Error: SFX File-%s\n Error-%s\n", file_name.c_str(), Mix_GetError());
			}
		}
	}
}
