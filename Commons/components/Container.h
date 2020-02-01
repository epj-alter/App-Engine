#ifndef CONTAINER_H
#define CONTAINER_H

#include "../src/StylesHandler.h"

namespace GUI
{
	/* Forward Declarations */
	class Container;
	class Button;
	class InputField;
	class CheckButton;
	class DropDownList;
	class ProgressBar;
	class Slider;
	class MessageBox;
	class ConfirmationBox;

	typedef std::map<std::string, SDL_Scancode> aKeyMap;
	typedef std::map<std::string, Texture*> aLabelMap;
	typedef std::map<std::string, Container*> aContainerMap;
	typedef std::map<std::string, Button*> aButtonMap;
	typedef std::map<std::string, InputField*> aInputFieldMap;
	typedef std::map<std::string, CheckButton*> aCheckButtonMap;
	typedef std::map<std::string, DropDownList*> aDropdownListMap;
	typedef std::map<std::string, ProgressBar*> aProgressBarMap;
	typedef std::map<std::string, Slider*> aSliderMap;
	typedef std::map<std::string, ConfirmationBox*> aConfirmationBoxMap;

	class Container : public GameEntity
	{

	protected:

		InputHandler* mInput;
		StylesHandler* mStyle;
		intRect mBounds;
		SDL_Rect mShape;

		int mLeft;
		int mTop;
		int mWidth;
		int mHeight;

		SDL_Color mFillColor;
		SDL_Color mLineColor;

	public:

		/* Constructor / Destructor */
		Container(GameEntity* parent, int x, int y, int width, int height, Uint8 opacity = 255);
		virtual ~Container();

		/* Accessors */
		intRect getBounds() const;

		/* Modifiers */
		void translate(Vector2 vec, SPACE space = SPACE::general) override;
		void setBounds(int x, int y, int width, int height);

		void colors(SDL_Color fill_color, SDL_Color line_color);
		void alpha(Uint8 opacity);

		/* Core Functions */
		virtual void update();
		virtual void render();
	};
}

#endif