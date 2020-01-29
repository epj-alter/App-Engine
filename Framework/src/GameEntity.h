#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include "Shapes.h"

namespace Engine
{

	class GameEntity
	{
	public:
		/* Enums */
		enum class SPACE { own, general };

	protected:
		/* Core Variables*/
		float mRotation;
		Vector2 mCenterPos;
		Vector2 mScale;

		bool mActive;
		GameEntity* mParent;

	public:
		/* Constructor / Destructor */
		GameEntity(Vector2 position = VECT2_ZERO);
		virtual ~GameEntity();

		/* Accessors */
		GameEntity* getParent() const;
		Vector2 getCenter(SPACE space = SPACE::general) const;
		Vector2 getScale(SPACE space = SPACE::general) const;
		float getRotation(SPACE space = SPACE::general) const;
		bool getActive(SPACE space = SPACE::general) const;

		/* Modifiers */
		void setParent(GameEntity* parent);
		void setCenterPos(Vector2 position);
		void setScale(Vector2 scale);
		void setRotation(float rotation);
		void setActive(bool active);
		void rotate(float amount);

		virtual void translate(Vector2 vec, SPACE space = SPACE::own);

		/* Core Functions */
		virtual void update();
		virtual void render();
	};
}
#endif