#pragma once
#include "Renderer.h"
#include "Game.h"
#include "GameObject.h"
#include "Application.h"

Renderer::Renderer(GameObject* gameobject) : gameobject(gameobject), rect(Vector2(0, 0)) {
	Game::RegisterRenderer(this);
}

Renderer::Renderer(GameObject* gameobject, SDL_Texture* texture) : Renderer(gameobject) {
	SetTexture(texture);
}

Renderer::Renderer(GameObject* gameobject, const Renderer& renderer) : Renderer(gameobject, renderer.texture) {

}

Renderer::~Renderer() {
	Game::UnregisterRenderer(this);
}

void Renderer::SetTexture(SDL_Texture* texture) {
	this->texture = texture;

	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	rect.x = w;
	rect.y = h;
}

SDL_Texture* Renderer::GetTexture() {
	return texture;
}

void Renderer::Render() {
	Vector2 size = gameobject->GetSize();
	SDL_Rect rect = {gameobject->Position()->x, gameobject->Position()->y, size.x, size.y};
	Game::RenderToScreen(Application::gRenderer, texture, NULL, &rect);
}

Vector2 Renderer::GetTextureSize() {
	return rect;
}

void Renderer::GameObjectSizeChanged(Vector2 size) {}