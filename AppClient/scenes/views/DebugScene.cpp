#include "DebugScene.h"

namespace Client
{
	/* Private Functions */
	void DebugScene::init()
	{
		
	}

	/* Constructor / Destructor */
	DebugScene::DebugScene()
		: Scene("debug_scene", SCENE_ID::debug_scene)
	{
		mButton1 = new GUI::Button(this, "Simulate", 100, 100, 100, 20);

		std::thread t1(&DebugScene::init, this);
		t1.detach();
		//t1.join(); waits for it to finish..
	}

	DebugScene::~DebugScene()
	{
		delete mButton1;
		mButton1 = nullptr;
	}

	/* Interface Functions */
	void DebugScene::updateInterface()
	{
		mButton1->update();
	}

	void DebugScene::renderInterface()
	{
		mButton1->render();
	}

	/* Core Functions */
	void DebugScene::updateInput()
	{
		if (!mWritting)
		{
			if (mInput->keyPressed(mKeyMap.at("MOVE_UP")))
			{
				
			}
			if (mInput->keyPressed(mKeyMap.at("MOVE_DOWN")))
			{
				
			}
		}
	}

	void DebugScene::update()
	{
		if (!mMessageBox->isShowing())
		{
			updateInput();
			updateInterface();
		}
		else
		{
			mMessageBox->update();
		}
	}

	void DebugScene::render()
	{
		renderInterface();
	}
}