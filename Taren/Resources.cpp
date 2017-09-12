#include <sstream>
#include <SDL_image.h>
#include <utility>
#include <SDL_mixer.h>
#include "Application.h"
#include "Resources.h"
#include "Game.h"

unordered_map<const char*, SDL_Texture*> Resources::textures;
unordered_map<const char*, GameObject*> Resources::prefabs;
unordered_map<const char*, Mix_Music*> Resources::music;
unordered_map<const char*, Mix_Chunk*> Resources::sounds;

bool Resources::LoadBMP(const char* fileName, SDL_Surface*& surface) {
	bool success = true;
	ostringstream path;
	path << "Resources/Images/" << fileName;

	SDL_Surface* loaded = SDL_LoadBMP(path.str().c_str());

	if (surface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.str(), SDL_GetError());
		success = false;
	} else {
		/*SDL_Surface* optimized = SDL_ConvertSurface(loaded, Application::gScreenSurface->format, 0);

		if (optimized == NULL) {
			printf("Unable to convert %s to optimal format. SDL Error: %s\n", path.str().c_str(), SDL_GetError());
		} else {
			SDL_FreeSurface(loaded);
			surface = optimized;
		}*/
	}

	return success;
}

bool Resources::LoadImage(const char* fileName, SDL_Surface*& surface, bool optimize) {
	bool success = true;
	ostringstream path;
	path << "Resources/Images/" << fileName;

	SDL_Surface* loaded = IMG_Load(path.str().c_str());

	if (loaded == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.str(), IMG_GetError());
		success = false;
	} else if (optimize) {
		//	//SDL_Surface* optimized = SDL_ConvertSurface(loaded, Application::gScreenSurface->format, 0);

		//	if (optimized == NULL) {
		//		printf("Unable to convert %s to optimal format. SDL Error: %s\n", path.str().c_str(), SDL_GetError());
		//	} else {
		//		SDL_FreeSurface(loaded);
		//		surface = optimized;
		//	}
		//}
	} else {
		surface = loaded;
	}

	return success;
}

bool Resources::LoadTexture(const char* fileName, SDL_Texture*& texture) {
	bool success = true;

	SDL_Surface* surface = NULL;

	if (LoadImage(fileName, surface, false)) {
		SDL_Texture* loaded = SDL_CreateTextureFromSurface(Application::gRenderer, surface);

		if (loaded == NULL) {
			Application::Error("Unable to create texture from %s. Error: %s\n", fileName, SDL_GetError());
		}

		SDL_FreeSurface(surface);
		texture = loaded;
	} else {
		success = false;
	}

	return success;
}

bool Resources::LoadMusic(const char* fileName, Mix_Music*& music) {
	bool success = true;
	ostringstream s;
	s << "Resources/Music/" << fileName;

	music = Mix_LoadMUS(s.str().c_str());

	if (music == NULL) {
		Application::Error("Unable to load music %s. Error: %s\n", s, Mix_GetError());
		success = false;
	}

	return success;
}

void Resources::SaveMusic(const char* name, Mix_Music* music) {
	Resources::music[name] = music;
}

Mix_Music* Resources::LoadAndSaveMusic(const char* fileName, const char* saveName) {
	Mix_Music* music = NULL;

	if (LoadMusic(fileName, music) && music != NULL) {
		SaveMusic(saveName, music);
	}

	return music;
}

bool Resources::LoadWAV(const char* fileName, Mix_Chunk*& chunk) {
	bool success = true;
	ostringstream s;
	s << "Resources/Sounds/" << fileName;

	chunk = Mix_LoadWAV(s.str().c_str());
	if (chunk == NULL) {
		Application::Error("Could not load WAV %s. Error: %s\n", s, Mix_GetError());
		success = false;
	}

	return success;
}

void Resources::SaveSound(const char* name, Mix_Chunk* chunk) {
	sounds[name] = chunk;
}

Mix_Chunk* Resources::LoadAndSaveSound(const char* fileName, const char* saveName) {
	Mix_Chunk* chunk = NULL;

	if (LoadWAV(fileName, chunk) && chunk != NULL) {
		SaveSound(saveName, chunk);
	}

	return chunk;
}

Mix_Chunk* Resources::GetSound(const char* name) {
	return sounds[name];
}

Mix_Music* Resources::GetMusic(const char* name) {
	return music[name];
}

void Resources::SaveTexture(const char* name, SDL_Texture* texture) {
	//std::pair<const char*, SDL_Texture*> pair = make_pair(name, texture);
	textures[name] = texture;
//	textures->emplace("link", texture);
}

SDL_Texture* Resources::LoadAndSaveTexture(const char* fileName, const char* saveName) {
	SDL_Texture* texture = NULL;

	if (LoadTexture(fileName, texture) && texture != NULL) {
		SaveTexture(saveName, texture);
	}

	return texture;
}

SDL_Texture* Resources::GetTexture(const char* name) {
	return textures.at(name);
}

GameObject* Resources::CreatePrefab(const char* name, GameObject* g) {
	prefabs[name] = g;
	return g;
}

GameObject* Resources::LoadPrefab(const char* name) {
	return prefabs.at(name);
}

void Resources::FreeAllResources() {
	for (pair<const char*, SDL_Texture*> p : textures) {
		SDL_DestroyTexture(p.second);
	}

	for (pair<const char*, Mix_Music*> p : music) {
		Mix_FreeMusic(p.second);
	}

	for (pair<const char*, Mix_Chunk*> p : sounds) {
		Mix_FreeChunk(p.second);
	}
}