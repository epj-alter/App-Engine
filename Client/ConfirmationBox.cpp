#include "stdafx.h"
#include "ConfirmationBox.h"

namespace Engine
{
	ConfirmationBox::ConfirmationBox(std::string message)
	{
		mStyle = StylesHandler::instance();

		mMessage = message;

		mShow = false;
		mApply = false;

		mTextColor = mStyle->color("contrast");

		mBox = new Container(nullptr, GraphicsSettings::get().width * 0.5, GraphicsSettings::get().height * 0.5, GraphicsSettings::get().width * 0.2, GraphicsSettings::get().height * 0.15);

		mRenderedText = new Texture(mMessage, mStyle->font("default"), mStyle->size(), mTextColor);
		mRenderedText->setParent(mBox);
		mRenderedText->setCenterPos(Vector2(0.f, mBox->getBounds().height * -0.20f));

		mConfirm = new Button(mBox, "Confirm", mBox->getBounds().width * -0.20f, mBox->getBounds().height * 0.20f, 60, 25);
		mDecline = new Button(mBox, "Decline", mBox->getBounds().width * 0.20f, mBox->getBounds().height * 0.20f, 60, 25);
	}

	ConfirmationBox::~ConfirmationBox()
	{
		delete mDecline;
		mDecline = nullptr;

		delete mConfirm;
		mConfirm = nullptr;

		delete mRenderedText;
		mRenderedText = nullptr;

		delete mBox;
		mBox = nullptr;

		mStyle = nullptr;
	}

	const bool ConfirmationBox::isShowing() const
	{
		return mShow;
	}

	const bool ConfirmationBox::apply() const
	{
		return mApply;
	}

	void ConfirmationBox::show()
	{
		mApply = false;
		mShow = true;
	}

	void ConfirmationBox::update()
	{
		if (mShow)
		{
			mConfirm->update();
			mDecline->update();

			if (mConfirm->getState() == Button::pressed || InputHandler::instance()->keyPressed(SDL_SCANCODE_RETURN))
			{
				mShow = false;
				mApply = true;
			}
			else if (mDecline->getState() == Button::pressed || InputHandler::instance()->keyPressed(SDL_SCANCODE_ESCAPE))
			{
				mShow = false;
				mApply = false;
			}
		}
	}

	void ConfirmationBox::render()
	{
		if (mShow)
		{
			mBox->render();

			if (mRenderedText != nullptr)
				mRenderedText->render();

			mConfirm->render();
			mDecline->render();
		}

	}
}