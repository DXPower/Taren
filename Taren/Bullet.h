#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
	public:
	int speed = 10;

	Bullet(Vector2 position);
	~Bullet() {};

	void SetDirection(Vector2 direction);

	GameObject* Clone() override;
	void ChangeTexture(int frame);
	void CollisionEnter(Collider* c, SDL_Rect intersection) override;

	private:
	Spritesheet* spritesheet;
};

