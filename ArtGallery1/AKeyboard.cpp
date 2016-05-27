#include "AKeyboard.h"


AKeyboard::AKeyboard()
{

}

AKeyboard::~AKeyboard()
{

}

AKeyboard::AKeyboard(AInputEvent *_inputEvent)
{
	inputEvent = _inputEvent;
}

void AKeyboard::setInputEvent(AInputEvent *_inputEvent)
{
	inputEvent = _inputEvent;
}

//Keyboard keyDown returns whether or not the key is physically down, while input keyDown does something similar to how a key is registered in text input.
bool AKeyboard::keyDown(int _key)
{
	if (keystate[_key])
	{
		return true;
	}
	else if (keystate[SDL_GetScancodeFromKey(_key)])
	{
		return true;
	}
	return false;
}

bool AKeyboard::keyPressed(int _key)
{
	return inputEvent->keyPressed(_key);
}

bool AKeyboard::keyReleased(int _key)
{
	return inputEvent->keyReleased(_key);
}

void AKeyboard::think()
{
	keystate = SDL_GetKeyboardState(NULL);
}
