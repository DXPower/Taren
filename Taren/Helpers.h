#pragma once
#include <SDL.h>
#include <string>
#include <sstream>

class Rect {
	public:
	Rect() {};
	Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

	float x;
	float y;
	float w;
	float h;

	SDL_Rect ToSDL();

	std::string ToString();
};

