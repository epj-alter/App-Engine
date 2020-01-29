#ifndef TIMER_H
#define TIMER_H
#include "BezierPath.h"

namespace Engine
{
	class Timer
	{
	private:
		/* Instance Variables */
		static Timer* sInstance;

		/* Core Variables */
		unsigned int mStartTicks;
		unsigned int mElapsedTicks;
		float mDeltaTime;
		float mTimeScale;

		/* Constructor / Destructor */
		Timer();
		~Timer();

	public:

		/* Accessors */
		float getTimeScale();
		float getDeltaTime();

		/* Modifiers */
		void setTimeScale(float t);

		/* Static Functions*/
		static Timer* instance();
		static void release();

		/* Core Functions */
		void restart();
		void update();
	};
}

#endif