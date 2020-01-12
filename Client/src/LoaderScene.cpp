#include "stdafx.h"
#include "LoaderScene.h"

LoaderScene::LoaderScene()
	: Scene("load_scene", Scene::SCENE_ID::load_scene)
{
	mNumberofAssets = &mSceneData->getNumberOfAssets();
	mAssetsLoadedCount = &mSceneData->getAssetsLoadedCount();

	mContinueLabel = new Texture("'Press Enter to Continue'", mStyles->font("default"), 16, mStyles->color("neutral"));
	mContinueLabel->setParent(this);
	mContinueLabel->setCenterPos(Vector2(GraphicsSettings::get().width * 0.5f, GraphicsSettings::get().height * 0.7f));

	mAlpha = 0;
	mReverseAlpha = false;
}

LoaderScene::~LoaderScene()
{
}

void LoaderScene::updateInterface()
{
}

void LoaderScene::renderInterface()
{
}

void LoaderScene::updateInput()
{
	if (mSceneData->loadCompleted())
	{
		if (mInput->keyPressed(SDL_SCANCODE_RETURN) || mInput->keyPressed(SDL_SCANCODE_SPACE))
		{
			mCloseScene = true;
		}
	}
}

void LoaderScene::update()
{
	mContinueLabel->setAlpha(mAlpha);

	if (!mReverseAlpha)
	{
		mAlpha += 80 * mTimer->getDeltaTime();
		if (mAlpha >= 255)
		{
			mAlpha = 255;
			mReverseAlpha = true;
		}
	}
	else
	{
		mAlpha -= 80 * mTimer->getDeltaTime();
		if (mAlpha <= 0)
		{
			mAlpha = 0;
			mReverseAlpha = false;
		}
	}

	updateInput();
}

void LoaderScene::render()
{
	mContinueLabel->render();
}
