#include "stdafx.h"
#include "CircleCollider.h"

namespace Engine
{
	CircleCollider::CircleCollider(float radius, bool broad_face)
		:Collider(ColliderType::Circle)
	{
		mRadius = radius;

		if (DEBUG_COLLIDERS)
		{
			if (broad_face)
				setDebugTexture(new Texture("broadface_collider.png"));
			else
				setDebugTexture(new Texture("circle_collider.png"));

			mDebugTexture->setScale(VECT2_ONE * (radius * 2 / 100.f));
		}

	}

	CircleCollider::~CircleCollider()
	{
	}

	float CircleCollider::getRadius() const
	{
		return mRadius;
	}

	Vector2 CircleCollider::getFurthestPoint() const
	{
		return VECT2_RIGHT * (mRadius + this->getCenter(GameEntity::SPACE::own).Magnitude());
	}
}
