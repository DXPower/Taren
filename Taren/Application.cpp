#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Application.h"
#include "Resources.h"

using namespace std;

SDL_Window* Application::gWindow = NULL;
SDL_Renderer* Application::gRenderer = NULL;
//SDL_Surface* Application::gScreenSurface = NULL;
SDL_Surface* Application::gHelloWorld = NULL;

bool Application::Init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		Error("SDL could not initialize. SDL_ERROR: : %s\n", SDL_GetError());
		success = false;
	} else {
		gWindow = SDL_CreateWindow("Taren", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			Error("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		} else {
			int imageFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imageFlags) & imageFlags)) {
				Error("SDL_image could not initialize. SDL_image error: %s\n", SDL_GetError());
				success = false;
			} else if (!Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				Application::Error("SDL mixer could not initialize! Error: %s\n", Mix_GetError());
			} else {
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

				if (gRenderer == NULL) {
					Error("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				} else {
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
			}
		}
	}

	return success;
}

Uint32 Application::GetPixelFormat() {
	return SDL_GetWindowPixelFormat(gWindow);
}

void Application::Close() {
	Resources::FreeAllResources();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Application::Error(const char* message, ...) {
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
}