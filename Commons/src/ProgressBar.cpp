#include "ProgressBar.h"

namespace GUI
{
	GUI::ProgressBar::ProgressBar(GameEntity* parent, int x, int y, int width, int height, const float& current_value, const float& max_value, bool show_percentage)
		: Container(parent, x, y, width, height), mCurrentValue(current_value), mMaxValue(max_value)
	{
		mFillColor = mStyle->color("disabled");
		mLineColor = mStyle->color("neutral");
		mTextColor = mStyle->color("light");

		mShowPercentage = false;

		mInnerBar = new Container(nullptr, x, y, width, height);
		mInnerBar->colors(mStyle->color("success"), mStyle->color("neutral"));

		mRenderedText = nullptr;

		if (mCurrentValue < 0.f)
		{
			mPercentage = (mCurrentValue * mMinPercentage) / mMaxValue;
			mCurrentWidth = round(mWidth * (mPercentage / 100.f));
			mInnerBar->setBounds(round(mLeft + mCurrentWidth * 0.5f), mCenterPos.y, mCurrentWidth, mHeight);
		}
		else
		{
			mPercentage = (mCurrentValue * mMaxPercentage) / mMaxValue;
			mCurrentWidth = round(mWidth * (mPercentage / 100.f));
			mInnerBar->setBounds(round(mLeft + mCurrentWidth * 0.5f), mCenterPos.y, mCurrentWidth, mHeight);
		}

		if (!show_percentage)
		{
			mText = std::to_string(static_cast<int>(round(mCurrentValue))) + "/" + std::to_string(static_cast<int>(round(mMaxValue)));

			mRenderedText = new Texture(mText, mStyle->font("default"), mStyle->size(), mTextColor);
			mRenderedText->setParent(this);
			mRenderedText->setCenterPos(VECT2_ZERO);

			mShowPercentage = false;
		}
		else
		{
			mText = fto_string(mPercentage, 1) + "/" + fto_string(mMaxPercentage, 1) + "%";

			mRenderedText = new Texture(mText, mStyle->font("default"), mStyle->size(), mTextColor);
			mRenderedText->setParent(this);
			mRenderedText->setCenterPos(VECT2_ZERO);

			mShowPercentage = true;
		}
	}

	GUI::ProgressBar::~ProgressBar()
	{
		delete mRenderedText;
		mRenderedText = nullptr;

		delete mInnerBar;
		mInnerBar = nullptr;
	}

	void GUI::ProgressBar::update()
	{
		mPercentage = (mCurrentValue * mMaxPercentage) / mMaxValue;

		if (mPercentage > mMaxPercentage)
			mPercentage = mMaxPercentage;
		else if (mPercentage < mMinPercentage)
			mPercentage = mMinPercentage;

		mCurrentWidth = round(mWidth * (mPercentage * 0.01f));

		/*if (mCurrentWidth > mWidth)
			mCurrentWidth = mWidth;
		else if (mCurrentWidth < 0)
			mCurrentWidth = 0;*/

		mInnerBar->setBounds(round(mLeft + mCurrentWidth * 0.5f), mCenterPos.y, mCurrentWidth, mHeight);

		if (mRenderedText != nullptr)
		{
			if (mShowPercentage)
				mText = fto_string(mPercentage, 1) + "/" + fto_string(mMaxPercentage, 1) + "%";
			else
			{
				if (mCurrentValue >= mMaxValue)
					mText = std::to_string(static_cast<int>(round(mMaxValue))) + "/" + std::to_string(static_cast<int>(round(mMaxValue)));
				else if(mCurrentValue < mMinValue)
					mText = std::to_string(static_cast<int>(round(mMinValue))) + "/" + std::to_string(static_cast<int>(round(mMaxValue)));
				else
					mText = std::to_string(static_cast<int>(round(mCurrentValue))) + "/" + std::to_string(static_cast<int>(round(mMaxValue)));
			}

			mRenderedText->setText(mText, mStyle->font("default"), mStyle->size(), mTextColor);
		}
	}

	void GUI::ProgressBar::render()
	{
		mShape.x = mLeft; //- mGraphics->getCamera().x);
		mShape.y = mTop; //- mGraphics->getCamera().y);
		mShape.w = mWidth;
		mShape.h = mHeight;

		Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);

		if(mCurrentWidth != 0)
			mInnerBar->render();

		if(mRenderedText != nullptr)
			mRenderedText->render();
	}

}