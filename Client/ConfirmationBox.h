#ifndef CONFIRMATIONBOX_H
#define CONFIRMATIONBOX_H
#include "MessageBox.h"

namespace Engine
{
	class ConfirmationBox
	{
	private:

		StylesHandler* mStyle;

		std::string mMessage;

		Container* mBox;
		Texture* mRenderedText;
		Button* mConfirm;
		Button* mDecline;

		bool mShow;
		bool mApply;

		SDL_Color mTextColor;

	public:
		/* Constructor / Destructor */
		ConfirmationBox(std::string message);
		~ConfirmationBox();

		/* Accessors */
		const bool isShowing() const;
		const bool apply() const;

		/* Modifiers */
		void show();

		/* Core Functions */
		void update();
		void render();
	};
}

#endif // !