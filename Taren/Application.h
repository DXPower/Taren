#pragma once

#include <string>
#include <SDL.h>
using namespace std;

class Application {
	public:
	static bool quit;

	static const int SCREEN_WIDTH = 1000;
	static const int SCREEN_HEIGHT = 900;
	static const int SCREEN_WIDTH_HALF = SCREEN_WIDTH / 2;
	static const int SCREEN_HEIGHT_HALF = SCREEN_HEIGHT / 2;


	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;
	//static SDL_Surface* gScreenSurface;
	static SDL_Surface* gHelloWorld;
	static SDL_Event e;

	static Uint32 GetPixelFormat();
	static bool Init();
	static void Close();
	static void Error(const char*, ...);
};
