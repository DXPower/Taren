#pragma once
#include "Renderer.h"
class RepeatRenderer : public Renderer {
	public:
	RepeatRenderer(GameObject* g, SDL_Texture* texture);
	~RepeatRenderer();

	void RepeatTexture();

	void Render() override;
	void GameObjectSizeChanged(Vector2 size) override;

	private:
	SDL_Texture* repeatedTexture = NULL;
};

