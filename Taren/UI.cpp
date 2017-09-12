#pragma once

#include <SDL.h>
#include <algorithm>
#include "UI.h"
#include "Application.h"

deque<UIObject*> UIManager::uiobjects;

UIObject::UIObject(Vector2 pos, Vector2 size) : UIObject() {
	position = pos;
	this->size = size;
}

UIObject::UIObject(Vector2 pos, Vector2 anchor, Vector2 size) : UIObject(pos, size) {
	SetAnchor(anchor);
}

UIObject::UIObject(Vector2 pos, Vector2 anchor, Vector2 origin, Vector2 size) : UIObject(pos, anchor, size) {
	SetOrigin(origin);
}

UIObject::UIObject() {
	UIManager::RegisterUIObject(this);
}

UIObject::~UIObject() {
	UIManager::UnregisterUIObject(this);
}

void UIManager::RenderUI() {
	SDL_SetRenderDrawColor(Application::gRenderer, 0, 0, 255, 255);

	for (UIObject* o : uiobjects) {
		o->Render();
	}
}

void UIManager::ResortUIObjects() {
	std::sort(uiobjects.begin(), uiobjects.end(), [](UIObject*& f, UIObject*& s) { return f->GetZIndex() < s->GetZIndex(); } );
}

void UIManager::RegisterUIObject(UIObject* o) {
	deque<UIObject*>::iterator it;

	if (uiobjects.size() > 0) {
		// Insert into the right place that way we don't have to sort.
		for (it = uiobjects.begin(); it != uiobjects.end(); it++) {
			if (o->GetZIndex() < (*it)->GetZIndex()) break; // Only a < and not a <= to avoid inefficiency when inserting at front 
		}
	} else {
		it = uiobjects.begin();
	}

	uiobjects.insert(it, o);
}

void UIManager::UnregisterUIObject(UIObject* o) {
	deque<UIObject*>::iterator it;

	for (it = uiobjects.begin(); it != uiobjects.end(); it++) {
		if (o == (*it)) {
			uiobjects.erase(it);
			return;
		}
	}
}

int UIObject::GetZIndex() {
	return zindex;
}

void UIObject::SetAnchor(Vector2 a) {
	anchor = a;
	calculatedAnchor = Vector2(floorf(Application::SCREEN_WIDTH * anchor.x), floorf(Application::SCREEN_HEIGHT * anchor.y));
}

void UIObject::SetOrigin(Vector2 o) {
	origin = o;
	calculatedOrigin = Vector2(floorf(origin.x * size.x), floorf(origin.y * size.y));
}

void UIObject::SetZIndex(int z) {
	zindex = z;
	UIManager::ResortUIObjects();
}

void UIObject::Tick() {

}

void UIObject::Render() {
	SDL_Rect r = {calculatedAnchor.x + position.x - calculatedOrigin.x, calculatedAnchor.y + position.y - calculatedOrigin.y, size.x, size.y};
	SDL_RenderDrawRect(Application::gRenderer, &r);
}

void UIObject::SetEnabled(bool f) {
	enabled = f;
}

bool UIObject::GetEnabled() {
	return enabled;
}