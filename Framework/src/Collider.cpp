#include "Collider.h"

namespace Engine
{
	/* Debug Functions */
	void Collider::setDebugTexture(Texture* texture)
	{
		delete mDebugTexture;
		mDebugTexture = texture;
		mDebugTexture->setParent(this);
	}

	/* Constructor / Destructor*/
	Collider::Collider(ColliderType type)
		: mType(type)
	{
		mDebugTexture = nullptr;
	}

	Collider::~Collider()
	{
		if (mDebugTexture != nullptr)
		{
			delete mDebugTexture;
			mDebugTexture = nullptr;
		}
	}

	Collider::ColliderType Collider::getType() const
	{
		return mType;
	}

	/* CORE Functions */
	void Collider::render()
	{
		if (DEBUG_COLLIDERS)
		{
			mDebugTexture->render();
		}
	}
}
