#pragma once
#include <set>

class BaseEventData {
	public:
	const char* name;

	BaseEventData(const char* name);
	~BaseEventData();
};

class RandomEventData : public BaseEventData {
	public:
	const char* message;
	const int number;

	RandomEventData(const char* name, const char* message, const int number);
	~RandomEventData();
};

class EventHandler {
	public:
	std::set<const char*> events;

	EventHandler();
	~EventHandler();

	virtual void GameEventListener(const char* name, BaseEventData* data);
};
