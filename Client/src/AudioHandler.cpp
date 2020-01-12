#include "stdafx.h"
#include "AudioHandler.h"

namespace Engine
{	
	/* Instance to NULL */
	AudioHandler* AudioHandler::sInstance = nullptr;

	/* Constructor / Destructor */
	AudioHandler::AudioHandler()
	{
		this->mAssetsHandler = AssetsHandler::instance();

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			printf("Mixer Initialization Error: %s\n", Mix_GetError());
		}
	}

	AudioHandler::~AudioHandler()
	{
		this->mAssetsHandler = nullptr;
		Mix_Quit();
	}

	/* Instance Functions */
	AudioHandler* AudioHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new AudioHandler();

		return sInstance;
	}

	void AudioHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	/* Music Functions */
	void AudioHandler::playMusic(std::string file_name, int loops)
	{
		Mix_PlayMusic(this->mAssetsHandler->getMusic(file_name), loops);
	}

	void AudioHandler::pauseMusic()
	{
		if (Mix_PlayingMusic() != 0)
			Mix_PauseMusic();
	}

	void AudioHandler::resumeMusic()
	{
		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
	}

	/* SFX Functions */
	void AudioHandler::playSFX(std::string file_name, int loops, int channel)
	{
		Mix_PlayChannel(channel, this->mAssetsHandler->getSFX(file_name), loops);
	}
}