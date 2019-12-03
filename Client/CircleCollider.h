#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H
#include "BoxCollider.h"

namespace Engine
{
	class CircleCollider : public Collider
	{
	private:

		float mRadius;

	public:

		CircleCollider(float radius, bool broad_face = false);
		~CircleCollider();

		/* Accessors */
		float getRadius() const;
		Vector2 getFurthestPoint() const override;

	};
}

#endif