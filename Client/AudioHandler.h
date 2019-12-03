#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

namespace Engine
{
	class AudioHandler
	{
	private:

		static AudioHandler* sInstance;
		AssetsHandler* mAssetsHandler;

		/* Constructor / Destructor */
		AudioHandler();
		~AudioHandler();

	public:

		/* Instance Functions */
		static AudioHandler* instance();
		static void release();

		/* Music Functions */
		void playMusic(std::string file_name, int loops = -1);
		void pauseMusic();
		void resumeMusic();

		/* SFX Functions */
		void playSFX(std::string file_name, int loops = 0, int channel = 0);


	};
}

#endif