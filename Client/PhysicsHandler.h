#ifndef PHYSICSHANDLER_H
#define PHYSICSHANDLER_H
#include "ConfirmationBox.h"

namespace Engine
{
	class PhysicsHandler
	{
	public:

		enum class CollisionLayers
		{
			Friendly = 0,
			FriendlyProjectiles,
			Hostile,
			HostileProjectiles,
			//-----------------//
			MAX_COLLISION_LAYERS
		};

		enum class CollisionFlags
		{
			None = 0x00,
			Friendly = 0x01,
			FriendlyProjectiles = 0x02,
			Hostile = 0x04,
			HostileProjectiles = 0x08
		};

	private:

		static PhysicsHandler* sInstance;

		std::vector<GameObject*>
			mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS)];

		std::bitset<static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS)>
			mLayerMasks[static_cast<unsigned int>(CollisionLayers::MAX_COLLISION_LAYERS)];

		unsigned long mLastId;

		PhysicsHandler();
		~PhysicsHandler();

	public:

		static PhysicsHandler* instance();
		static void release();

		void setLayerCollisionMask(CollisionLayers layer, CollisionFlags flag);

		unsigned long registerObject(GameObject* entity, CollisionLayers layer);
		void unregisterObject(unsigned long id);

		void update();
	};

	inline PhysicsHandler::CollisionFlags operator|(PhysicsHandler::CollisionFlags a, PhysicsHandler::CollisionFlags b)
	{
		return static_cast<PhysicsHandler::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
	}
	inline PhysicsHandler::CollisionFlags operator &(PhysicsHandler::CollisionFlags a, PhysicsHandler::CollisionFlags b)
	{
		return static_cast<PhysicsHandler::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
	}
}

#endif