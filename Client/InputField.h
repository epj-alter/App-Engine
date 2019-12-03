#ifndef INPUTFIELD_H
#define INPUTFIELD_H
#include "Button.h"

namespace Engine
{
	class InputField : public Container
	{
	private:

		Texture* mRenderedText;
		std::string mText;

		SDL_Color mTextColor;
		SDL_Color mInactiveColor;
		SDL_Color mActiveColor;

		bool mFocus;

	public:

		InputField(GameEntity* parent,	int x, int y, int width, int height, bool opaque = false);

		~InputField();

		/* Accessors */
		bool hasFocus() const;
		std::string getText() const;

		/* Text Modifiers */
		void addText();
		void removeText();
		void pasteText(std::string clipboard_text);

		void update();
		void render() override;

	};
}

#endif