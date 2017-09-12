#pragma once
#include <SDL.h>
#include <unordered_map>
#include <list>

using namespace std;

class Input {
	public:
	static unordered_map<const SDL_Scancode, list<Input*>> keyboardEvents;
	static unordered_map<const SDL_Scancode, list<Input*>> keydownEvents;

	Input() {};
	
	static void ScanKeyboard();
	static void PollEvents();
	static void RegisterKeyboardListener(const SDL_Scancode, Input*);
	static void RegisterKeyDownListener(const SDL_Scancode, Input*);

	virtual void KeyboardEvent(const SDL_Scancode) {};
	virtual void KeyDownEvent(const SDL_Scancode) {};
};





