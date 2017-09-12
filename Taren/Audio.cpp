#include "Audio.h"

Mix_Music* Audio::currentMusic = NULL;

void Audio::PlayMusic(Mix_Music* music, int loops) {
	if (currentMusic != NULL) {
		Mix_PauseMusic();
	} 

	Mix_PlayMusic(music, -1);
	currentMusic = music;
}

void Audio::PauseMusic() {
	Mix_PauseMusic();
}

void Audio::ResumeMusic() {
	Mix_ResumeMusic();
}

void Audio::HaltMusic() {
	Mix_HaltMusic();
	currentMusic = NULL;
}

bool Audio::GetMusicPaused() {
	return Mix_PausedMusic();
}

void Audio::SetAllVolume(int v) {
	Mix_Volume(-1, v);
}

void Audio::SetMusicVolume(int v) {
	Mix_VolumeMusic(v);
}

void Audio::PlaySound(Mix_Chunk* sound, int channel, int loops) {
	Mix_PlayChannel(channel, sound, loops);
}

void Audio::SetChunkVolume(Mix_Chunk* chunk, int volume) {
	Mix_VolumeChunk(chunk, volume);
}