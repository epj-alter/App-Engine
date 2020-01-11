#include "stdafx.h"
#include "Container.h"

namespace Engine
{
	Container::Container(GameEntity* parent, int x, int y, int width, int height, Uint8 opacity)
		: mBounds(mLeft, mTop, mWidth, mHeight)
	{
		mInput = InputHandler::instance();
		mStyle = StylesHandler::instance();

		mLeft = NULL;
		mTop = NULL;
		mWidth = NULL;
		mHeight = NULL;

		mFillColor = mStyle->color("neutral");
		mLineColor = mStyle->color("reduced");

		mFillColor.a = opacity;
		mLineColor.a = opacity;
		
		mShape.x = mLeft;
		mShape.y = mTop;
		mShape.w = mWidth;
		mShape.h = mHeight;

		setParent(parent);
		setBounds(x, y, width, height);
	}

	Container::~Container()
	{
		mStyle = nullptr;
		mInput = nullptr;
	}

	/* Accessors */
	intRect Container::getBounds() const
	{
		return mBounds;
	}

	void Container::colors(SDL_Color fill_color, SDL_Color line_color)
	{
		mFillColor = fill_color;
		mLineColor = line_color;
	}

	/* Modifiers */
	void Container::alpha(Uint8 opacity)
	{
		mFillColor.a = opacity;
		mLineColor.a = opacity;
	}

	void Container::translate(Vector2 vec, SPACE space)
	{
		if (space == SPACE::general)
		{
			mCenterPos += vec;
			mLeft += static_cast<int>(vec.x);
			mTop += static_cast<int>(vec.y);
		}
	}

	void Container::setBounds(int x, int y, int width, int height)
	{
		if (mParent == nullptr)
		{
			mWidth = mScale.x * width;
			mHeight = mScale.y * height;
			setCenterPos(Vector2(x, y));
			mLeft = getCenter().x - mWidth * 0.5f;
			mTop = getCenter().y - mHeight * 0.5f;
		}
		else
		{
			mWidth = mScale.x * width;
			mHeight = mScale.y * height;
			setCenterPos(Vector2(x + getCenter().x, y + getCenter().y));
			mLeft = getCenter().x - mWidth * 0.5f;
			mTop = getCenter().y - mHeight * 0.5f;
		}
	}

	/* Core Functions */
	void Container::update()
	{
	}

	void Container::render()
	{
		if (mFillColor.a != 0 || mLineColor.a != 0)
		{
			mShape.x = mLeft; //- mGraphics->getCamera().x);
			mShape.y = mTop; //- mGraphics->getCamera().y);
			mShape.w = mWidth;
			mShape.h = mHeight;

			Graphics::Instance()->drawRectangle(&mShape, mFillColor, mLineColor);
		}
	}
}