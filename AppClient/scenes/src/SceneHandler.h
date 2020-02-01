#ifndef SCENEHANDLER_H
#define SCENEHANDLER_H
#include "../views/DebugScene.h"

namespace Client
{
	class SceneHandler
	{
	private:
		static SceneHandler* sInstance;

		/* Variables */
		GUI::SceneData* mSceneData;
		std::stack<GUI::Scene*> mScenes;

		/* Initializer */
		void initScenes();

		/* Constructor / Destructor */
		SceneHandler();
		~SceneHandler();

	public:
		/* Instance Handler */
		static SceneHandler* instance();
		static void release();

		/* Scene Accessors */
		GUI::aInputFieldMap* getInputField();

		/* Core Functions */
		void update();
		void render();

	};
}

#endif