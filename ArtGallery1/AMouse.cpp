#include "AMouse.h"

extern SDL_Event e;

using awcutil::Vector2f;

AMouse::AMouse()
{
	m1pressed = false;
	m1released = false;
	m2pressed = false;
	m2released = false;
}

AMouse::AMouse(AInputEvent* _inputEvent)
{
	m1pressed = false;
	m1released = false;
	m2pressed = false;
	m2released = false;
	setInputEvent(_inputEvent);
}

AMouse::~AMouse()
{
	inputEvent = NULL;
}

void AMouse::setInputEvent(AInputEvent* _inputEvent)
{
	inputEvent = _inputEvent;
}

void AMouse::think()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	pos = Vector2f((float)x, (float)y);

	m1isDown = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
	m2isDown = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));

	m1pressed = inputEvent->mousePressed(SDL_BUTTON_LEFT);
	m1released = inputEvent->mouseReleased(SDL_BUTTON_LEFT);
	m2pressed = inputEvent->mousePressed(SDL_BUTTON_RIGHT);
	m2released = inputEvent->mouseReleased(SDL_BUTTON_RIGHT);

	mWheelY = inputEvent->mouseWheelY();
}
