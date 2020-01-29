#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "AssetsHandler.h"

namespace Engine
{
	class InputHandler
	{
	public:

		enum class MOUSE_BUTTONS { left, right, middle, back, forward };

	private:

		static InputHandler* sInstance;
		static SDL_Event sEvents;

		//KeyBoard
		Uint8* mPreviousKeyboardState;
		const Uint8* mKeyboardState;
		int mKeyLenght;

		//Mouse
		Uint32 mPreviousMouseState;
		Uint32 mMouseState;
		int mMouseXPos;
		int mMouseYPos;

		bool mExitGame;

		/* Constructor / Destructor */
		InputHandler();
		~InputHandler();

	public:

		/* Instance Functions */
		static InputHandler* instance();
		static void release();

		static void setEvent(SDL_Event event);
		static SDL_Event& getEvent();

		/* Accessors */

		//KeyBoard
		bool keyUsed(SDL_Scancode scan_code);
		bool keyPressed(SDL_Scancode scan_code);
		bool keyReleased(SDL_Scancode scan_code);
		bool exitGame() const;

		//Mouse
		Vector2 getMousePosition();
		bool mouseButtonUsed(MOUSE_BUTTONS button);
		bool mouseButtonPressed(MOUSE_BUTTONS button);
		bool mouseButtonReleased(MOUSE_BUTTONS button);

		void exitGame(bool exit_game);

		/* CORE */
		void update();
		void updatePreviousInput();
	};
}

#endif