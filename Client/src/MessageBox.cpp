#include "stdafx.h"
#include "MessageBox.h"

namespace Engine
{
	MessageBox* MessageBox::sInstance = nullptr;

	MessageBox::MessageBox()
	{
		mStyle = StylesHandler::instance();

		mMessage = "ERROR 404 NOT FOUND";
		
		mShow = false;

		mTextColor = mStyle->color("contrast");

		mBox = new Container(nullptr, GraphicsSettings::get().width * 0.5, GraphicsSettings::get().height * 0.5, GraphicsSettings::get().width * 0.2, GraphicsSettings::get().height * 0.15);

		mRenderedText = new Texture(mMessage, mStyle->font("default"), mStyle->size(), mTextColor);
		mRenderedText->setParent(mBox);
		mRenderedText->setCenterPos(Vector2(0.f, mBox->getBounds().height * -0.20f));

		mButton = new Button(mBox, "OK", 0, mBox->getBounds().height * 0.20f, 40, 20);
	}

	MessageBox::~MessageBox()
	{
		delete mButton;
		mButton = nullptr;

		delete mRenderedText;
		mRenderedText = nullptr;

		delete mBox;
		mBox = nullptr;

		mStyle = nullptr;
	}

	MessageBox* MessageBox::instance()
	{
		if (sInstance == nullptr)
			sInstance = new MessageBox();

		return sInstance;
	}

	void MessageBox::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	const bool MessageBox::isShowing() const
	{
		return mShow;
	}

	void MessageBox::show()
	{
		mShow = true;
	}

	void MessageBox::setMessage(std::string message)
	{
		mRenderedText->setText(message, mStyle->font("default"), mStyle->size(), mTextColor);
	}

	void MessageBox::update()
	{
		if (mShow)
		{
			mButton->update();

			if (mButton->getState() == Button::BUTTON_STATE::pressed || InputHandler::instance()->keyPressed(SDL_SCANCODE_RETURN))
			{
				mShow = false;
			}
		}
	}

	void MessageBox::render()
	{
		if (mShow)
		{
			mBox->render();

			if (mRenderedText != nullptr)
				mRenderedText->render();

			mButton->render();
		}
		
	}
}