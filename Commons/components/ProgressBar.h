#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "DropDownList.h"

namespace GUI
{
	class ProgressBar : public Container
	{
	private:

		Container* mInnerBar;

		Texture* mRenderedText;
		std::string mText;

		bool mShowPercentage;

		int mCurrentWidth;

		const float mMinValue = 0.f;
		const float & mMaxValue;
		const float & mCurrentValue;

		const float mMinPercentage = 0.f;
		const float mMaxPercentage = 100.f;

		float mPercentage;

		SDL_Color mTextColor;

	public:

		/* Contructor / Destructor */
		ProgressBar(GameEntity* parent,	int x, int y, int width, int height, const float& current_value, const float& max_value, bool show_percentage = false);
		~ProgressBar();

		void update();
		void render();

	};
}
#endif