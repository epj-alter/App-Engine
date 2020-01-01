#include "stdafx.h"
#include "DebugScene.h"

namespace Engine
{
	/* Private Functions */
	void DebugScene::init()
	{
		mDataHandler = DataHandler::instance();
		mDataHandler->setDatabaseSize(500);

		//printf("ELO 1: %i \n", mTeam->getPerson(Engine::Selection::TOP)->getPlayerAttribute().ELO);
		//printf("ELO 2: %i \n", mTeam->getPerson(Engine::Selection::MIDDLE)->getPlayerAttribute().ELO);
		//printf("TEAM ELO: %i \n", mTeam->getELO());

		mLadderSimulation = new LadderSimulation();
	}

	/* Constructor / Destructor */
	DebugScene::DebugScene()
		: Scene("debug_scene", Scene::debug_scene)
	{
		std::thread t1(&DebugScene::init, this);
		t1.detach();
		//t1.join(); waits for it to finish..
	}

	DebugScene::~DebugScene()
	{
		mDataHandler = nullptr;

		delete mLadderSimulation;
		mLadderSimulation = nullptr;
	}

	/* Interface Functions */
	void DebugScene::updateInterface()
	{
	}

	void DebugScene::renderInterface()
	{
		
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