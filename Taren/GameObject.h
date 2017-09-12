#pragma once
#include <SDL.h>
#include <string>
#include "Vector2.h"

class Renderer;
class Collider;

using namespace std;

class GameObject {
	public:
	Renderer* renderer;
	Collider* collider;

	bool deleted = false;
	bool needsCollisionCheck = false;

	string name = "";

	GameObject();
	GameObject(const GameObject& gameObject, Vector2 position);
	GameObject(Vector2 position);
	GameObject(Vector2 position, SDL_Texture* texture);
	GameObject(SDL_Texture* texture);
	GameObject(Renderer* r, Collider* c, Vector2 position);
	~GameObject();

	Vector2* Position();/// <summary>Gets the position</summary>
	const Vector2* GetVelocity() const;
	const Vector2* GetLastPosition() const;
	Vector2 GetSize();
	bool IsEnabled();
	void SetPosition(Vector2 pos); /// <summary>Replaces existing position with completely new pointer.</summary>
	void UpdatePosition(float x, float y); /// <summary>Use to update position variables manually, mostly to avoid Vector2 constructor</summary>
	void SetEnabled(bool);
	void Translate(Vector2*);
	void SetSize(Vector2);
	void SetVelocity(Vector2* v);
	void Destroy();
	//void UpdateRect();
	//void UpdateRectPos();
	virtual void Tick();
	//virtual void SetTexture(SDL_Texture*, bool);
	//virtual void SetTexture(SDL_Texture*, Vector2);

	virtual void CollisionEnter(Collider* c, SDL_Rect intersection);
	virtual GameObject* Clone();

	private:
	bool enabled = false;

	Vector2 position = Vector2(0, 0);
	Vector2 lastPosition = Vector2(0, 0);
	Vector2 size = Vector2(50, 50);
	Vector2 velocity = Vector2(0, 0);
};