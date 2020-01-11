#include "stdafx.h"
#include "Texture.h"

namespace Engine
{
	/* Cosntructor / Destructor */
	Texture::Texture(std::string file_name)
		: mBounds(mRenderRect.x, mRenderRect.y, mRenderRect.w, mRenderRect.h)
	{
		mGraphics = Graphics::Instance();
		mTexture = AssetsHandler::instance()->getTexture(file_name);

		SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

		mClipped = false;

		mRenderRect = SDL_Rect();
		mClippedRect = SDL_Rect();

		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;

		mExpanded = false;
	}

	Texture::Texture(std::string file_name, bool stretched_image)
		: mBounds(mRenderRect.x, mRenderRect.y, mRenderRect.w, mRenderRect.h)
	{
		mExpanded = stretched_image;
		mGraphics = Graphics::Instance();

		mTexture = AssetsHandler::instance()->getTexture(file_name);

		mClipped = false;

		mRenderRect = SDL_Rect();
		mClippedRect = SDL_Rect();

		mWidth = GraphicsSettings::instance()->get().width;
		mHeight = GraphicsSettings::instance()->get().height;
	}

	Texture::Texture(std::string file_name, int x, int y, int width, int height)
		: mBounds(mRenderRect.x, mRenderRect.y, mRenderRect.w, mRenderRect.h)
	{
		mGraphics = Graphics::Instance();
		mTexture = AssetsHandler::instance()->getTexture(file_name);

		mClipped = true;

		mWidth = width;
		mHeight = height;

		mRenderRect = SDL_Rect();
		mClippedRect = SDL_Rect();

		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;

		mClippedRect.x = x;
		mClippedRect.y = y;
		mClippedRect.w = mWidth;
		mClippedRect.h = mHeight;

		mExpanded = false;
	}

	Texture::Texture(std::string text, std::string font, int size, SDL_Color color)
		: mBounds(mRenderRect.x, mRenderRect.y, mRenderRect.w, mRenderRect.h)
	{
		mClippedRect = SDL_Rect();

		mGraphics = Graphics::Instance();
		mTexture = AssetsHandler::instance()->getText(text, font, size, color);

		mClipped = false;

		SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;

		mExpanded = false;
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mGraphics = nullptr;
	}

	intRect Texture::getBounds() const
	{
		return mBounds;
	}

	void Texture::setText(std::string text, std::string font, int size, SDL_Color color)
	{
		mClippedRect = SDL_Rect();

		mGraphics = Graphics::Instance();
		mTexture = AssetsHandler::instance()->getText(text, font, size, color);

		mClipped = false;

		SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;

		mExpanded = false;
	}

	void Texture::setAlpha(Uint8 value)
	{
		SDL_SetTextureAlphaMod(mTexture, value);
	}

	void Texture::setBlend(SDL_BlendMode mode)
	{
		SDL_SetTextureBlendMode(mTexture, mode);
	}

	void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_SetTextureColorMod(mTexture, r, g, b);
	}

	/* Core Functions */
	void Texture::render()
	{
		if (!mExpanded)
		{
			Vector2 position = VECT2_ZERO;

			if (mParent == nullptr)
				position = getCenter(SPACE::own);
			else
				position = getCenter(SPACE::general);

			// this is for the future player class.
			//static_cast<int>((position.x - mWidth * scale.x * 0.5f) - mGraphics->getCamera().x);  
			//static_cast<int>((position.y - mHeight * scale.y * 0.5f) - mGraphics->getCamera().y);

			mRenderRect.x = static_cast<int>((position.x - mWidth * mScale.x * 0.5f)); //- mGraphics->getCamera().x);
			mRenderRect.y = static_cast<int>((position.y - mHeight * mScale.y * 0.5f)); //- mGraphics->getCamera().y);
			mRenderRect.w = static_cast<int>(mWidth * mScale.x);
			mRenderRect.h = static_cast<int>(mHeight * mScale.y);

			mGraphics->drawTexture(mTexture, (mClipped) ? &mClippedRect : nullptr, &mRenderRect, getRotation(SPACE::general));
		}
		else
		{
			mGraphics->drawTexture(mTexture);
		}
		
	}
}
