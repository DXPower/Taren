#pragma once

#include <SDL.h>
#include "GameObject.h"
#include "Game.h"
#include "Application.h"
#include "Renderer.h"
#include "Collision.h"

GameObject::GameObject() {
	Game::RegisterGameObject(this);
}

GameObject::GameObject(Vector2 position) : GameObject() {
	this->position = position;
}

GameObject::GameObject(Vector2 position, SDL_Texture* texture) : position(position) {
	Game::RegisterGameObject(this);
	renderer = new Renderer(this, texture);
}

GameObject::GameObject(SDL_Texture* texture) {
	Game::RegisterGameObject(this);
	renderer = new Renderer(this, texture);
}

GameObject::GameObject(const GameObject& go, Vector2 position) : position(position), renderer(new Renderer(this, *go.renderer)) {
	Game::RegisterGameObject(this);
}

GameObject::GameObject(Renderer* r, Collider* c, Vector2 position) : renderer(r), collider(c), position(position) {
	Game::RegisterGameObject(this);
}

GameObject::~GameObject() {
	delete renderer;
	delete collider;

	Game::UnregisterGameObject(this);
}

/// <deprecated></deprecated>
GameObject* GameObject::Clone() {
	//return new GameObject(*this, position);
	return new GameObject();
}

void GameObject::SetSize(Vector2 size) {
	this->size = size;
	collider->GameObjectSizeChanged(size);
	renderer->GameObjectSizeChanged(size);
}

Vector2 GameObject::GetSize() {
	return size;
}

void GameObject::Tick() {
	if (velocity != Vector2::zero) {
		UpdatePosition(position.x + velocity.x, position.y + velocity.y);
	}
}

void GameObject::Translate(Vector2* v) {
	UpdatePosition(position.x + v->x, position.y + v->y);
}

void GameObject::SetEnabled(bool f) {
	enabled = f;
}

void GameObject::Destroy() {
	deleted = true;
	Game::UnregisterGameObject(this);
}

void GameObject::SetPosition(Vector2 pos) {
	lastPosition = position;
	position = pos;

	needsCollisionCheck = true;
}

void GameObject::UpdatePosition(float x, float y) {
	lastPosition = position;
	position.x = x;
	position.y = y;

	needsCollisionCheck = true;
}

const Vector2* GameObject::GetLastPosition() const {
	return &lastPosition;
}

Vector2* GameObject::Position() {
	return &position;
}

bool GameObject::IsEnabled() {
	return enabled;
}

void GameObject::CollisionEnter(Collider* c, SDL_Rect intersection) {

}

void GameObject::SetVelocity(Vector2* v) {
	velocity = *v;
}

const Vector2* GameObject::GetVelocity() const {
	return &velocity;
}