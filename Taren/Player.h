#pragma once
#include "GameObject.h"
#include "Input.h"
#include "EventHandler.h"

class Spritesheet;

class Player : public GameObject, public Input, public EventHandler {
	public:
	Player(Vector2);
	~Player();

	void Tick() override;
	void CollisionEnter(Collider* c, SDL_Rect intersection) override;
	void KeyboardEvent(const SDL_Scancode) override;
	void KeyDownEvent(const SDL_Scancode) override;
	//void GameEventListener(const char* name, BaseEventData* data) override;

	private:
	int count;
	int textureCount = 0;

	float speed = 6;

	unsigned char dBits = 0;
	unsigned int directionsBlocked = 0;

	Vector2 direction = Vector2(0, 0);
	Vector2 lastDirection = Vector2(0, 0);

	Spritesheet* spritesheet;
};

