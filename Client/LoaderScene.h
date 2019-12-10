#ifndef LOADERSCENE_H
#define LOADERSCENE_H
#include "Scene.h"
#include "DataHandler.h"

class LoaderScene : public Scene
{
private:

	Texture* mContinueLabel;

	int mAlpha;
	bool mReverseAlpha;

	const unsigned int* mNumberofAssets;
	const unsigned int* mAssetsLoadedCount;

public:

	LoaderScene();
	~LoaderScene();

	void updateInterface();
	void renderInterface();

	void updateInput();
	void update();
	void render();

};

#endif