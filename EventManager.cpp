#include "EventManager.h"
#include <fstream>
#include <sstream>
#include <ctime>

int EventManager::nextId = 1;
void EventManager::initFromFiles()
{
    loadAllEventsMaxId();
    loadActiveEvents();
    reconstructPastFromAll();
    
}

void EventManager::loadAllEventsMaxId()
{
    std::ifstream in(allPath);
    if (!in.is_open()) {
        return;
    }
    std::string line;

    while (std::getline(in, line)) {
        int id;
        Event e;
        std::istringstream iss(line);

        if (!(iss >> id)) {
            continue;
        } 
        iss.ignore(1);

        if (Event::readEvent(iss, e)) {
            if (id >= nextId) {
                nextId = id + 1;
            }
        }

    }
    std::ifstream inActive(activePath);
    if (!inActive.is_open()) {
        return;
    }
    while (std::getline(inActive, line)) {
        int id;
        Event e;
        std::istringstream iss(line);

        if (!(iss >> id)) {
            continue;
        }
        iss.ignore(1);

        if (Event::readEvent(iss, e)) {
            if (id >= nextId) {
                nextId = id + 1;
            }
        }

    }
    in.close();
    inActive.close();
}

void EventManager::loadActiveEvents()
{
    std::ifstream in(activePath);
    if (!in.is_open()) {
        return;
    }
    std::string line;

    while (std::getline(in, line)) {
        int id;
        Event e;
        std::istringstream iss(line);

        if (!(iss >> id)) {
            continue;
        }
        iss.ignore(1);
        if (Event::readEvent(iss, e)) {
            activeEvents[id] = e;
        }
    }
    in.close();
    
}

void EventManager::reconstructPastFromAll()
{
    std::ifstream in(allPath);
    if (!in.is_open()) {
        return;
    }
    std::string line;

    auto now = std::chrono::system_clock::now();

    while (std::getline(in, line)) {
        int id;
        Event e;
        std::istringstream iss(line);

        if (!(iss >> id)) {
            continue;
        }
        iss.ignore(1);
        if (!Event::readEvent(iss, e)) {
            continue;
        }
        if (e.getWhen() < now && activeEvents.find(id) ==
            activeEvents.end()) {
            allHistoryEvents[id] = e;
        }
        
    }
    in.close();
}



EventManager::EventManager(const std::string& activeFile, const std::string& allFile)
    :activePath(activeFile), allPath(allFile)
{
    initFromFiles();
}

int EventManager::addEvent(SportType sport, SkillLevel level,
    const std::chrono::system_clock::time_point& when, 
    int duration, int maxPlayers, const std::string& fieldName)
{
    Event e(sport, level, when, duration, maxPlayers, fieldName);
    int id = nextId++;
    activeEvents[id] = e;

    return id;
}

bool EventManager::removeEvent(int id, Player& player)
{
    auto it = activeEvents.find(id);
    if (it == activeEvents.end()) {
        return false;
    }
    //ako e minal eventa se dobawq v past
    auto now = std::chrono::system_clock::now();
    if (it->second.getWhen() < now) {
        allHistoryEvents[id] = it->second;
    }
    
    //remove
    activeEvents.erase(it);
    player.removeEventById(id);

    return true;
}

Event* EventManager::getActiveEvent(int id)
{
    auto it = activeEvents.find(id);

    if (it == activeEvents.end()) {
        return nullptr;
    }
    return &it->second;
}

void EventManager::printActive(std::ostream& os) const
{
    os << " Active events \n";
    for (const auto& tmp : activeEvents) {
        tmp.second.printEvent(tmp.first);
    }
}

void EventManager::printPast(std::ostream& os) const
{
    os << " Past events \n";
    for (const auto& tmp : allHistoryEvents) {
        tmp.second.printEvent(tmp.first);
    }
}

void EventManager::printAll(std::ostream& os) const
{
    os << " All events \n";
    for (const auto& tmp : activeEvents) {
        tmp.second.printEvent(tmp.first);
    }
    for (const auto& tmp : allHistoryEvents) {
        tmp.second.printEvent(tmp.first);
    }
}

void EventManager::onExitSave() const
{
    std::ofstream active(activePath);
    std::ofstream allPast(allPath);

    for (const auto& tmp : activeEvents) {
        tmp.second.saveEvent(active,tmp.first);
    }
    for (const auto& tmp : allHistoryEvents) {
        tmp.second.saveEvent(allPast,tmp.first);
    }
    active.close();
    allPast.close();

}
