#include "stdafx.h"
#include "GameEntity.h"

namespace Engine
{
	/* Constructor / Destructor */
	GameEntity::GameEntity(Vector2 position)
	{
		mCenterPos.x = position.x;
		mCenterPos.y = position.y;

		mRotation = NULL;
		mActive = true;

		mParent = nullptr;

		mScale = VECT2_ONE;
	}

	GameEntity::~GameEntity()
	{
		mParent = nullptr;
	}

	/* Accessors */
	GameEntity* GameEntity::getParent() const
	{
		return mParent;
	}

	Vector2 GameEntity::getCenter(SPACE space) const
	{
		if (space ==  own || mParent == nullptr)
			return mCenterPos;

		GameEntity* parent = mParent;
		Vector2 final_pos = mCenterPos;
		Vector2 parent_scale = VECT2_ZERO;

		do
		{
			parent_scale = mParent->getScale(own);
			final_pos = RotateVector(Vector2(final_pos.x * parent_scale.x, final_pos.y * parent_scale.y), parent->getRotation(own));
			final_pos += parent->getCenter(own);

			parent = parent->getParent();

		} while (parent != nullptr);

		return final_pos;
	}

	Vector2 GameEntity::getScale(SPACE space) const
	{
		if (space == own || mParent == nullptr)
			return mScale;

		Vector2 scale = mParent->getScale(general);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return mScale;
	}

	float GameEntity::getRotation(SPACE space) const
	{
		if (space == own || mParent == nullptr)
			return mRotation;

		return mParent->getRotation(general) + mRotation;
	}

	bool GameEntity::getActive(SPACE space) const
	{
		return this->mActive;
	}

	/* Modifiers */
	void GameEntity::setParent(GameEntity* parent)
	{
		if (parent == nullptr)
		{
			this->mCenterPos = this->getCenter(general);
			this->mRotation = this->getRotation(general);
			this->mScale = this->getScale(general);
		}
		else
		{
			if (mParent != nullptr)
				setParent(nullptr);

			Vector2 parent_scale = parent->getScale(general);

			mCenterPos = RotateVector(getCenter(general) - parent->getCenter(general), -parent->getRotation(general));
			mCenterPos.x /= parent_scale.x;
			mCenterPos.y /= parent_scale.y;

			mRotation -= parent->getRotation(general);
			mScale = Vector2(mScale.x / parent_scale.x, mScale.y / parent_scale.y);

		}

		this->mParent = parent;
	}

	void GameEntity::setCenterPos(Vector2 position)
	{
		mCenterPos = position;
	}

	void GameEntity::setScale(Vector2 scale)
	{
		mScale = scale;
	}

	void GameEntity::setRotation(float rotation)
	{
		mRotation = rotation;

		if (mRotation > 360.f)
		{
			int mul = mRotation / 360;
			mRotation -= 360.f * mul;
		}

		else if (mRotation < 0.0f)
		{
			int mul = (mRotation / 360) - 1;
			mRotation -= 360.f * mul;
		}
	}

	void GameEntity::setActive(bool active)
	{
		mActive = active;
	}

	void GameEntity::rotate(float amount)
	{
		setRotation(mRotation + amount);
	}

	void GameEntity::translate(Vector2 vec, SPACE space)
	{
		if (space == general)
		{
			mCenterPos += vec;
		}
		else
		{
			mCenterPos += RotateVector(vec, getRotation());
		}

		// for future player class
		//Graphics::Instance()->setCamera(mPosition.x, mPosition.y);
	}

	/* Core Functions */
	void GameEntity::update()
	{
	}

	void GameEntity::render()
	{
	}
}