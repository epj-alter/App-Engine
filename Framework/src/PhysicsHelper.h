#ifndef PHYSICSHELPER_H
#define PHYSICSHELPER_H
#include "CircleCollider.h"

namespace Engine
{

	inline bool pointInPolygon(Vector2* verts, int vert_count, const Vector2& point)
	{
		bool return_value = false;

		for (int i = 0, j = vert_count - 1; i < vert_count; j = i++)
		{
			if ((verts[i].y >= point.y) != (verts[j].y >= point.y))
			{
				Vector2 vec1 = (verts[i] - verts[j]).Normalized();
				Vector2 projection = verts[j] + vec1 * dot(point - verts[j], vec1);

				if (projection.x > point.x)
				{
					return_value = !return_value;
				}
			}
		}

		return return_value;
	}

	inline float pointLineDistance(const Vector2& line_start, const Vector2& line_end, const Vector2& point)
	{
		Vector2 slope = line_end - line_start;

		float param = clamp(dot(point - line_start, slope) / slope.MagnitudeSqr(), 0.0f, 1.0f);

		Vector2 nearest_point = line_start + slope * param;

		return (point - nearest_point).Magnitude();
	}

	inline bool circle_circle_Collision(CircleCollider* c1, CircleCollider* c2)
	{
		return (c1->getCenter() - c2->getCenter()).Magnitude() < (c1->getRadius() + c2->getRadius());
	}

	inline bool box_circle_collision(BoxCollider* box, CircleCollider* circle)
	{
		Vector2 quad[4];
		quad[0] = box->getVertexPosition(0);
		quad[1] = box->getVertexPosition(1);
		quad[2] = box->getVertexPosition(2);
		quad[3] = box->getVertexPosition(3);

		float radius = circle->getRadius();
		Vector2 circle_position = circle->getCenter();

		for (int i = 0; i < 4; i++)
		{
			if ((quad[i] - circle_position).Magnitude() < radius)
			{
				return true;
			}
		}

		if (pointLineDistance(box->getVertexPosition(0), box->getVertexPosition(1), circle_position) < radius ||
			pointLineDistance(box->getVertexPosition(0), box->getVertexPosition(2), circle_position) < radius ||
			pointLineDistance(box->getVertexPosition(2), box->getVertexPosition(3), circle_position) < radius ||
			pointLineDistance(box->getVertexPosition(3), box->getVertexPosition(1), circle_position) < radius)
		{
			return true;
		}

		if (pointInPolygon(quad, 4, circle_position))
		{
			return true;
		}

		return false;
	}

	inline bool box_box_collision(BoxCollider* b1, BoxCollider* b2)
	{
		Vector2 projection_axis[4];

		projection_axis[0] = (b1->getVertexPosition(0) - b1->getVertexPosition(1)).Normalized();
		projection_axis[1] = (b1->getVertexPosition(0) - b1->getVertexPosition(2)).Normalized();
		projection_axis[2] = (b2->getVertexPosition(0) - b2->getVertexPosition(1)).Normalized();
		projection_axis[3] = (b2->getVertexPosition(0) - b2->getVertexPosition(2)).Normalized();

		float b1_min = 0.0f, b1_max = 0.0f;
		float b2_min = 0.0f, b2_max = 0.0f;
		float projection_1 = 0.0f, projection_2 = 0.0f;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				projection_1 = dot(b1->getVertexPosition(j), projection_axis[i]);
				projection_2 = dot(b2->getVertexPosition(j), projection_axis[i]);

				if (j == 0)
				{
					b1_min = b1_max = projection_1;
					b2_min = b2_max = projection_2;
				}
				else
				{
					if (projection_1 < b1_min)
						b1_min = projection_1;

					if (projection_1 > b1_max)
						b1_max = projection_1;

					if (projection_2 < b2_min)
						b2_min = projection_2;

					if (projection_2 > b2_max)
						b2_max = projection_2;
				}
			}

			float half_distance1 = (b1_max - b1_min) * 0.5f;
			float mid_point1 = b1_min + half_distance1;

			float half_distance2 = (b2_max - b2_min) * 0.5f;
			float mid_point2 = b2_min + half_distance2;

			if (abs(mid_point1 - mid_point2) > (half_distance1 + half_distance2))
			{
				return false;
			}
		}

		return true;
	}

	inline bool collider_collider_Check(Collider* c1, Collider* c2)
	{
		if (c1->getType() == Collider::ColliderType::Circle && c2->getType() == Collider::ColliderType::Circle)
			return circle_circle_Collision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
		else if (c1->getType() == Collider::ColliderType::Box && c2->getType() == Collider::ColliderType::Circle)
			return box_circle_collision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
		else if (c1->getType() == Collider::ColliderType::Circle && c2->getType() == Collider::ColliderType::Box)
			return box_circle_collision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
		else if (c1->getType() == Collider::ColliderType::Box && c2->getType() == Collider::ColliderType::Box)
			return box_box_collision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
		else
			return false;
	}
}

#endif