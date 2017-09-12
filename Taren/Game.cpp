#pragma once

#include <SDL.h>
#include <string>
#include <array>
#include "Game.h"
#include "Camera.h"
#include "Renderer.h"
#include "Collision.h"
#include "Application.h"
#include "Resources.h"
#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Vector2.h"
#include "Helpers.h"
#include "EventHandler.h"
#include "Audio.h"
#include "UI.h"


using namespace std;

bool Game::quit = false;

int Game::sceneW = Application::SCREEN_WIDTH;
int Game::sceneH = Application::SCREEN_HEIGHT;
int Game::collisionsChecksPerSec = 0;

SDL_Texture* Game::textures[4];
SDL_Texture* Game::currentTexture = NULL;

set<GameObject*> Game::objects;
set<GameObject*> Game::objectsToDelete;
set<Renderer*> Game::renderers;
set<Collider*> Game::colliders;
unordered_map<const char*, set<EventHandler*>> Game::gameEvents;

GameObject* Game::gameObject;
GameObject* Game::player;

Camera* Game::camera;

void Game::Init() {
	InitLoadImages();
	InitLoadSound();
	Load();
	GameLoop();
}

void Game::Load() {
	Collision::SetupBuckets(Application::SCREEN_WIDTH, Application::SCREEN_HEIGHT, 100, 100);

	player = new Player(Vector2(50, 50));
	gameObject = new Wall(Vector2(225, 225), Resources::GetTexture("window"));
	new UIObject(Vector2(-50, -50), Vector2(1, 1), Vector2(1, 1), Vector2(75, 75));

	camera = new Camera();
	camera->SetTargetType(CameraTargetType::CAMERA_FOLLOW);
	camera->SetFollowTarget(player);
}

void Game::InitLoadImages() {
	Resources::LoadAndSaveTexture("penguin.png", "player_spritesheet");
	Resources::LoadAndSaveTexture("window.png", "window");
	Resources::LoadAndSaveTexture("weapons.png", "bullet_spritesheet");
}

void Game::InitLoadSound() {
	Resources::LoadAndSaveMusic("anotherme.flac", "epica");
	Resources::LoadAndSaveMusic("pharaoh.flac", "sx");
	Resources::LoadAndSaveSound("high.wav", "high");
	Resources::LoadAndSaveSound("low.wav", "low");
	Audio::SetChunkVolume(Resources::LoadAndSaveSound("medium.wav", "medium"), MIX_MAX_VOLUME / 5);
	Resources::LoadAndSaveSound("scrach.wav", "scratch");
	Audio::SetMusicVolume(MIX_MAX_VOLUME / 20);

}

void Game::Tick() {
	SDL_SetRenderDrawColor(Application::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(Application::gRenderer);

	set<GameObject*>::iterator git;

	collisionsChecksPerSec = 0;

	for (git = objects.begin(); git != objects.end(); git++) {
		if ((*git)->needsCollisionCheck) {
			(*git)->collider->GetNearbyBoxes();
		}
	}

	SDL_SetRenderDrawColor(Application::gRenderer, 0x00, 0x00, 0x00, 0xFF);

	for (git = objects.begin(); git != objects.end(); git++) {
		if (!(*git)->deleted && (*git)->IsEnabled()) {
			(*git)->Tick();
		}
	}

	set<GameObject*>::iterator dit;

	for (dit = objectsToDelete.begin(); dit != objectsToDelete.end(); dit++) {
		objects.erase(*dit);
		delete(*dit);
	}

	objectsToDelete.clear();

	set<Renderer*>::iterator rit;

	for (rit = renderers.begin(); rit != renderers.end(); rit++) {
		if ((*rit)->GetEnabled()) {
			(*rit)->Render();
		}
	}

	UIManager::RenderUI();

	//for (pair<int, Bucket*> p : Collision::buckets) {
	//	if (p.second->objects.size() == 0) {
	//		SDL_SetRenderDrawColor(Application::gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	//	} else {
	//		SDL_SetRenderDrawColor(Application::gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	//	}

	//	Bucket* b = p.second;
	//	Rect rect = Rect(b->sceneX, b->sceneY, Collision::cellSizeX, Collision::cellSizeY);

	//	SDL_RenderDrawRect(Application::gRenderer, &rect.ToSDL());
	//}

	SDL_RenderPresent(Application::gRenderer);
};

void Game::GameLoop() {
	while (!quit) {
		int start = SDL_GetTicks();
		Input::PollEvents();
		Input::ScanKeyboard();
		Tick();
		int time = SDL_GetTicks() - start;
		if (time < 0) continue;

		int sleepTime = 16 - time; // 60fps baby
	}
};

void Game::RegisterRenderer(Renderer* r) {
	renderers.insert(r);
}

void Game::RegisterGameObject(GameObject* g) {
	objects.insert(g);
}

void Game::UnregisterRenderer(Renderer* r) {
	renderers.erase(r);
}

void Game::UnregisterGameObject(GameObject* g) {
	objectsToDelete.insert(g);
}

void Game::RenderToScreen(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* crop, const SDL_Rect* draw) {
	const Vector2 pos = camera->WorldToScreenPos(Vector2(draw->x, draw->y));
	SDL_Rect cameraShifted = {pos.x, pos.y, draw->w, draw->h};

	SDL_RenderCopy(renderer, texture, crop, &cameraShifted);
}

void Game::RegisterGameEventListener(const char* name, EventHandler* eh) {
	eh->events.insert(name);
	gameEvents[name].insert(eh);
}

void Game::UnregisterGameEventListener(const char* name, EventHandler* eh) {
	if (gameEvents.find(name) != gameEvents.end()) {
		eh->events.erase(name);
		gameEvents[name].erase(eh);
	}
}

void Game::UnregisterGameEventListener(const char* name, EventHandler* eh, bool eraseFromEvents) {
	if (gameEvents.find(name) != gameEvents.end()) {
		if (eraseFromEvents) {
			eh->events.erase(name);
		}

		gameEvents[name].erase(eh);
	}
}

void Game::InvokeGameEvent(const char* name, BaseEventData& data) {
	if (gameEvents.find(name) != gameEvents.end()) {
		for (EventHandler* o : gameEvents[name]) {
			o->GameEventListener(name, &data);
		}
	}
}