
#include "PhysicsHandler.h"

namespace Engine
{
	PhysicsHandler* PhysicsHandler::sInstance = nullptr;

	PhysicsHandler::PhysicsHandler()
	{
		mLastId = 0;

		for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS); i++)
		{
			mLayerMasks[i] = std::bitset<static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS)>(static_cast<unsigned int>(CollisionFlags::None));
		}

	}

	PhysicsHandler::~PhysicsHandler()
	{
		for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS); i++)
		{
			mCollisionLayers[i].clear();
		}
	}

	PhysicsHandler* PhysicsHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new PhysicsHandler();

		return sInstance;
	}

	void PhysicsHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	void PhysicsHandler::setLayerCollisionMask(CollisionLayers layer, CollisionFlags flag)
	{
		mLayerMasks[static_cast<unsigned int>(layer)] =
			std::bitset<static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS)>(static_cast<unsigned int>(flag));
	}

	unsigned long PhysicsHandler::registerObject(GameObject* entity, CollisionLayers layer)
	{
		mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);

		mLastId++;

		return mLastId;
	}

	void PhysicsHandler::unregisterObject(unsigned long id)
	{
		bool found = false;

		for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS) && !found; i++)
		{
			for (int j = 0; j < mCollisionLayers[i].size() && !found; j++)
			{
				if (mCollisionLayers[i][j]->getId() == id)
				{
					mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
					found = true;
				}
			}
		}
	}

	void PhysicsHandler::update()
	{
		for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS); i++)
		{
			for (unsigned int j = 0; j < static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS); j++)
			{
				if (mLayerMasks[i].test(j) && i <= j)
				{
					for (unsigned int k = 0; k < mCollisionLayers[i].size(); k++)
					{
						for (unsigned int l = 0; l < mCollisionLayers[j].size(); l++)
						{
							if (mCollisionLayers[i][k]->checkCollision(mCollisionLayers[j][l]))
							{
								mCollisionLayers[i][k]->hit(mCollisionLayers[j][l]);
								mCollisionLayers[j][l]->hit(mCollisionLayers[i][k]);
							}
						}
					}
				}
			}
		}
	}
}
