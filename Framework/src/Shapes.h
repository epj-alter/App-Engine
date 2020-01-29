#ifndef SHAPES_H
#define SHAPES_H
#include "AudioHandler.h"

namespace Engine
{
	typedef struct intRect
	{
		int& left;
		int& top;
		int& width;
		int& height;

		intRect(int& _left, int& _top, int& _width, int& _height)
			: left(_left), top(_top), width(_width), height(_height) {}

		bool contains(const Vector2& point) const
		{
			if (point.x > left && point.x < (left + width) && point.y > top && point.y < top + height)
				return true;

			return false;
		}
	} intRect;
}

#endif // ! SHAPES_H