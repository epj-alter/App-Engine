#include "stdafx.h"
#include "SceneHandler.h"

namespace Engine
{
	SceneHandler* SceneHandler::sInstance = nullptr;

	void SceneHandler::initScenes()
	{
		mSceneData = SceneData::instance();
		mScenes.push(new LoaderScene());
	}

	/* Constructor / Destructor */
	SceneHandler::SceneHandler()
	{
		initScenes();
	}

	SceneHandler::~SceneHandler()
	{

		/* Clearing Scene Stack */
		while (!mScenes.empty())
		{
			delete mScenes.top();
			mScenes.top() = nullptr;
			mScenes.pop();
		}

		SceneData::release();
		mSceneData = nullptr;
	}

	/* Instance Handler */
	SceneHandler* SceneHandler::instance()
	{		
		if (sInstance == nullptr)
			sInstance = new SceneHandler();

		return sInstance;
	}

	void SceneHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}
	
	/* Scene Accessors */
	aInputFieldMap* SceneHandler::getInputField()
	{
		return mScenes.top()->getInputField();
	}

	/* Core Functions */
	void SceneHandler::update()
	{
		if (!mScenes.empty())
		{
			mScenes.top()->updateInputLock();
			mScenes.top()->update();
			
			/* Core updates */
			if (mScenes.top()->closeScene())
			{
				switch (mScenes.top()->getID())
				{
				case Scene::load_scene:

					delete mScenes.top();
					mScenes.top() = nullptr;
					mScenes.pop();
					mScenes.push(new DebugScene());
					break;

				case Scene::debug_scene:

					delete mScenes.top();
					mScenes.top() = nullptr;
					mScenes.pop();
					break;
				}
			}
		}
	}

	void SceneHandler::render()
	{
		if (!mScenes.empty())
		{
			mScenes.top()->render();
		}
	}
}
