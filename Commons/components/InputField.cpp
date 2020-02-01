#include "InputField.h"

namespace GUI
{
	InputField::InputField(GameEntity* parent, int x, int y, int width, int height, bool opaque)
		: Container(parent, x, y, width, height)
	{
		if (opaque)
		{
			mFillColor = mStyle->color("reduced");
			mLineColor = mStyle->color("neutral");
			mTextColor = mStyle->color("light");

			mInactiveColor = mStyle->color("neutral");
		}
		else
		{
			mTextColor = mStyle->color("contrast");
			mInactiveColor = mStyle->color("neutral");
		}

		mActiveColor = mStyle->color("interactive");

		mRenderedText = nullptr;
		mFocus = false;
	}

	InputField::~InputField()
	{
		delete mRenderedText;
		mRenderedText = nullptr;

		SDL_StopTextInput();
	}

	bool InputField::hasFocus() const
	{
		return mFocus;
	}

	std::string InputField::getText() const
	{
		return mText;
	}

	void InputField::addText()
	{
		if (mRenderedText == nullptr)
		{

			if (mText.size() < 20)
			{
				mText += mInput->getEvent().text.text;
				mRenderedText = new Texture(mText, mStyle->font("default"), mStyle->size(), mTextColor); 
				mRenderedText->setParent(this);
				mRenderedText->setCenterPos(Vector2(0.05f, 0.10f));
			}
		}
		else
			if (mText.size() < 20)
			{
				mText += mInput->getEvent().text.text;
				mRenderedText->setText(mText, mStyle->font("default"), mStyle->size(), mTextColor);
			}
	}

	void InputField::removeText()
	{
		if (mText.size() > 0)
		{
			mText = mText.substr(0, mText.length() - 1);
			if (mText.size() == 0)
			{
				delete mRenderedText;
				mRenderedText = nullptr;
			}
			else
				mRenderedText->setText(mText, mStyle->font("default"), mStyle->size(), mTextColor);
		}
	}

	void InputField::pasteText(std::string clipboard_text)
	{
		if (mRenderedText == nullptr)
		{
			if (clipboard_text.size() < 21)
			{
				mText = clipboard_text;
				mRenderedText = new Texture(mText, mStyle->font("default"), mStyle->size(), mTextColor);
				mRenderedText->setParent(this);
				mRenderedText->setCenterPos(Vector2(0.05f, 0.10f));
			}
		}
		else 
		{
			if (clipboard_text.size() < 21)
			{
				mText = clipboard_text;
				mRenderedText->setText(mText, mStyle->font("default"), mStyle->size(), mTextColor);
			}
		}
	}

	void InputField::update()
	{
		if (this->getBounds().contains(mInput->getMousePosition()) && !mFocus && mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left))
		{
			mLineColor = mActiveColor;
			SDL_StartTextInput();
			mFocus = true;
		}
		else if (mFocus && mInput->mouseButtonPressed(InputHandler::MOUSE_BUTTONS::left) && !this->getBounds().contains(mInput->getMousePosition()))
		{
			mLineColor = mInactiveColor;
			SDL_StopTextInput();
			mFocus = false;
		}
	}

	void InputField::render()
	{
		mShape.x = mLeft; //- mGraphics->getCamera().x);
		mShape.y = mTop; //- mGraphics->getCamera().y);
		mShape.w = mWidth;
		mShape.h = mHeight;

		Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);

		if (mText != "")
		{
			mRenderedText->render();
		}
	}
}