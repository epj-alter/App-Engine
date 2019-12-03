#ifndef COLLIDER_H
#define COLLIDER_H
#include "AnimatedTexture.h"

namespace Engine
{
	typedef std::map<std::string, AnimatedTexture*> AnimatedTextureMap;

	class Collider : public GameEntity
	{
	public:

		enum class ColliderType
		{
			Box,
			Circle
		};

	protected:

		ColliderType mType;

		static const bool DEBUG_COLLIDERS = true;
		Texture* mDebugTexture;

		/* Debug Functions */
		void setDebugTexture(Texture* texture);

	public:

		/* Constructor / Destructor*/
		Collider(ColliderType type);
		virtual ~Collider();

		/* Accessors */
		virtual Vector2 getFurthestPoint() const = 0;
		ColliderType getType() const;

		/* CORE Functions */
		virtual void render();
	};
}

#endif