#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include "InputField.h"

namespace GUI
{
	class CheckButton : public Container
	{
	private:

		aButtonMap mButton;
		aLabelMap mLabel;

		bool isRadio;
		
		SDL_Color mTextColor;

	public:

		/* Constructor / Destructor */
		CheckButton(GameEntity* parent,	int x, int y, int width, int height, bool is_radio = false, bool opaque = false);

		~CheckButton();

		/* Modifiers */
		void addButton(std::string name, bool disabled = false, bool selected = false);

		/* Core Functions */
		void update();
		void render() override;
	};
}

#endif