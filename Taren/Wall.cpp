#include "Wall.h"
#include "RepeatRenderer.h"
#include "Collision.h"
#include <iostream>

Wall::Wall(Vector2 pos, SDL_Texture* texture) : GameObject(new RepeatRenderer(this, texture), new SquareCollider(this), pos) {
	SetSize(Vector2(580, 420));
	SetEnabled(true);
	renderer->SetEnabled(true);

	name = "Wall";
}


Wall::~Wall() {}