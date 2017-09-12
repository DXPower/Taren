#pragma once
#include "EventHandler.h"
#include "Game.h"

EventHandler::EventHandler() {};

EventHandler::~EventHandler() {
	for (const char* name : events) {
		Game::UnregisterGameEventListener(name, this, false);
	}
};

void EventHandler::GameEventListener(const char* name, BaseEventData* data) {};

BaseEventData::BaseEventData(const char* name) : name(name) {};
BaseEventData::~BaseEventData() {};

RandomEventData::RandomEventData(const char* name, const char* message, const int number) : BaseEventData(name), message(message), number(number) {};
RandomEventData::~RandomEventData() {};