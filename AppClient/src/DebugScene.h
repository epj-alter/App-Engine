#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H
#include "LoaderScene.h"

namespace Client
{
	class DebugScene : public GUI::Scene
	{
	private:

		Core::DataHandler* mDataHandler;
		Core::LadderSimulation* mLadderSimulation;

		GUI::Button* mButton1;

		void init();

	public:

		DebugScene();
		~DebugScene();

		void updateInterface();
		void renderInterface();

		void updateInput();
		void update();
		void render();
	};
}

#endif
