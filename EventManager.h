#pragma once
#include "Event.h"
#include "Player.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include<ostream>

class EventManager
{
private:
	std::string activePath;
	std::string allPath;
	
	std::unordered_map<int, Event> activeEvents;
	std::unordered_map<int, Event> allHistoryEvents;

	static int nextId;

	void initFromFiles();
	void loadAllEventsMaxId();
	void loadActiveEvents();
	void reconstructPastFromAll();
	

public:
	EventManager(const std::string& activeFile = "active.txt",
		const std::string& allFile = "all.txt");

	int addEvent(SportType sport, SkillLevel level,
		const std::chrono::system_clock::time_point& when,
		int duration, int maxPlayers,
		const std::string& fieldName);

	bool removeEvent(int id, Player& player);
	Event* getActiveEvent(int id);
	void printActive(std::ostream& os = std::cout) const;
	void printPast(std::ostream& os = std::cout) const;
	void printAll(std::ostream& os = std::cout) const;
	void onExitSave() const;

};

