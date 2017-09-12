#pragma once
#include <string>
#include <SDL.h>
#include <unordered_map>
#include <SDL_mixer.h>

using namespace std;

class GameObject;

class Resources {
	public:

	static SDL_Texture* GetTexture(const char*);
	static SDL_Texture* LoadAndSaveTexture(const char*, const char*);
	static GameObject* CreatePrefab(const char* name, GameObject* g);
	static GameObject* LoadPrefab(const char* name);
	static Mix_Music* LoadAndSaveMusic(const char*, const char*);
	static Mix_Music* GetMusic(const char*);
	static Mix_Chunk* LoadAndSaveSound(const char*, const char*);
	static Mix_Chunk* GetSound(const char*);
	static bool LoadBMP(const char*, SDL_Surface*&);
	static bool LoadImage(const char*, SDL_Surface*&, bool);
	static bool LoadTexture(const char*, SDL_Texture*&);
	static bool LoadMusic(const char*, Mix_Music*&);
	static bool LoadWAV(const char*, Mix_Chunk*&);
	static void SaveSound(const char*, Mix_Chunk*);
	static void SaveTexture(const char*, SDL_Texture*);
	static void SaveMusic(const char*, Mix_Music*);
	static void FreeAllResources();

	private:
	static unordered_map<const char*, SDL_Texture*> textures;
	static unordered_map<const char*, GameObject*> prefabs;
	static unordered_map<const char*, Mix_Music*> music;
	static unordered_map<const char*, Mix_Chunk*> sounds;
};

