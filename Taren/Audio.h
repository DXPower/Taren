#pragma once
#include <SDL_mixer.h>

class Audio {
	public:
	static Mix_Music* currentMusic;

	static bool GetMusicPaused();
	static void PlayMusic(Mix_Music* music, int loops);
	static void PlaySound(Mix_Chunk* soumd, int channel, int loops);
	static void PauseMusic();
	static void ResumeMusic();
	static void HaltMusic();
	static void SetAllVolume(int v);
	static void SetMusicVolume(int v);
	static void SetChunkVolume(Mix_Chunk* chunk, int volume);
};

