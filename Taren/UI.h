#pragma once
#include <deque>
#include "Vector2.h"

using namespace std;

class UIObject {
	public:

	UIObject();
	UIObject(Vector2 pos, Vector2 size);
	UIObject(Vector2 pos, Vector2 anchor, Vector2 size);
	UIObject(Vector2 pos, Vector2 anchor, Vector2 origin, Vector2 size);
	~UIObject();

	inline int GetZIndex();
	bool GetEnabled();
	void SetEnabled(bool f);
	void SetZIndex(int z);
	void SetAnchor(Vector2 a);
	void SetOrigin(Vector2 o);

	virtual void Tick();
	virtual void Render();

	private:
	Vector2 position = Vector2::zero;
	Vector2 anchor = Vector2::zero;
	Vector2 calculatedAnchor = Vector2::zero;
	Vector2 origin = Vector2::zero;
	Vector2 calculatedOrigin = Vector2::zero;
	Vector2 size = Vector2::zero;

	int zindex = 0;

	bool enabled = false;
};

class UIManager {
	public:
	static deque<UIObject*> uiobjects;

	static void RenderUI();
	static void ResortUIObjects();
	static void RegisterUIObject(UIObject* o);
	static void UnregisterUIObject(UIObject* o);
};

