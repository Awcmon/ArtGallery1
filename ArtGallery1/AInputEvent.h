#pragma once

#define MAX_EVENTS 32
/*
#define MAX_EVENTS_KEYBOARD 32
#define MAX_EVENTS_MOUSE 8
#define MAX_EVENTS_MOUSEWHEEL 8
*/

#include <SDL.h>
#include <iostream>

class AInputEvent
{
public:
	AInputEvent();
	~AInputEvent();

	bool isEvent(int ev);
	int mouseWheelY();
	bool keyDown(int _key);
	bool keyPressed(int _key);
	bool keyReleased(int _key);
	bool mousePressed(int _button);
	bool mouseReleased(int _button);

	void think();

private:
	SDL_Event e;
	SDL_Event defaultEvent;

	int eventTypes[MAX_EVENTS];
	SDL_Event events[MAX_EVENTS];

	int eventsStored;
};

