
#include <iostream>

#include <SDL.h>
#undef main
#undef M_PI

#define _AWCUTIL_SDL
#include <awcutil.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Polygon.h"
#include "ArtGallery.h"
#include "Trace.h"
#include "AMouse.h"
#include "AKeyboard.h"

using std::cout;

using awcutil::Vector2f;

using awcutil::clamp;
using awcutil::approach;
using awcutil::deg2rad;
using awcutil::rad2deg;
using awcutil::dsin;
using awcutil::dcos;
using awcutil::angd_normalize;
using awcutil::angd_difference;
using awcutil::angd_approach;
using awcutil::angd_forward;
using awcutil::angr_normalize;
using awcutil::angr_difference;
using awcutil::angr_approach;
using awcutil::angr_forward;

using awcutil::sdl::Window;
using awcutil::sdl::EventContainer;

void drawPolygon(SDL_Renderer* renderer, Polygon poly)
{
	for (int i = 0; i < (int)poly.vertices.size(); i++)
	{
		SDL_RenderDrawLine(renderer, (int)poly.vertices[i].x, (int)poly.vertices[i].y, (int)poly.vertices[(i + 1) % poly.vertices.size()].x, (int)poly.vertices[(i + 1) % poly.vertices.size()].y);
	}
}

void fillPolygon(SDL_Renderer* renderer, Polygon poly)
{
	bool start = false;
	for (int i = 0; i < 800; i++)
	{
		Trace tr(Vector2f(-10.0f,(float)i), Vector2f(1000.0f, (float)i), poly);
		if (tr.hits.size() > 0)
		{
			start = true;
		}
		for (int i = 0; i < (int)tr.hits.size() / 2; i++)
		{
			SDL_RenderDrawLine(renderer, (int)tr.hits[i*2].x, (int)tr.hits[i * 2].y, (int)tr.hits[i * 2 + 1].x, (int)tr.hits[i * 2 + 1].y);
		}
		if (start && tr.hits.size() == 0)
		{
			break;
		}
	}
}

template<typename T, typename A>
void printVec(std::vector<T, A> const& vec, string delim)
{
	for (int i = 0; i < (int)vec.size(); i++)
	{
		std::cout << vec[i] << delim;
	}
}

int main(int argc, char* args[])
{
	Window window("Hi", 800, 600, SDL_WINDOW_SHOWN);
	bool run = true;

	AMouse mouse;
	AKeyboard keyboard;

	AInputEvent input;
	mouse.setInputEvent(&input);
	keyboard.setInputEvent(&input);

	//EventContainer events;
	/*
	vector<Vector2f> points1 =
	{
		Vector2f(10,10),
		Vector2f(40,400),
		Vector2f(600,450),
		Vector2f(600,20),
		Vector2f(300, 300)
	};
	*/
	/*
	vector<Vector2f> points1 =
	{
		Vector2f(0.0f,0.0f),
		Vector2f(0.0f,450.0f),
		Vector2f(600.0f,450.0f),
		Vector2f(600.0f,0.0f),
		Vector2f(300.0f, 300.0f)
	};
	*/

	/*
	Polygon poly(points1);

	ArtGallery gallery(poly);

	Vector2f guardpos = Vector2f(300.0f, 400.0f);
	Polygon visible = gallery.generateVisible(guardpos);

	Trace tr(Vector2f(300.0f, 0.0f), Vector2f(300.0f, 1000.0f), poly);
	printVec(tr.hits, " ");
	*/

	vector<Vector2f> points;
	vector<Vector2f> guards;
	ArtGallery gallery;
	bool fill = false;

	while (run)
	{
		input.think();
		mouse.think();
		keyboard.think();
		/*
		events.think();
		if (events.has_event_type(SDL_QUIT))
		{
			run = false;
		}
		*/

		Vector2f mpos(mouse.pos.x, mouse.pos.y);

		if (input.isEvent(SDL_QUIT))
		{
			run = false;
		}

		if (keyboard.keyPressed(SDL_SCANCODE_R))
		{
			guards.clear();
		}

		if (keyboard.keyPressed(SDL_SCANCODE_T))
		{
			points.clear();
			guards.clear();
			gallery.enclosing.vertices.clear();
		}

		if (keyboard.keyPressed(SDL_SCANCODE_F))
		{
			fill = !fill;
		}

		if (keyboard.keyPressed(SDL_SCANCODE_Q))
		{
			points.push_back(mpos);
			if (points.size() >= 3)
			{
				gallery.enclosing = Polygon(points);
			}
		}

		if (keyboard.keyPressed(SDL_SCANCODE_E))
		{
			guards.push_back(mpos);
		}


		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.renderer);

		//Draw a black background
		SDL_Rect fillRect = { 0, 0, 800, 600 };
		SDL_SetRenderDrawColor(window.renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(window.renderer, &fillRect);


		//Draw poly
		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		if (gallery.enclosing.vertices.size() >= 3)
		{
			drawPolygon(window.renderer, gallery.enclosing);
		}

		SDL_SetRenderDrawColor(window.renderer, 0, 0, 0xFF, 0xFF);
		for (int i = 0; i < (int)guards.size(); i++)
		{
			if (fill)
			{
				fillPolygon(window.renderer, gallery.generateVisible(guards[i]));
			}
			else
			{
				drawPolygon(window.renderer, gallery.generateVisible(guards[i]));
			}
		}

		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		if (fill)
		{
			if (gallery.enclosing.vertices.size() >= 3)
			{
				drawPolygon(window.renderer, gallery.enclosing);
			}
		}

		//fillPolygon(window.renderer, visible);

		for (int i = 0; i < (int)guards.size(); i++)
		{
			SDL_RenderDrawPoint(window.renderer, (int)guards[i].x, (int)guards[i].y);
		}


		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
