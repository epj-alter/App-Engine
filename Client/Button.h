#ifndef BUTTON_H
#define BUTTON_H

#include "Container.h"

namespace Engine
{
	class Button : public Container
	{
	public:
		enum class BUTTON_STATE { idle, hovered, pressed };

	private:

		BUTTON_STATE mState;

		Texture* mLabel;
		std::string mText;

		bool mTextButton;

		bool mDisabled;
		bool mSelected;

		SDL_Color mTextColor;

		SDL_Color mIdleColor;
		SDL_Color mHoveredColor;
		SDL_Color mPressedColor;
		SDL_Color mSelectedColor;

	public:
		/* Cosntructor / Destructor */
		Button(GameEntity* parent, std::string text, int x, int y, int width, int height, bool text_only = false, bool default_button = true);	// Default Button
		Button(GameEntity* parent, int x, int y, int width, int height, bool disabled, bool selected = false);									// Check Button
	
		virtual ~Button();

		/* Accessors */
		const std::string getText() const;
		const BUTTON_STATE getState();
		bool isDisabled() const;
		bool isSelected() const;

		/* Modifiers */
		void setLabel(std::string label, StylesHandler::FONT_MODIFIER size_mod = StylesHandler::FONT_MODIFIER::medium, std::string font_path = "default");

		void setDisable();
		void setSelected(bool select);

		/* Core */
		void update() override;
		void render() override;
	};
}

#endif // !BUTTON_H