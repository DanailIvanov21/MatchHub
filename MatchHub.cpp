#include "Event.h"
#include "Player.h"
#include "EventManager.h"
#include <iostream>
#include <ctime>
const int MAX = 32;

int main()
{
    EventManager manager("active.txt", "all.txt");
    Player player;
    player.readIDPlayer();
    bool flag = true;
    char command[MAX];
    do {
        std::cout << "Write commands: " << std::endl;
        std::cin >> command;
        if (strcmp(command, "addEvent") == 0) {
            int sport, level, duration, maxPlayers;
            std::string field, date, time;

            std::cout << "Sport: ";
            std::cin >> sport;

            std::cout << "Level: ";
            std::cin >> level;

            std::cout << "Date(YYYY-MM-DD): ";
            std::cin >> date;

            std::cout << "Hour(HH:MM): ";
            std::cin >> time;

            std::cout << "Duration: ";
            std::cin >> duration;

            std::cout << "MaxPlayers: ";
            std::cin >> maxPlayers;

            std::cout << "Field: ";
            std::cin.ignore();
            std::getline(std::cin, field);

            std::tm tp;
            if (!Event::parseDataTime(date, time, tp)) {
                std::cout << "Invalid date ot time\n";
                return -1;
            }

            int id = manager.addEvent(static_cast<SportType>(sport),
                static_cast<SkillLevel>(level), tp, duration,
                maxPlayers, field);

            std::cout << "Event is added with ID= " << id << "\n";
        }
        else if (strcmp(command, "removeEvent") == 0) {
            int id;
            std::cout << "ID event for remove: ";
            std::cin >> id;
            if (manager.removeEvent(id, player)) {
                std::cout << "Event removed\n";
            }
            else {
                std::cout << "None this event\n";
            }
        }
        else if (strcmp(command, "printActive") == 0) {
            manager.printActive();
        }
        else if (strcmp(command, "printPast") == 0) {
            manager.printPast();
        }
        else if (strcmp(command, "printAll") == 0) {
            manager.printAll();
            player.printParticipations();
        }
        else if (strcmp(command, "getActiveEvent") == 0) {
            int id;
            std::cout << "ID event for remove: ";
            std::cin >> id;

            Event* e = manager.getActiveEvent(id);
            if (!e) {
                std::cout << "None this active event\n";
                continue;
            }

            bool joined = player.joinOrleaveEvent(id);
            std::cout << (joined ? "join\n" : "out\n");
        }
        else if (strcmp(command, "joinOrleaveEvent") == 0) {
            int id;
            std::cout << "ID event for joinOrLeave: ";
            std::cin >> id;
            player.joinOrleaveEvent(id);
        }
        else if (strcmp(command, "printParticipations") == 0) {
            player.printParticipations();
            
        }
        else if (strcmp(command, "onExitSave") == 0) {
            flag = false;
            manager.onExitSave();
            player.savePlayerinEvents();
        }


    } while (flag);
}

