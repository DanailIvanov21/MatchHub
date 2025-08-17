#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>

enum class SportType {
	Football = 0,
	Basketball = 1,
	Tennis = 2
};

enum class SkillLevel {
	Beginner = 0,
	Intermediate = 1,
	Advanced = 2
};


//helpers
std::string sportToString(SportType s);
std::string skillToString(SkillLevel l);

bool parseSport(const std::string& s, SportType& out);
bool parseSkill(const std::string& s, SkillLevel& out);


class Event
{
private:
	SportType sport;
	SkillLevel level;
	std::tm when;
	int duration;
	int maxPlayers;
	std::string fieldName;
public:
	Event() = default;
	Event(SportType sport, SkillLevel level, 
		const std::tm& when,
		int duration, int maxPlayers, const std::string& fieldName);

	SportType getSport() const;
	SkillLevel getLevel() const;
	const std::tm& getWhen() const;
	int getDuration() const;
	int getMaxPlayers() const;
	const std::string getFieldName() const;

	
	void saveEvent(std::ostream& os, int id) const;
	static bool readEvent(std::istringstream& iss, Event& out);
	static bool parseDataTime(const std::string& dateStr,
		const std::string& timeStr,
		std::tm& out);
	static std::string formatDate(const std::tm& tp);
	static std::string formatTime(const std::tm& tp);

	void printEvent(int id) const;
};

