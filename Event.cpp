#include "Event.h"
#include <sstream>
#include <iomanip>
#define  _CRT_SECURE_NO_WARNINGS


std::string sportToString(SportType s)
{
    switch (s) {
    case SportType::Football:
        return "Football";
    case SportType::Basketball:
        return "Basketball";
    case SportType::Tennis:
        return "Tennis";
    default:
        return "Football";
    }
}

std::string skillToString(SkillLevel l)
{
    switch (l) {
    case SkillLevel::Beginner:
        return "Beginner";
    case SkillLevel::Intermediate:
        return "Intermediate";
    case SkillLevel::Advanced:
        return "Advanced";
    default:
        return "Beginner";
    }
}

bool parseSport(const std::string& s, SportType& out)
{
    bool result = false;

    if (s == "Football" || s == "0") {
        out = SportType::Football;
        result = true;
    } 
    else if (s == "Basketball" || s == "1") {
        out = SportType::Basketball;
        result = true;
    } 
    else if (s == "Tennis" || s == "2") {
        out = SportType::Tennis;
        result = true;
    }
    
    return result;
}

bool parseSkill(const std::string& s, SkillLevel& out)
{
    bool result = false;

    if (s == "Beginner" || s == "0"){
        out = SkillLevel::Beginner;
        result = true;
    }
    else if (s == "Intermediate" || s == "1") {
        out = SkillLevel::Intermediate;
        result = true;
    }
    else if (s == "Advanced" || s == "2") {
        out = SkillLevel::Advanced;
        result = true;
    }
    
    return result;
}

Event::Event(SportType sport, SkillLevel level, 
    const std::tm& when,
    int duration, int maxPlayers, const std::string& fieldName) 
    :sport(sport), level(level), when(when),
    duration(duration),
    maxPlayers(maxPlayers), fieldName(fieldName)
{}

SportType Event::getSport() const
{
    return sport;
}

SkillLevel Event::getLevel() const
{
    return level;
}

const std::tm& Event::getWhen() const
{
    return when;
}

int Event::getDuration() const
{
    return duration;
}

int Event::getMaxPlayers() const
{
    return maxPlayers;
}

const std::string Event::getFieldName() const
{
    return fieldName;
}

void Event::saveEvent(std::ostream& os, int id) const
{
    os << id << "|"
        << sportToString(getSport()) << "|"
        << skillToString(getLevel()) << "|"
        << formatDate(getWhen()) << "|"
        << formatTime(getWhen()) << "|"
        << getDuration() << "|"
        << getMaxPlayers() << "|"
        << getFieldName() << "\n";
}

bool Event::readEvent(std::istringstream& iss, Event& out)
{
    std::string sport, level, dateStr, timeStr, duration, maxPlayers, fieldStr;
   
    if (!std::getline(iss, sport, '|')) {
        return false;
    }
    if (!std::getline(iss, level, '|')) {
        return false;
    }
    if (!std::getline(iss, dateStr, '|')) {
        return false;
    }
    if (!std::getline(iss, timeStr, '|')) {
        return false;
    }
    if(!std::getline(iss, duration, '|')) {
        return false;
    }
    if (!std::getline(iss, maxPlayers, '|')) {
        return false;
    }
    if (!std::getline(iss, fieldStr)) {
        return false;
    }
   
    SportType s;
    SkillLevel l;
    if(!parseSport(sport, s)) {
        return false;
    }
    if (!parseSkill(level, l)) {
        return false;
    }
    int dur = 0;
    int maxPl = 0;
    try {
        dur = std::stoi(duration);
        maxPl = std::stoi(maxPlayers);
    } 
    catch (...) {
        return false;
    }
    std::tm tp;
    if (!Event::parseDataTime(dateStr, timeStr, tp))
    {
        return false;
    }
    out = Event(s, l, tp, dur, maxPl, fieldStr);
    return true;
}

static bool parseYMD(const std::string& ymd, int& Y, int& M, int& D) {
    if (ymd.size() != 10 || ymd[4] != '-' || ymd[7] != '-') {
        return false;
    }
    try {
        Y = std::stoi(ymd.substr(0, 4));
        M = std::stoi(ymd.substr(5, 2));
        D = std::stoi(ymd.substr(8, 2));
    }
    catch (...) {
        return false;
    }

    return  (Y >= 1900 && M >= 1 && M <= 12 || D >= 1 || D <= 31);
    
}
static bool parseHM(const std::string& hm, int& H, int& Min) {
    if (hm.size() != 5 || hm[2] != ':') {
        return false;
    }
    try {
        H = std::stoi(hm.substr(0, 2));
        Min = std::stoi(hm.substr(3, 2));
    }
    catch (...) { 
        return false;
    }

    return (H >= 0 && H <= 23 && Min >= 0 && Min <= 59);
    
}

bool Event::parseDataTime(const std::string& dateStr, const std::string& timeStr, 
    std::tm& out)
{
    int Y, M, D, H, Min;
    if (!parseYMD(dateStr, Y, M, D)) {
        return false;
    }
    if (!parseHM(timeStr, H, Min)) {
        return false;
    }
    std::tm tm{};
    out.tm_year = Y - 1900;
    out.tm_mon = M - 1;
    out.tm_mday = D;
    out.tm_hour = H;
    out.tm_min = Min;
    out.tm_sec = 0;
    out.tm_isdst = -1;

    return true;
}

std::string Event::formatDate(const std::tm& tp)
{
    std::ostringstream oss;
    oss << std::put_time(&tp, "%Y-%m-%d");
    return oss.str();
}

std::string Event::formatTime(const std::tm& tp)
{
    std::ostringstream oss;
    oss << std::put_time(&tp, "%H:%M");
    return oss.str();
}

void Event::printEvent(int id) const {
    std::cout << id << "|"
        << sportToString(getSport()) << "|"
        << skillToString(getLevel()) << "|"
        << formatDate(getWhen()) << "|"
        << formatTime(getWhen()) << "|"
        << getDuration() << "|"
        << getMaxPlayers() << "|"
        << getFieldName() << "\n";
}
