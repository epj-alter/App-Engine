#ifndef GAME_H
#define GAME_H
#include "SceneHandler.h"

namespace Client
{
	class Client
	{
	private:

		/* Static Instances */
		static Client* sInstance;
		SDL_Event* mEvent;

		/* Core Variables */
		Timer* mTimer;
		Graphics* mGraphics;
		AssetsHandler* mAssetsHandler;
		InputHandler* mInputHandler;
		AudioHandler* mAudioHandler;
		PhysicsHandler* mPhysicsHandler;
		SceneHandler* mSceneHandler;
		GUI::StylesHandler* mStyle;
		Core::DataHandler* mDataHandler;

		/* Various */
		GUI::MessageBox* mMessageBox;
		GUI::ConfirmationBox* mConfirmExitBox;

		/* Primary Variables */
		//SDL_Event mEvents;
		bool mExitGame;

		/* Added Variables */


		/* Physics */
		void initPhysics();

		/* Constructor / Destructor */
		Client();
		~Client();

		/* Private Core Functions */
		void earlyUpdate();
		void update();
		void lateUpdate();
		void render();

	public:

		/* Instance Functions */
		static Client* Instance();
		static void release();

		/* Core Functions */
		void run();
	};
}
#endif