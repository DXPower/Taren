#pragma once
#include "Player.h"
#include "GameObject.h"
#include "Spritesheet.h"
#include "Application.h"
#include "Resources.h"
#include "Helpers.h"
#include "Input.h"
#include "Bullet.h"
#include "Collision.h"
#include "Game.h"
#include "EventHandler.h"
#include "Audio.h"
#include <iostream>

Player::Player(Vector2 position) : GameObject(position), Input() {
	SpritesheetRenderer* renderer = new SpritesheetRenderer(this);
	this->renderer = renderer;
	this->collider = new SquareCollider(this);

	Spritesheet* spritesheet = renderer->SetSpritesheet(Resources::GetTexture("player_spritesheet"));

	spritesheet->RegisterAnimation(1, new SpritesheetAnimation(0, 168, 41, 42, 8, 1, 10)); // Up
	spritesheet->RegisterAnimation(2, new SpritesheetAnimation(0, 0, 41, 42, 8, 1, 10)); // Down
	spritesheet->RegisterAnimation(4, new SpritesheetAnimation(0, 252, 41, 42, 8, 1, 10)); // Left
	spritesheet->RegisterAnimation(8, new SpritesheetAnimation(0, 84, 41, 42, 8, 1, 10)); // Right
	spritesheet->RegisterAnimation(9, new SpritesheetAnimation(0, 126, 41, 42, 8, 1, 10)); // Up-Right
	spritesheet->RegisterAnimation(10, new SpritesheetAnimation(0, 42, 41, 42, 8, 1, 10)); // Down-Right
	spritesheet->RegisterAnimation(5, new SpritesheetAnimation(0, 210, 41, 42, 8, 1, 10)); // Up-Left
	spritesheet->RegisterAnimation(6, new SpritesheetAnimation(0, 294, 41, 42, 8, 1, 10)); // Down-Left
	
	spritesheet->SetAnimation(2);
	this->spritesheet = spritesheet;

	Input::RegisterKeyboardListener(SDL_SCANCODE_W, this);
	Input::RegisterKeyboardListener(SDL_SCANCODE_S, this);
	Input::RegisterKeyboardListener(SDL_SCANCODE_A, this);
	Input::RegisterKeyboardListener(SDL_SCANCODE_D, this);
	Input::RegisterKeyDownListener(SDL_SCANCODE_SPACE, this);

	SetSize(renderer->GetTextureSize());
	name = "Player";

	SetEnabled(true);
	renderer->SetEnabled(true);

	//SetActive(true);
	//SetCollisionEnabled(true);
	
	//boundingRect = Rect(position.x, position.y, 41, 42);
};


Player::~Player() {}

void Player::Tick() {
	GameObject::Tick();
	direction.x = 0;
	direction.y = 0;

	if (dBits != 0 && dBits != 15) {
		dBits = dBits & (~directionsBlocked); // Sets any bits with direction blocked to zero if they are one. ex. 1010 & ~(0110) = 1010 & 1001 = 1000

		if ((dBits & 1) == 1) {
			direction.y -= 1;
		}

		if ((dBits & 2) == 2) {
			direction.y += 1;
		}

		if ((dBits & 4) == 4) {
			direction.x -= 1;
		}

		if ((dBits & 8) == 8) {
			direction.x += 1;
		}
	}
	
	if (direction != Vector2::zero) {
		if (spritesheet->AnimationExists(dBits)) {
			spritesheet->SetAnimation(dBits);
		}

		Vector2 v = direction;
		lastDirection = direction;

		if (abs(v.x + v.y) == 1) {
			v = v * speed;
		} else {
			v.Normalize();
			v = v * speed;
		}

		SetVelocity(&v);
	} else {
		SetVelocity(&Vector2::zero);
	}

	dBits = 0;
	directionsBlocked = 0;
}

void Player::KeyboardEvent(const SDL_Scancode key) {
	switch (key) {
		case SDL_SCANCODE_W:
			dBits |= 1;
			break;
		case SDL_SCANCODE_S:
			dBits |= 2;
			break;
		case SDL_SCANCODE_A:
			dBits |= 4;
			break;
		case SDL_SCANCODE_D:
			dBits |= 8;
			break;
	}
}

void Player::KeyDownEvent(const SDL_Scancode key) {
	Bullet* bullet = new Bullet(*Position());
	bullet->ChangeTexture(textureCount++);
	bullet->SetDirection(lastDirection);
	bullet->SetEnabled(true);

	//Audio::PlaySound(Resources::GetSound("medium"), -1, 1);
}

void Player::CollisionEnter(Collider* c, SDL_Rect intersection) {
	if (c->gameobject->name == "Wall") {
		Vector2* pos = Position();
		Vector2 size = GetSize();
		Vector2 middle = Vector2(pos->x + size.x / 2, pos->y + size.y / 2);

		if (intersection.w > intersection.h) {
			if (intersection.y >= middle.y || intersection.y + intersection.h >= middle.y) { // wall is below us
				directionsBlocked |= 2;
			} else { // wall is above us
				directionsBlocked |= 1;
			}
		} else if (intersection.w < intersection.h) {
			if (intersection.x >= middle.x || intersection.x + intersection.w >= middle.x) { // wall is to the right
				directionsBlocked |= 8;
			} else { // wall is to the left
				directionsBlocked |= 4;
			}
		} else {// If they're equal then they hit a corner exactly and shouldn't be blocked, just move them to the past position
			SetPosition(*GetLastPosition());
		}
	}
}
/*
void Player::GameEventListener(const char* name, BaseEventData* e) {
	if (name == "random") {
		if (RandomEventData* data = static_cast<RandomEventData*>(e)) {
			cout << name << " made message: " << data->message << " with count of " << data->number;
		}
	}
}*/