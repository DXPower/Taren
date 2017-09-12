#pragma once
#include <unordered_map>
#include "Renderer.h"

class Rect;
class Vector2;

using namespace std;

class SpritesheetAnimation {
	public:
	///<summary>How fast the animation plays. Lower is faster.</summary>
	int speed;

	SpritesheetAnimation() {};
	SpritesheetAnimation(int x, int y, int boxW, int boxH, int nX, int nY, int speed);
	~SpritesheetAnimation() {};

	Rect GetFrame(int frame);
	Rect SetFrame(int frame);
	Rect GetCurrent();
	Rect Next();

	private:
	int x, y, boxW, boxH, nX, nY, currentX = 0, currentY = 0;	
};

class Spritesheet {
	public:
	Spritesheet() {};
	Spritesheet(SDL_Texture*);
	~Spritesheet();
	
	static Spritesheet SpritesheetFactory(SDL_Texture* texture) {
		return Spritesheet(texture);
	}

	SDL_Texture* GetTexture();
	Rect* GetCurrent();
	Rect* SetFrame(int frame);
	SpritesheetAnimation* GetAnimation(int key);
	SpritesheetAnimation* CurrentAnimation();
	int Width();
	int Height();
	bool AnimationExists(int key);
	void SetAnimation(int key);
	void SetAnimation(SpritesheetAnimation* animation);	
	void RegisterAnimation(int key, SpritesheetAnimation* animation);
	void Next();

	inline int GetSpeed() {
		return animation->speed;
	}

	private:
	SDL_Texture* sheet;
	
	SpritesheetAnimation* animation;

	unordered_map<int, SpritesheetAnimation*> animations;

	Rect box;

	int width;
	int height;
};

class SpritesheetRenderer : public Renderer {
	public:
	SpritesheetRenderer(GameObject* go);
	~SpritesheetRenderer();

	Spritesheet* SetSpritesheet(SDL_Texture*);
	void Pause();
	void Resume();


	Vector2 GetTextureSize() override;
	void Render() override;

	private:
	Spritesheet spritesheet;

	int count = 0;

	bool isPlaying = true;
};