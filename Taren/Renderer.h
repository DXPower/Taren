#pragma once;
#include <SDL.h>
#include "Vector2.h"
#include "Helpers.h"

class GameObject;

class Renderer {
	public:
	GameObject* gameobject;

	Renderer(GameObject* gameobject);
	Renderer(GameObject* gameobject, SDL_Texture* texture);
	Renderer(GameObject* gameobject, const Renderer&);
	~Renderer();

	virtual Vector2 GetTextureSize();
	virtual inline SDL_Texture* GetTexture();
	virtual void SetTexture(SDL_Texture* texture);
	virtual void Render();
	virtual void GameObjectSizeChanged(Vector2 size);

	inline bool GetEnabled() {
		return enabled;
	}

	inline void SetEnabled(bool f) {
		enabled = f;
	}

	protected:
	SDL_Texture* texture;

	Vector2 rect;

	bool enabled;
};