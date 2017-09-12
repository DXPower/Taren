#pragma once
#include "Game.h"
#include "RepeatRenderer.h"
#include "GameObject.h"
#include "Application.h"
#include <math.h>

RepeatRenderer::RepeatRenderer(GameObject* g, SDL_Texture* texture) : Renderer(g, texture) {
	repeatedTexture = SDL_CreateTexture(Application::gRenderer, Application::GetPixelFormat(), SDL_TEXTUREACCESS_TARGET, rect.x, rect.y);
	//RepeatTexture();
}


RepeatRenderer::~RepeatRenderer() {
}

void RepeatRenderer::Render() {
	Vector2 size = gameobject->GetSize();
	SDL_Rect r = {gameobject->Position()->x, gameobject->Position()->y, size.x, size.y};
	Game::RenderToScreen(Application::gRenderer, repeatedTexture, NULL, &r);
}

void RepeatRenderer::GameObjectSizeChanged(Vector2 size) {
	SDL_DestroyTexture(repeatedTexture);
	repeatedTexture = SDL_CreateTexture(Application::gRenderer, Application::GetPixelFormat(), SDL_TEXTUREACCESS_TARGET, size.x, size.y);
	RepeatTexture();
}

void RepeatRenderer::RepeatTexture() {
	SDL_SetRenderTarget(Application::gRenderer, repeatedTexture);

	Vector2 size = gameobject->GetSize();
	int nx = (int) ceilf(size.x / rect.x), ny = (int) ceilf(size.y / rect.y);

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			SDL_Rect tr = {i * rect.x, j * rect.y, rect.x, rect.y};
			SDL_RenderCopy(Application::gRenderer, texture, NULL, &tr);
		}
	}

	SDL_RenderPresent(Application::gRenderer);
	SDL_SetRenderTarget(Application::gRenderer, NULL);
}

