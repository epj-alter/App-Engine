#include "stdafx.h"
#include "Game.h"

namespace Engine
{
	/* Instance to NULL */
	Game* Game::sInstance = nullptr;

	void Game::initPhysics()
	{
		mPhysicsHandler->setLayerCollisionMask
		(
			PhysicsHandler::CollisionLayers::Friendly,
			PhysicsHandler::CollisionFlags::Hostile | PhysicsHandler::CollisionFlags::HostileProjectiles
		);
		mPhysicsHandler->setLayerCollisionMask
		(
			PhysicsHandler::CollisionLayers::FriendlyProjectiles,
			PhysicsHandler::CollisionFlags::Hostile
		);
		mPhysicsHandler->setLayerCollisionMask
		(
			PhysicsHandler::CollisionLayers::Hostile,
			PhysicsHandler::CollisionFlags::Friendly | PhysicsHandler::CollisionFlags::FriendlyProjectiles
		);
		mPhysicsHandler->setLayerCollisionMask
		(
			PhysicsHandler::CollisionLayers::HostileProjectiles,
			PhysicsHandler::CollisionFlags::Friendly
		);
	}

	/* Constructor / Destructor */
	Game::Game()
	{
		/* Core Variables */
		mGraphics = Graphics::Instance();
		if (!Graphics::initialized())
			mExitGame = true;

		mTimer = Timer::instance();
		mAssetsHandler = AssetsHandler::instance();
		mInputHandler = InputHandler::instance();
		mAudioHandler = AudioHandler::instance();
		mPhysicsHandler = PhysicsHandler::instance();
		mSceneHandler = SceneHandler::instance();
		mStyle = StylesHandler::instance();


		mEvent = &mInputHandler->getEvent();

		mMessageBox = MessageBox::instance();
		mConfirmExitBox = new ConfirmationBox("Do you really want to Exit the Game?");

		/* Primary Variables */
		//this->mEvents = SDL_Event();
		mExitGame = false;

		/* Physics */
		initPhysics();
	}

	Game::~Game()
	{
		delete mConfirmExitBox;
		mConfirmExitBox = nullptr;

		StylesHandler::release();
		mStyle = nullptr;

		MessageBox::release();
		mMessageBox = nullptr;

		SceneHandler::release();
		mSceneHandler = nullptr;

		PhysicsHandler::release();
		mPhysicsHandler = nullptr;

		AudioHandler::release();
		this->mAudioHandler = nullptr;

		AssetsHandler::release();
		this->mAssetsHandler = nullptr;

		Graphics::release();
		this->mGraphics = nullptr;

		InputHandler::release();
		this->mInputHandler = nullptr;

		Timer::release();
		this->mTimer = nullptr;

	}

	/* Private Core Functions */
	void Game::earlyUpdate()
	{
		this->mInputHandler->update();
	}

	void Game::update()
	{
		/* HERE WE UPDATE SCENES */
		mSceneHandler->update();

		if(mInputHandler->exitGame())
		{
			mConfirmExitBox->show();
			mConfirmExitBox->update();

			if (mConfirmExitBox->apply())
				mExitGame = true;

			if (!mConfirmExitBox->isShowing())
				mInputHandler->exitGame(false);
		}

		/*-----------------------------------*/
		//DEBUG
		//printf("Pos X: %f \n Pos Y: %f \n", this->mInputHandler->getMousePosition().x, this->mInputHandler->getMousePosition().y);
		//printf("Delta Time: %f\n", this->mTimer->getDeltaTime());
	}

	void Game::lateUpdate()
	{
		/* HERE WE UPDATE COLLISION AND STUFF */

		mPhysicsHandler->update();

		/*-----------------------------------*/

		this->mInputHandler->updatePreviousInput();
		this->mTimer->restart();
	}

	void Game::render()
	{
		this->mGraphics->clearBackBuffer();

		/* HERE WE RENDER EVERYTHING */
		mSceneHandler->render();

		if(mInputHandler->exitGame())
			mConfirmExitBox->render();
		/*---------------------------*/

		this->mGraphics->render();
	}

	/* Instance Functions */
	Game* Game::Instance()
	{
		if (sInstance == nullptr)
			sInstance = new Game();

		return sInstance;
	}

	void Game::release()
	{
		delete sInstance;
		sInstance = nullptr;

		//DEBUG
		printf("Game Exited Successfully.\n");
	}

	/* Core Functions */
	void Game::run()
	{
		while (!this->mExitGame)
		{
			this->mTimer->update();

			while (SDL_PollEvent(mEvent) != 0)
			{
				switch (mEvent->type)
				{
				case SDL_QUIT:
					mInputHandler->exitGame(true);
					break;

				case SDL_KEYDOWN:
					if (mEvent->key.keysym.sym == SDLK_BACKSPACE)
					{
						for (auto& mTbox : *mSceneHandler->getInputField())
						{
							if (mTbox.second->hasFocus())
								mTbox.second->removeText();
						}
					}
					else if (mEvent->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
					{
						for (auto& mTbox : *mSceneHandler->getInputField())
						{
							if (mTbox.second->hasFocus())
								SDL_SetClipboardText(mTbox.second->getText().c_str());
						}
					}
					else if (mEvent->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
					{
						for (auto& mTbox : *mSceneHandler->getInputField())
						{
							if (mTbox.second->hasFocus())
								mTbox.second->pasteText(SDL_GetClipboardText());
						}
					}
					break;

				case SDL_TEXTINPUT:

					if(!(SDL_GetModState() & KMOD_CTRL && (mEvent->text.text[0] == 'c' || mEvent->text.text[0] == 'C' || mEvent->text.text[0] == 'v' || mEvent->text.text[0] == 'V')))
					{
						for (auto& mTbox : *mSceneHandler->getInputField())
						{
							if (mTbox.second->hasFocus())
								mTbox.second->addText();
						}
					}
					break;
				}
			}

			if (this->mTimer->getDeltaTime() >= 1.0f / GraphicsSettings::FPS())
			{
				this->earlyUpdate();
				this->update();
				this->lateUpdate();
				this->render();
			}
		}
	}
}