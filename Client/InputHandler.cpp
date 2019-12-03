#include "stdafx.h"
#include "InputHandler.h"

namespace Engine
{
	/* Instance to NULL */
	InputHandler* InputHandler::sInstance = nullptr;
	SDL_Event InputHandler::sEvents = SDL_Event();

	InputHandler::InputHandler()
	{
		this->mMouseXPos = NULL;
		this->mMouseYPos = NULL;
		this->mKeyboardState = SDL_GetKeyboardState(&this->mKeyLenght);
		this->mPreviousKeyboardState = new Uint8[this->mKeyLenght];
		memcpy(this->mPreviousKeyboardState, this->mKeyboardState, this->mKeyLenght);

		mExitGame = false;
	}

	InputHandler::~InputHandler()
	{

		delete[] this->mPreviousKeyboardState;
		this->mPreviousKeyboardState = nullptr;
	}

	InputHandler* InputHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new InputHandler();

		return sInstance;
	}

	void InputHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	void InputHandler::setEvent(SDL_Event event)
	{
		sEvents = event;
	}

	SDL_Event& InputHandler::getEvent()
	{
		return sEvents;
	}

	bool InputHandler::keyUsed(SDL_Scancode scanCode)
	{
		return this->mKeyboardState[scanCode];
	}

	bool InputHandler::keyPressed(SDL_Scancode scan_code)
	{
		return !this->mPreviousKeyboardState[scan_code] && this->mKeyboardState[scan_code];
	}

	bool InputHandler::keyReleased(SDL_Scancode scan_code)
	{
		return this->mPreviousKeyboardState[scan_code] && !this->mKeyboardState[scan_code];
	}

	bool InputHandler::exitGame() const
	{
		return mExitGame;
	}

	Vector2 InputHandler::getMousePosition()
	{
		return Vector2(static_cast<float>(this->mMouseXPos), static_cast<float>(this->mMouseYPos));
	}

	bool InputHandler::mouseButtonUsed(MOUSE_BUTTONS button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;

		case right:
			mask = SDL_BUTTON_RMASK;
			break;

		case middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		};

		return (this->mMouseState & mask);
	}

	bool InputHandler::mouseButtonPressed(MOUSE_BUTTONS button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;

		case right:
			mask = SDL_BUTTON_RMASK;
			break;

		case middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		};

		return !(this->mPreviousMouseState & mask) && (this->mMouseState & mask);
	}

	bool InputHandler::mouseButtonReleased(MOUSE_BUTTONS button)
	{
		Uint32 mask = 0;

		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;

		case right:
			mask = SDL_BUTTON_RMASK;
			break;

		case middle:
			mask = SDL_BUTTON_MMASK;
			break;

		case back:
			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		};

		return (this->mPreviousMouseState & mask) && !(this->mMouseState & mask);
	}

	void InputHandler::exitGame(bool exit_game)
	{
		mExitGame = exit_game;
	}

	void InputHandler::update()
	{
		this->mMouseState = SDL_GetMouseState(&this->mMouseXPos, &this->mMouseYPos);
	}

	void InputHandler::updatePreviousInput()
	{
		memcpy(this->mPreviousKeyboardState, this->mKeyboardState, this->mKeyLenght);
		this->mPreviousMouseState = this->mMouseState;
	}
}