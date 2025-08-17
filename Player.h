#pragma once
#include <unordered_set>
#include <iostream>

class Player
{
private:
	std::unordered_set<int> eventIds;

public:
	Player() = default;
	bool joinOrleaveEvent(int eventId);
	void removeEventById(int eventId);
	void printParticipations(std::ostream& os = std::cout) const;
	void savePlayerinEvents() const;
	void readIDPlayer();
};

