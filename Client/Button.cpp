#include "stdafx.h"
#include "Button.h"

namespace Engine
{
	Button::Button(GameEntity* parent, std::string text, int x, int y, int width, int height, bool text_only, bool default_button)
		: Container(parent, x, y, width, height)
	{
		mState = BUTTON_STATE::idle;

		mText = text;
		mLabel = nullptr;
		
		mTextButton = text_only;

		mDisabled = false;
		mSelected = false;

		if (default_button)
		{
			mTextColor = mStyle->color("contrast");
			mIdleColor = mStyle->color("neutral");
			mHoveredColor = mStyle->color("reduced");
			mPressedColor = mStyle->color("neutral");
			mSelectedColor = mStyle->color("success");
		}
		else
		{
			mTextColor = mStyle->color("contrast");
			mIdleColor = mStyle->color("interactive");
			mHoveredColor = mStyle->color("hovered");
			mPressedColor = mStyle->color("pressed");
			mSelectedColor = mStyle->color("success");
		}

		setLabel(mText);
	}

	Button::Button(GameEntity* parent, int x, int y, int width, int height, bool disabled, bool selected)
		: Container(parent, x, y, width, height)
	{
		mState = BUTTON_STATE::idle;

		mLabel = nullptr;

		mTextButton = false;

		mDisabled = disabled;
		mSelected = selected;

		mTextColor = mStyle->color("contrast");
		mIdleColor = { 0, 0, 0, 0 };
		mHoveredColor = mStyle->color("success");
		mPressedColor = mStyle->color("pressed");
		mSelectedColor = mStyle->color("success");
	}

	Button::~Button()
	{
		delete mLabel;
		mLabel = nullptr;
	}

	const std::string Button::getText() const
	{
		return mText;
	}

	const Button::BUTTON_STATE Button::getState()
	{
		if (!mDisabled)
		{
			if (mTextButton)
			{
				if (mBounds.contains(mInput->getMousePosition()) && !mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left))
					mState = BUTTON_STATE::hovered;
				else if (mLabel->getBounds().contains(mInput->getMousePosition()) && mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left))
					mState = BUTTON_STATE::pressed;
				else
					mState = BUTTON_STATE::idle;
			}
			else
			{
				if (mBounds.contains(mInput->getMousePosition()) && !mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left))
					mState = BUTTON_STATE::hovered;
				else if (mBounds.contains(mInput->getMousePosition()) && mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left))
					mState = BUTTON_STATE::pressed;
				else
					mState = BUTTON_STATE::idle;
			}
		}

		return mState;
	}

	bool Button::isDisabled() const
	{
		return mDisabled;
	}

	bool Button::isSelected() const
	{
		return mSelected;
	}

	void Button::setLabel(std::string text, StylesHandler::FONT_MODIFIER size_mod, std::string font_path)
	{
		mText = text;

		if (mLabel == nullptr)
		{
			mLabel = new Texture(mText, mStyle->font(font_path), mStyle->size(size_mod), mTextColor);
			mLabel->setParent(this);
			mLabel->setCenterPos(VECT2_ZERO);
		}
		else
			mLabel->setText(mText, mStyle->font(font_path), mStyle->size(size_mod), mTextColor);
	}

	void Button::setDisable()
	{
		mDisabled = !mDisabled;
	}

	void Button::setSelected(bool select)
	{
		mSelected = select;
	}

	void Button::update()
	{
		if (!mDisabled)
		{
			switch (mState)
			{
			case Engine::Button::BUTTON_STATE::idle:
				if (!mSelected)
					mFillColor = mIdleColor;
				else
					mFillColor = mSelectedColor;
				break;

			case Engine::Button::BUTTON_STATE::hovered:
				mFillColor = mHoveredColor;
				break;

			case Engine::Button::BUTTON_STATE::pressed:
				mFillColor = mPressedColor;
				break;
			}
		}
		else
			mFillColor = mStyle->color("disabled");
	}

	void Button::render()
	{
		if (!mTextButton)
		{
			mShape.x = mLeft; //- mGraphics->getCamera().x);
			mShape.y = mTop; //- mGraphics->getCamera().y);
			mShape.w = mWidth;
			mShape.h = mHeight;

			Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);

			if (mLabel != nullptr)
			{
				mLabel->render();
			}
		}
		else
			mLabel->render();
	}
}