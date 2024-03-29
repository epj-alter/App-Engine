#include "Slider.h"

namespace GUI
{

	GUI::Slider::Slider(GameEntity* parent, int x, int y, int width, int height, int& current_value, const int& max_value)
		: Container(parent, x, y, width, height), mCurrentValue(current_value), mMaxValue(max_value)
	{
		mPercentage = 0.f;

		mFillColor = mStyle->color("disabled");
		mLineColor = mStyle->color("neutral");
	
		mInnerBar = new Container(nullptr, x, y, width, height);
		mInnerBar->colors(mStyle->color("success"), mStyle->color("neutral"));
	
		mCurrentWidth = mWidth;
		mSelected = false;

		if (mCurrentValue < 0.f)
		{
			mPercentage = (mCurrentValue * 0.f) / mMaxValue;
			mCurrentWidth = round(mWidth * (mPercentage / 100.f));
			mInnerBar->setBounds(round(mLeft + mCurrentWidth * 0.5f), mCenterPos.y, mCurrentWidth, mHeight);
		}
		else
		{
			mPercentage = (mCurrentValue * 100.f / mMaxValue);
			mCurrentWidth = round(mWidth * (mPercentage / 100.f));
			mInnerBar->setBounds(round(mLeft + mCurrentWidth * 0.5f), mCenterPos.y, mCurrentWidth, mHeight);
		}
	}
	
	GUI::Slider::~Slider()
	{
		delete mInnerBar;
		mInnerBar = nullptr;
	}
	
	void GUI::Slider::update()
	{
		if (!mSelected)
		{
			if (getBounds().contains(mInput->getMousePosition()) && mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left))
				mSelected = true;
		}
		else
		{
			if (mInput->mouseButtonReleased(InputHandler::MOUSE_BUTTONS::left))
				mSelected = false;
	
			mPercentage = (mInput->getMousePosition().x - mLeft) / mWidth * 100.f;
	
			if (mPercentage > 100.f)
				mPercentage = 100.f;
			else if (mPercentage < 0.f)
				mPercentage = 0.f;
	
			mCurrentValue = round(mPercentage * mMaxValue * 0.01f);
	
			mCurrentWidth = round(mWidth * (mPercentage * 0.01f));
			mInnerBar->setBounds(round(mLeft + mCurrentWidth * 0.5f), mCenterPos.y, mCurrentWidth, mHeight);
		}
	}
	
	void GUI::Slider::render()
	{
		mShape.x = mLeft; //- mGraphics->getCamera().x);
		mShape.y = mTop; //- mGraphics->getCamera().y);
		mShape.w = mWidth;
		mShape.h = mHeight;
	
		Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);
	
		if(mCurrentWidth != 0)
			mInnerBar->render();
	}
}