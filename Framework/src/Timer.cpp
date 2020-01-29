#include "Timer.h"

namespace Engine
{
	Timer* Timer::sInstance = nullptr;

	/* Constructor / Destructor */
	Timer::Timer()
	{
		this->mDeltaTime = NULL;
		this->mStartTicks = NULL;
		this->mElapsedTicks = NULL;

		this->restart();
		this->mTimeScale = 1.0f;
	}

	Timer::~Timer()
	{
	}


	/* Accessors */
	float Timer::getTimeScale()
	{
		return this->mTimeScale;
	}

	float Timer::getDeltaTime()
	{
		return this->mDeltaTime;
	}

	/* Modifiers */
	void Timer::setTimeScale(float t)
	{
		this->mTimeScale = t;
	}

	/* Static Functions*/
	Timer* Timer::instance()
	{
		if (sInstance == nullptr)
			sInstance = new Timer();

		return sInstance;
	}

	void Timer::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	/* Core Functions */
	void Timer::restart()
	{
		this->mStartTicks = SDL_GetTicks();
		this->mElapsedTicks = 0;
		this->mDeltaTime = 0.0f;
	}

	void Timer::update()
	{
		this->mElapsedTicks = SDL_GetTicks() - this->mStartTicks;
		this->mDeltaTime = mElapsedTicks * 0.001f;
	}
}