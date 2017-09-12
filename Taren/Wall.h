#pragma once
#include "GameObject.h"

class Wall : public GameObject {
	public:
	Wall(Vector2 pos, SDL_Texture* texture);
	~Wall();
};

