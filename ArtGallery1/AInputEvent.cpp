#include "AInputEvent.h"


AInputEvent::AInputEvent()
{
	
}

AInputEvent::~AInputEvent()
{

}

//More like has event
bool AInputEvent::isEvent(int ev)
{
	for (int i = 0; i < eventsStored; i++)
	{
		if (events[i].type == ev)
		{
			return true;
		}
	}
	return false;
}

int AInputEvent::mouseWheelY()
{
	//if (eventTypes[0] == 0) { return 0; }
	for (int i = 0; i < eventsStored; i++)
	{
		if (events[i].type == SDL_MOUSEWHEEL)
		{
			return events[i].wheel.y;
		}
	}
	return 0;
}

bool AInputEvent::keyDown(int _key)
{
	for (int i = 0; i < eventsStored; i++)
	{
		if ((events[i].type == SDL_KEYDOWN) && ((events[i].key.keysym.sym == _key) || (events[i].key.keysym.scancode == _key)))
		{
			return true;
		}
	}
	return false;
}

bool AInputEvent::keyPressed(int _key)
{
	for (int i = 0; i < eventsStored; i++)
	{
		if ((events[i].type == SDL_KEYDOWN) && ( (events[i].key.keysym.sym == _key) || (events[i].key.keysym.scancode == _key) ) && (events[i].key.repeat == 0))
		{
			printf("KeyPressed\n");
			return true;
		}
	}
	return false;
}

bool AInputEvent::keyReleased(int _key)
{
	for (int i = 0; i < eventsStored; i++)
	{
		if ((events[i].type == SDL_KEYUP) && ( (events[i].key.keysym.sym == _key) || (events[i].key.keysym.scancode == _key) ) && (events[i].key.repeat == 0))
		{
			printf("KeyReleased\n");
			return true;
		}
	}
	return false;
}

bool AInputEvent::mousePressed(int _button)
{
	for (int i = 0; i < eventsStored; i++)
	{
		if (events[i].type == SDL_MOUSEBUTTONDOWN)
		{
			if (events[i].button.button == _button)
			{
				return true;
			}
		}
	}
	return false;
}

bool AInputEvent::mouseReleased(int _button)
{
	for (int i = 0; i < eventsStored; i++)
	{
		if (events[i].type == SDL_MOUSEBUTTONUP)
		{
			if (events[i].button.button == _button)
			{
				return true;
			}
		}
	}
	return false;
}

//Populates the event arrays
void AInputEvent::think()
{
	//Reset the two arrays
	std::fill_n(eventTypes, MAX_EVENTS, 0);
	for (int i = 0; i < MAX_EVENTS; i++)
	{
		events[i] = defaultEvent;
	}

	//PeepEvents is stupid and doesn't work.
	//eventsStored = SDL_PeepEvents(events, MAX_EVENTS, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);

	int i = 0;
	while (SDL_PollEvent(&e) != 0)
	{
		if (i >= MAX_EVENTS)
		{
			break;
		}

		events[i] = e;
		eventTypes[i] = e.type;

		i++;
	}
	eventsStored = i;
}
