#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "Collider.h"

class Collider;

namespace Engine
{

	class BoxCollider : public Collider
	{
	private:

		static const int MAX_VERTS = 4;

		GameEntity* mVerts[MAX_VERTS];

		void addVert(int index, Vector2 pos);

	public:

		BoxCollider(Vector2 size);
		~BoxCollider();

		/* Accessors */
		Vector2 getFurthestPoint() const override;
		Vector2 getVertexPosition(int index) const;
	};
}

#endif