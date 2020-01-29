#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include "Slider.h"

namespace GUI
{
	class MessageBox
	{
	private:
		static MessageBox* sInstance;

		StylesHandler* mStyle;

		std::string mMessage;

		Container* mBox;
		Texture* mRenderedText;
		Button* mButton;

		bool mShow;

		SDL_Color mTextColor;

		/* Constructor / Destructor */
		MessageBox();
		~MessageBox();

	public:
		/* Instance Functions */
		static MessageBox* instance();
		static void release();

		/* Accessors */
		const bool isShowing() const;

		/* Modifiers */
		void setMessage(std::string message);
		void show();

		/* Core Functions */
		void update();
		void render();
	};
}

#endif // !
