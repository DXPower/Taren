#include "Helpers.h"

SDL_Rect Rect::ToSDL() {
	SDL_Rect rect = SDL_Rect();
	rect.x = (int) x;
	rect.y = (int) y;
	rect.w = (int) w;
	rect.h = (int) h;

	return rect;
}

std::string Rect::ToString() {
	std::ostringstream s;
	s << "p(" << x << ", " << y << ")  s(" << w << ", " << h << ")";
	return s.str();
}
