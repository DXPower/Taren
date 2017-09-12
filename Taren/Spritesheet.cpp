#pragma once
#include <math.h>
#include "Spritesheet.h"
#include "GameObject.h"
#include "Application.h"
#include "Game.h"

Spritesheet::Spritesheet(SDL_Texture* sheet) : sheet(sheet) {
	int w, h;
	SDL_QueryTexture(sheet, NULL, NULL, &w, &h);
	width = w;
	height = h;
}

Spritesheet::~Spritesheet() {
	for (pair<int, SpritesheetAnimation*> p : animations) {
		delete p.second;
	}
}

SpritesheetAnimation::SpritesheetAnimation(int x, int y, int boxW, int boxH, int timesX, int timesY, int speed) : x(x), y(y), boxW(boxW), boxH(boxH), nX(timesX), nY(timesY), speed(speed) {

}

SpritesheetRenderer::SpritesheetRenderer(GameObject* go) : Renderer(go) {

}

SDL_Texture* Spritesheet::GetTexture() {
	return sheet;
}

SpritesheetAnimation* Spritesheet::GetAnimation(int key) {
	return animations[key];
}

SpritesheetAnimation* Spritesheet::CurrentAnimation() {
	return animation;
}

bool Spritesheet::AnimationExists(int key) {
	return animations.find(key) != animations.end();
}

void Spritesheet::SetAnimation(int key) {
	SetAnimation(GetAnimation(key));
}

void Spritesheet::SetAnimation(SpritesheetAnimation* animation) {
	this->animation = animation;
	box = animation->GetCurrent();
}

void Spritesheet::RegisterAnimation(int key, SpritesheetAnimation* animation) {
	animations[key] = animation;
}

void Spritesheet::Next() {
	box = animation->Next();
}

Rect* Spritesheet::GetCurrent() {
	return &box;
}

Rect* Spritesheet::SetFrame(int frame) {
	box = animation->SetFrame(frame);
	return &box;
}

Rect SpritesheetAnimation::GetFrame(int frame) {
	if (frame >= (nX * nY)) frame = 0;

	int y = (int) floorf(frame / (nX));
	int x = frame - (y * (nX));

	return Rect(currentX * boxW + x, currentY * boxH + y, boxW, boxH);
}

Rect SpritesheetAnimation::GetCurrent() {
	return Rect(currentX * boxW + x, currentY * boxH + y, boxW, boxH);
}

Rect SpritesheetAnimation::Next() {
	if (++currentX >= nX) {
		currentX = 0;

		if (++currentY >= nY) {
			currentY = 0;
		}
	}

	return GetCurrent();
}

Rect SpritesheetAnimation::SetFrame(int frame) {
	if (frame >= (nX * nY)) frame = frame % (nY * nX);

 	int y = (int) floorf(frame / (nX));
	int x = frame - (y * (nX));

	currentX = x;
	currentY = y;

	return Rect(currentX * boxW + x, currentY * boxH + y, boxW, boxH);
}

Spritesheet* SpritesheetRenderer::SetSpritesheet(SDL_Texture* texture) {
	spritesheet = Spritesheet(texture);
	return &spritesheet;
}

void SpritesheetRenderer::Render() {
	SDL_Rect clip = spritesheet.GetCurrent()->ToSDL();
	Vector2* pos = gameobject->Position();
	Vector2 size = gameobject->GetSize();
	SDL_Rect render = {(int) pos->x, (int) pos->y, size.x, size.y};
	
	Game::RenderToScreen(Application::gRenderer, spritesheet.GetTexture(), &clip, &render);

	if (isPlaying && spritesheet.GetSpeed() != 0) {
		if (++count > spritesheet.GetSpeed()) {
			count = 0;
			spritesheet.Next();
		}
	}

	//SDL_RenderDrawRect(Application::gRenderer, &render);
}

void SpritesheetRenderer::Pause() {
	isPlaying = false;
}

void SpritesheetRenderer::Resume() {
	isPlaying = true;
}

Vector2 SpritesheetRenderer::GetTextureSize() {
	Rect r = spritesheet.CurrentAnimation()->GetCurrent();

	return Vector2(r.w, r.h);
}