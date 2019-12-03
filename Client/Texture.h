#ifndef TEXTURE_H
#define TEXTURE_H
#include "GameEntity.h"

namespace Engine
{
	class Texture : public GameEntity
	{
	protected:

		Graphics* mGraphics;
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
		bool mClipped;
		bool mExpanded;

		SDL_Rect mRenderRect;
		SDL_Rect mClippedRect;

		intRect mBounds;

	public:

		/* Cosntructor / Destructor */
		Texture(std::string file_name);
		Texture(std::string file_name, bool expanded_image); // set always to true
		Texture(std::string file_name, int x, int y, int width, int height);
		Texture(std::string text, std::string font, int size, SDL_Color color);
		virtual ~Texture();

		/* Accessors */
		intRect getBounds() const;

		/* Mutators */
		void setText(std::string text, std::string font, int size, SDL_Color color);
		void setAlpha(Uint8 value);
		void setBlend(SDL_BlendMode mode);
		void setColor(Uint8 r, Uint8 g, Uint8 b);

		/* Core Functions */
		virtual void render();
	};
}

#endif