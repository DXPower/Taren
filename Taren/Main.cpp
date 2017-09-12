#include <SDL.h>
#include <stdio.h>
#include "Application.h"
#include "Game.h"

int main(int argc, char* args[]) {
	if (!Application::Init()) {
		printf("Failed to init!\n");
	} else {
		Game::Init();
		Application::Close();
	}

	return 0;
}