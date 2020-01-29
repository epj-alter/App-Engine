#include "BoxCollider.h"

namespace Engine
{
	void BoxCollider::addVert(int index, Vector2 pos)
	{
		mVerts[index] = new GameEntity(pos);
		mVerts[index]->setParent(this);
	}

	BoxCollider::BoxCollider(Vector2 size)
		: Collider(ColliderType::Box)
	{
		addVert(0, Vector2(size.x, size.y));
		addVert(1, Vector2(size.x, size.y));
		addVert(2, Vector2(size.x, size.y));
		addVert(3, Vector2(size.x, size.y));

		if (DEBUG_COLLIDERS)
		{
			setDebugTexture(new Texture("box_collider.png"));
			mDebugTexture->setScale(size / 100.f);
		}
	}

	BoxCollider::~BoxCollider()
	{
		for (auto& verts : mVerts)
		{
			delete verts;
			verts = nullptr;
		}
	}

	Vector2 BoxCollider::getFurthestPoint() const
	{
		Vector2 local_pos = this->getCenter(GameEntity::SPACE::own);

		int furthest_index = 0;
		float distance = (local_pos + mVerts[0]->getCenter(GameEntity::SPACE::own)).MagnitudeSqr();
		float otherDist = 0.0f;

		for (size_t i = 1; i < MAX_VERTS; i++)
		{
			otherDist = (local_pos + mVerts[i]->getCenter(GameEntity::SPACE::own)).MagnitudeSqr();
			if (otherDist > distance)
			{
				furthest_index = i;
				distance = otherDist;
			}
		}

		return local_pos + mVerts[furthest_index]->getCenter(GameEntity::SPACE::own);
	}
	Vector2 BoxCollider::getVertexPosition(int index) const
	{
		return mVerts[index]->getCenter();
	}
}
