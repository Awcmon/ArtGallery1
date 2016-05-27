#pragma once
#include <SDL.h>
#include "AInputEvent.h"

class AKeyboard
{
public:
	AKeyboard();
	AKeyboard(AInputEvent *_inputEvent);
	~AKeyboard();

	void setInputEvent(AInputEvent *_inputEvent);

	bool keyDown(int _key);
	bool keyPressed(int _key);
	bool keyReleased(int _key);

	void think();

private:
	AInputEvent *inputEvent;
	const Uint8 *keystate;
};

