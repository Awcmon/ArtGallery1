
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
	//cout << angr_normalize((float)M_PI);
	Window window("Hi", 800, 600, SDL_WINDOW_SHOWN);
	bool run = true;
	EventContainer events;
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

	vector<Vector2f> points1 =
	{
		Vector2f(0,0),
		Vector2f(0,450),
		Vector2f(600,450),
		Vector2f(600,0),
		Vector2f(300, 300)
	};

	Polygon poly(points1);

	ArtGallery gallery(poly);

	Vector2f guardpos = Vector2f(100, 121);
	Polygon visible = gallery.generateVisible(guardpos);

	Trace tr(Vector2f(300.0f, 0.0f), Vector2f(300.0f, 1000.0f), poly);
	printVec(tr.hits, " ");

	while (run)
	{
		events.think();
		if (events.has_event_type(SDL_QUIT))
		{
			run = false;
		}

		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.renderer);

		//Draw a black background
		SDL_Rect fillRect = { 0, 0, 800, 600 };
		SDL_SetRenderDrawColor(window.renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(window.renderer, &fillRect);

		//Draw test poly
		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		drawPolygon(window.renderer, poly);

		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0, 0, 0xFF);
		drawPolygon(window.renderer, visible);

		SDL_RenderDrawPoint(window.renderer, (int)guardpos.x, (int)guardpos.y);
		
		SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 0xFF);
		for (int i = 0; i < (int)tr.hits.size(); i++)
		{
			SDL_RenderDrawPoint(window.renderer, (int)tr.hits[i].x, (int)tr.hits[i].y);
		}

		SDL_RenderPresent(window.renderer);
	}

	return 0;
}
