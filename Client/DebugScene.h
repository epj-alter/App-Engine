#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H
#include "LoaderScene.h"

namespace Engine
{
	class DebugScene : public Scene
	{
	private:

		DataHandler* mDataHandler;
		LadderSimulation* mLadderSimulation;
		PlayerBase* mPlayerBase;

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
