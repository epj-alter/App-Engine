#ifndef GAME_H
#define GAME_H
#include "SceneHandler.h"

namespace Engine
{
	class Game
	{
	private:

		/* Static Instances */
		static Game* sInstance;
		SDL_Event* mEvent;

		/* Core Variables */
		Timer* mTimer;
		Graphics* mGraphics;
		AssetsHandler* mAssetsHandler;
		InputHandler* mInputHandler;
		AudioHandler* mAudioHandler;
		PhysicsHandler* mPhysicsHandler;
		SceneHandler* mSceneHandler;
		StylesHandler* mStyle;

		/* Various */
		MessageBox* mMessageBox;
		ConfirmationBox* mConfirmExitBox;

		/* Primary Variables */
		//SDL_Event mEvents;
		bool mExitGame;

		/* Added Variables */


		/* Physics */
		void initPhysics();

		/* Constructor / Destructor */
		Game();
		~Game();

		/* Private Core Functions */
		void earlyUpdate();
		void update();
		void lateUpdate();
		void render();

	public:

		/* Instance Functions */
		static Game* Instance();
		static void release();

		/* Core Functions */
		void run();
	};
}
#endif