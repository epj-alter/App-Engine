#include "GameObject.h"

namespace Engine
{
	bool GameObject::ignoreCollisions()
	{
		return false;
	}

	void GameObject::addCollider(Collider* collider, Vector2 local_pos)
	{
		collider->setParent(this);
		collider->setCenterPos(local_pos);
		mColliders.push_back(collider);

		if (mColliders.size() > 1 || mColliders[0]->getType() != Collider::ColliderType::Circle)
		{
			float furthestDist = mColliders[0]->getFurthestPoint().Magnitude();
			float dist = 0.0f;
			for (int i = 0; i < mColliders.size(); i++)
			{
				dist = mColliders[i]->getFurthestPoint().Magnitude();
				if (dist > furthestDist)
				{
					furthestDist = dist;
				}
			}

			delete mBroadPhaseCollider;
			mBroadPhaseCollider = new CircleCollider(furthestDist *0.5f, true);
			mBroadPhaseCollider->setParent(this);
			mBroadPhaseCollider->setCenterPos(VECT2_ZERO);
		}
	}

	GameObject::GameObject()
	{
		mBroadPhaseCollider = nullptr;
		mId = 0;
	}

	GameObject::~GameObject()
	{
		for (auto& colliders : mColliders)
		{
			delete colliders;
			colliders = nullptr;
		}
		mColliders.clear();

		if (mBroadPhaseCollider)
		{
			delete mBroadPhaseCollider;
			mBroadPhaseCollider = nullptr;
		}

		if (mId != 0)
		{
			PhysicsHandler::instance()->unregisterObject(mId);
		}
	}

	const unsigned long GameObject::getId() const
	{
		return mId;
	}

	bool GameObject::checkCollision(GameObject* other)
	{
		if (ignoreCollisions() || other->ignoreCollisions())
			return false;

		bool narrow_phase_check = false;
		if (mBroadPhaseCollider && other->mBroadPhaseCollider)
		{
			narrow_phase_check = collider_collider_Check(mBroadPhaseCollider, other->mBroadPhaseCollider);
		}
		else
		{
			narrow_phase_check = true;
		}

		if (narrow_phase_check)
		{
			for (const auto& collider : mColliders)
			{
				for (const auto& other_collider : other->mColliders)
				{
					if (collider_collider_Check(collider, other_collider))
					{
						return true;
					}
				}
			}

			/*for (int i = 0; i < mColliders.size(); i++)
			{
				for (int j = 0; j < other->mColliders.size(); j++)
				{
					if (collider_collider_Check(mColliders[i], other->mColliders[j]))
					{
						return true;
					}
				}
			}*/
		}

		return false;
	}

	void GameObject::hit(GameObject* other)
	{

	}

	void GameObject::render()
	{
		for (const auto& colliders : mColliders)
		{
			colliders->render();
		}

		if (mBroadPhaseCollider)
		{
			mBroadPhaseCollider->render();
		}
	}
}
