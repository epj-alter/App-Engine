#include "stdafx.h"
#include "CheckButton.h"

namespace Engine
{
	/* Constructor / Destructor */
	CheckButton::CheckButton(GameEntity* parent, int x, int y, int width, int height, bool is_radio, bool opaque)
		: Container(parent, x, y, width, height)
	{
		if (opaque)
		{
			mFillColor = mStyle->color("reduced");
			mLineColor = mStyle->color("neutral");
			mTextColor = mStyle->color("light");
		}
		else
			mTextColor = mStyle->color("contrast");

		isRadio = is_radio;
	}

	CheckButton::~CheckButton()
	{
		for (auto radiobut : mButton)
		{
			delete radiobut.second;
			radiobut.second = nullptr;
		}
		mButton.clear();

		for (auto itr : mLabel)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mLabel.clear();
	}

	/* Modifiers */
	void CheckButton::addButton(std::string name, bool disabled, bool selected)
	{
		mButton.insert({name, new Button(this, -30.f, -25.f + (abs(-25.f) * (mButton.size())), 20, 20, disabled, selected)});

		mLabel.insert({ name, new Texture(name, mStyle->font("default"), mStyle->size(), mTextColor) });
		mLabel[name]->setParent(this);
		mLabel[name]->setCenterPos(Vector2(-15.f + mLabel[name]->getBounds().width *0.5f, -25.f + (abs(-25.f) * (mButton.size() -1))));
	}

	/* Core Functions */
	void CheckButton::update()
	{
		if (!isRadio)
		{
			for (auto itr : mButton)
			{
				itr.second->update();

				if (itr.second->getState() == Button::pressed)
				{
					if(!itr.second->isDisabled())
						itr.second->setSelected(!itr.second->isSelected());
				}
			}
		}
		else
		{
			for (auto itr : mButton)
			{
				itr.second->update();

				if (itr.second->getState() == Button::pressed)
				{
					if (!itr.second->isDisabled())
							itr.second->setSelected(!itr.second->isSelected());

					for (auto itr2 : mButton)
					{
						if (itr2 != itr)
							if (!itr2.second->isDisabled())
									itr2.second->setSelected(false);
					}
				}
			}
		}
	}
	

	void CheckButton::render()
	{
		mShape.x = mLeft; //- mGraphics->getCamera().x);
		mShape.y = mTop; //- mGraphics->getCamera().y);
		mShape.w = mWidth;
		mShape.h = mHeight;

		Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);

		if (!mButton.empty())
		{
			for (auto itr : mButton)
			{
				itr.second->render();
			}
		}

		if (!mLabel.empty())
		{
			for (auto itr : mLabel)
			{
				itr.second->render();
			}
		}

	}
}