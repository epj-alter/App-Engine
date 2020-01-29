#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "PhysicsHandler.h"

namespace Engine
{
	class PhysicsHandler;

	class GameObject : public GameEntity
	{
	protected:

		unsigned long mId;

		std::vector<Collider*> mColliders;

		Collider* mBroadPhaseCollider;

		virtual bool ignoreCollisions();
		void addCollider(Collider* collider, Vector2 local_pos = VECT2_ZERO);

	public:

		GameObject();
		virtual ~GameObject();

		const unsigned long getId() const;
		bool checkCollision(GameObject* other);
		virtual void hit(GameObject* other);

		virtual void render();
	};
}
#endif