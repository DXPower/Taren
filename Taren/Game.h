#pragma once

#include <SDL.h>
#include <list>
#include <set>
#include <unordered_map>
#include <iostream>

using namespace std;

class Player;
class GameObject;
class Collider;
class Renderer;
class Camera;
class Rect;
class Vector2;
class EventHandler;
class BaseEventData;

class Game {
	public:
	static bool quit;

	static enum MOVEMENT_DIRECTION {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT
	};


	static set<GameObject*> objects;
	static set<Renderer*> renderers;
	static set<Collider*> colliders;
	static set<GameObject*> objectsToDelete;
	static unordered_map<const char*, set<EventHandler*>> gameEvents;

	static SDL_Texture* textures[4];
	static SDL_Texture* currentTexture;

	static GameObject* gameObject;
	static GameObject* player;

	static Camera* camera;

	static int sceneW, sceneH, collisionsChecksPerSec;

	static void Init();
	static void InitLoadSound();
	static void RegisterRenderer(Renderer* r);
	static void RegisterGameObject(GameObject* g);
	static void UnregisterRenderer(Renderer* r);
	static void UnregisterGameObject(GameObject* g);
	static void RenderToScreen(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* crop, const SDL_Rect* draw);
	static void RegisterGameEventListener(const char* name, EventHandler* eh);
	static void UnregisterGameEventListener(const char* name, EventHandler* eh);
	static void UnregisterGameEventListener(const char* name, EventHandler* eh, bool eraseFromEvents);
	static void  InvokeGameEvent(const char* name, BaseEventData& data);
	static inline void GameLoop();

	private:
	static void InitLoadImages();
	static void Load();
	static inline void Tick();
};






