#include "Spritesheet.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Collision.h"
#include "Resources.h"
#include "Application.h"
#include "Game.h"
#include "EventHandler.h"

Bullet::Bullet(Vector2 position) : GameObject(position) {
	SpritesheetRenderer* renderer = new SpritesheetRenderer(this);
	this->renderer = renderer;
	collider = new SquareCollider(this);

	Spritesheet* spritesheet = renderer->SetSpritesheet(Resources::GetTexture("bullet_spritesheet"));

	spritesheet->RegisterAnimation(0, new SpritesheetAnimation(0, 0, 32, 32, 5, 9, 0));

	spritesheet->SetAnimation(0);
	spritesheet->SetFrame(7);

	this->spritesheet = spritesheet;
	name = "Bullet";

	renderer->SetEnabled(true);

	//boundingRect = Rect(Position()->x, Position()->y, 41, 42);
}

void Bullet::SetDirection(Vector2 direction) {
	Vector2 v = direction;

	v.Normalize();
	v = v * speed;
	SetVelocity(&v);
}

void Bullet::ChangeTexture(int frame) {
	spritesheet->SetFrame(frame);
}

GameObject* Bullet::Clone() {
	return new Bullet(Vector2(0, 0));
}

void Bullet::CollisionEnter(Collider* c, SDL_Rect intersection) {
	if (c->gameobject->name == "Wall") {
		Game::InvokeGameEvent("random", RandomEventData("random", "event message", 12));

		Destroy();
	}
}