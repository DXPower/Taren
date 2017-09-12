#pragma once
#include "Game.h"
#include "Input.h"

unordered_map<const SDL_Scancode, list<Input*>> Input::keyboardEvents;
unordered_map<const SDL_Scancode, list<Input*>> Input::keydownEvents;

void Input::PollEvents() {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			case SDL_QUIT:
				Game::quit = true;
				break;
			case SDL_KEYDOWN:
				if (keydownEvents.find(e.key.keysym.scancode) != keydownEvents.end() && e.key.repeat == 0) {
					for (Input* o : keydownEvents[e.key.keysym.scancode]) {
						o->KeyDownEvent(e.key.keysym.scancode);
					}
				}

				break;
		}
	}
}

void Input::RegisterKeyboardListener(const SDL_Scancode key, Input* o) {
	keyboardEvents[key].push_back(o);
}

void Input::RegisterKeyDownListener(const SDL_Scancode key, Input* o) {
	keydownEvents[key].push_back(o);
}

void Input::ScanKeyboard() {
	const Uint8* states = SDL_GetKeyboardState(NULL);

	for (pair<const SDL_Scancode, list<Input*>> pair : keyboardEvents) {
		if (states[pair.first]) {
			for (Input* o : pair.second) {
				o->KeyboardEvent(pair.first);
			}
		}
	}
}

