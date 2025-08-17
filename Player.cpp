#include "Player.h"
#include <fstream>
#include <sstream>
bool Player::joinOrleaveEvent(int eventId)
{
    auto it = eventIds.find(eventId);
    if (it != eventIds.end()) {
        eventIds.erase(it);
        return false;
    }
    else {
        eventIds.insert(eventId);
        return true;
    }
}

void Player::removeEventById(int eventId)
{
    // eventIds.erase(eventId);
    auto it = eventIds.find(eventId);
    if (it != eventIds.end()) {
        eventIds.erase(eventId);
    }
}

void Player::printParticipations(std::ostream& os) const
{
    os << "Player joins in events (ID): ";
    if (eventIds.empty()) {
        os << "(none)\n";
        return;
    }
    bool first = true;

    for (int id : eventIds) {
        if (!first) {
            os << ", ";
        }
        os << id;
        first = false;
    }
    os << "\n";
}

void Player::savePlayerinEvents() const
{
    std::ofstream idFiles("idFiles.txt");
    if (!idFiles.is_open()) {
        return;
    }
    bool first = true;
    std::cout << "Save all id:  " << std::endl;
    for (const auto& tmp : eventIds) {
        if (!first) {
            idFiles << ",";
        }
        idFiles << tmp;
        first = false;
    }
    idFiles << "\n";
    idFiles.close();
}

void Player::readIDPlayer()
{
    std::ifstream idFiles("idFiles.txt");
    if (!idFiles.is_open()) {
        return;
    }
    std::string line;
    if (std::getline(idFiles, line)) {
        std::istringstream iss(line);

        std::string tmp;

        while(std::getline(iss, tmp, ',')) {
            eventIds.insert(std::stoi(tmp));
        }
        
    }
    idFiles.close();


}
