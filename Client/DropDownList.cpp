#include "stdafx.h"
#include "DropDownList.h"

namespace Engine
{
	/* Constructor / Destructor */
	DropDownList::DropDownList(GameEntity* parent, int x, int y, int width, int height, bool opaque)
		: Container(parent, x, y, width, height)
	{
		mOpen = false;
		mOpenHeight = NULL;

		if (opaque)
		{
			mFillColor = mStyle->color("reduced");
			mLineColor = mStyle->color("neutral");
			mTextColor = mStyle->color("light");
		}
		else
			mTextColor = mStyle->color("contrast");

		mIndex = new Button(this, "--", 0, 0, mWidth, mHeight);
	}

	DropDownList::~DropDownList()
	{
		for (auto itr : mItems)
		{
			delete itr;
			itr = nullptr;
		}

		delete mIndex;
		mIndex = nullptr;

		mItems.clear();
		mItems.shrink_to_fit();
	}

	const std::string DropDownList::getIndex() const
	{
		return mIndex->getText();
	}

	/* Functions */
	void DropDownList::open()
	{
		if (!mOpen)
		{
			if (mBounds.contains(mInput->getMousePosition()) && mInput->mouseButtonPressed(InputHandler::left))
			{
				mOpen = true; 
				mHeight = mOpenHeight;
			}
		}
		else
		{
			for (auto itr : mItems)
			{
				itr->update();

				if (itr->getState() == Button::pressed)
				{
					mOpen = false;
					mHeight = itr->getBounds().height; //static_cast<int>(mOpenHeight / mItems.size());
					mIndex->setLabel(itr->getText());
				}
				else if (mInput->mouseButtonPressed(InputHandler::left) && (!mBounds.contains(mInput->getMousePosition()) || mIndex->getState() == Button::pressed))
				{
					mOpen = false;
					mHeight = itr->getBounds().height; //static_cast<int>(mOpenHeight / mItems.size());
				}
			}
		}
	}

	void DropDownList::addItem(std::string label)
	{
		mItems.push_back(new Button(this, label, 0, mHeight + mHeight * (mItems.size()), mWidth, mHeight));

		mIndex->setLabel(mItems.front()->getText());

		mOpenHeight  = mHeight * (mItems.size() + 1);
		if (mOpenHeight > mMaxHeight)
			mOpenHeight = mMaxHeight;
	}

	void DropDownList::removeItem()
	{
	}

	/* Core Functions */
	void DropDownList::update()
	{
		mIndex->update();
		this->open();
	}

	void DropDownList::render()
	{
		mShape.x = mLeft; //- mGraphics->getCamera().x);
		mShape.y = mTop; //- mGraphics->getCamera().y);
		mShape.w = mWidth;
		mShape.h = mHeight;

		Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);

		if (!mOpen)
			mIndex->render();
		else
		{
			mIndex->render();

			for (auto itr : mItems)
				itr->render();
		}
	}
}