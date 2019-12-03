#include "stdafx.h"
#include "AnimatedTexture.h"

namespace Engine
{
	void AnimatedTexture::runAnimation()
	{
		this->mAnimationTimer += this->mTimer->getDeltaTime();

		if (this->mAnimationTimer >= this->mAnimationSpeed)
		{
			if (this->mWrapMode == loop)
			{
				this->mAnimationTimer -= this->mAnimationSpeed;
			}
			else
			{
				this->mAnimationTimer = this->mAnimationSpeed - this->mTimerPerFrame;
				this->mAnimationIsDone = true;
			}
		}
		if (this->mAnimationDirection == horizontal)
		{
			this->mClippedRect.x = this->mStartX + static_cast<int>(this->mAnimationTimer / this->mTimerPerFrame) * this->mWidth;
		}
		else
		{
			this->mClippedRect.y = this->mStartY + static_cast<int>(this->mAnimationTimer / this->mTimerPerFrame) * this->mHeight;
		}
	}

	/* Constructor / Destructor */
	AnimatedTexture::AnimatedTexture(std::string file_name, int x, int y, int w, int h, int frame_count, float animation_speed, ANIM_DIR animation_direction)
		: Texture(file_name, x, y, w, h)
	{
		this->mTimer = Timer::instance();

		this->mStartX = x;
		this->mStartY = y;

		this->mFrameCount = frame_count;
		this->mAnimationSpeed = animation_speed;
		this->mTimerPerFrame = this->mAnimationSpeed / this->mFrameCount;
		this->mAnimationTimer = 0.0f;

		this->mAnimationDirection = animation_direction;

		this->mAnimationIsDone = false;
		this->mWrapMode = loop;
	}

	AnimatedTexture::~AnimatedTexture()
	{
		this->mTimer = nullptr;
	}

	bool AnimatedTexture::isAnimating()
	{
		return (!this->mAnimationIsDone);
	}

	/* Functions */
	void AnimatedTexture::wrapMode(WRAP_MODE mode)
	{
		this->mWrapMode = mode;
	}

	void AnimatedTexture::resetAnimation()
	{
		this->mAnimationTimer = 0.0f;
		this->mAnimationIsDone = false;
	}

	/* Core Functions */
	void AnimatedTexture::update()
	{
		if (!this->mAnimationIsDone)
		{
			this->runAnimation();
		}
	}
}