#ifndef MATHHELPER_H
#define MATHHELPER_H

namespace Engine
{
	struct Vector2
	{
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f)
			: x(_x), y(_y) {}

		float MagnitudeSqr()
		{
			return x * x + y * y;
		}

		float Magnitude()
		{
			return static_cast<float>(sqrt(x * x + y * y));
		}

		Vector2 Normalized()
		{
			float mag = Magnitude();

			return Vector2(x / mag, y / mag);
		}

		Vector2& operator +=(const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Vector2& operator -=(const Vector2& lhs)
		{
			x -= lhs.x;
			y -= lhs.y;

			return *this;
		}

		Vector2 operator -() const
		{
			return Vector2(-x, -y);
		}
	};

	inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline Vector2 operator *(const Vector2& lhs, const float& rhs)
	{
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}
	inline Vector2 operator *(const float& lhs, const Vector2& rhs)
	{
		return Vector2(lhs * rhs.x, lhs * rhs.y);
	}
	inline Vector2 operator /(const Vector2& lhs, const float& rhs)
	{
		return Vector2(lhs.x / rhs, lhs.y / rhs);
	}
	inline Vector2 operator /(const float& lhs, const Vector2& rhs)
	{
		return Vector2(lhs / rhs.x, lhs / rhs.y);
	}

	inline Vector2 RotateVector(const Vector2& vector, float angle)
	{
		float radAngle = static_cast<float>(angle * DEG_TO_RAD);

		return Vector2
		(
			static_cast<float>(vector.x * cos(radAngle) - vector.y * sin(radAngle)),
			static_cast<float>(vector.x * sin(radAngle) + vector.y * cos(radAngle))
		);
	}

	inline float dot(const Vector2& vec1, const Vector2& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	inline float clamp(const float& value, const float& min, const float& max)
	{
		if (value > max)
		{
			return max;
		}
		if (value < min)
		{
			return min;
		}

		return value;
	}

	//linear interpolation
	inline Vector2 lerp(const Vector2& start, const Vector2& end, float time)
	{
		if (time <= 0.0f)
			return start;

		if (time >= 1.0f)
			return end;

		Vector2 direction = (end - start).Normalized();
		float mag = (end - start).Magnitude();

		return start + direction * mag * time;
	}

	const Vector2 VECT2_ZERO = { 0.0f, 0.0f };
	const Vector2 VECT2_ONE = { 1.0f, 1.0f };
	const Vector2 VECT2_UP = { 0.0f, 1.0f };
	const Vector2 VECT2_RIGHT = { 1.0f, 0.0f };

	struct BezierCurve
	{
		Vector2 p0, p1, p2, p3;

		Vector2 calculateCurvePoint(float t)
		{
			float tt = t * t;
			float ttt = tt * t;
			float u = 1.0f - t;
			float uu = u * u;
			float uuu = uu * u;

			Vector2 point = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);

			point.x = round(point.x);
			point.y = round(point.y);

			return point;
		}
	};

	struct gfxSettings
	{
		const char* title = "default";
		int x_pos, y_pos;
		int width, height;
		int display_mode;
		bool Vsync;
		int filter;

		gfxSettings(int _w_pos, int _width, int _height, int _mode, bool _Vsync, int _filter)
			: width(_width), height(_height), display_mode(_mode), Vsync(_Vsync), filter(_filter)
		{
			switch (_w_pos)
			{
			case 0:
				x_pos = 5;
				y_pos = 5;
				break;

			case 1:
				x_pos = SDL_WINDOWPOS_CENTERED;
				y_pos = SDL_WINDOWPOS_CENTERED;
				break;

			default:
				x_pos = SDL_WINDOWPOS_UNDEFINED;
				y_pos = SDL_WINDOWPOS_UNDEFINED;
				break;
			}
		}
	};

	template <typename T>
	std::string fto_string(const T a_value, const int precision)
	{
		std::ostringstream out;
		out.precision(precision);
		out << std::fixed << a_value;
		return out.str();
	}
}

#endif