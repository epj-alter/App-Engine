#ifndef SLIDER_H
#define SLIDER_H

#include "ProgressBar.h"

namespace GUI
{
	class Slider : public Container
	{
	private:

		Container* mInnerBar;

		const int mMinValue = 0;

		int mCurrentWidth;

		int & mCurrentValue;
		const int & mMaxValue;

		float mPercentage;
		bool mSelected;

	public:
		Slider(GameEntity* parent, int x, int y, int width, int height, int& current_value, const int& max_value);
		~Slider();

		void update();
		void render();
	};
}
#endif // !SLIDER_H