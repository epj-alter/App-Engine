#ifndef LOADER_H
#define LOADER_H
#include "DebugScene.h"

namespace Engine
{
	class SceneHandler
	{
	private:
		static SceneHandler* sInstance;

		/* Variables */
		SceneData* mSceneData;
		std::stack<Scene*> mScenes;

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
		aInputFieldMap* getInputField();

		/* Core Functions */
		void update();
		void render();

	};
}

#endif