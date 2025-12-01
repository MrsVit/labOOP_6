#include "../head/NPCFactory.h"
#include "../head/Knight.h"
#include "../head/Druid.h"
#include "../head/Elf.h"
#include <sstream>
#include <stdexcept>

std::unique_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Knight") {
        return std::make_unique<Knight>(name, x, y);
    } else if (type == "Druid") {
        return std::make_unique<Druid>(name, x, y);
    } else if (type == "Elf") {
        return std::make_unique<Elf>(name, x, y);
    } else {
        throw std::invalid_argument("Unknown NPC type: " + type);
    }
}

std::unique_ptr<NPC> NPCFactory::loadFromLine(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    int x, y;

    if (std::getline(iss, type, ',') &&
        std::getline(iss, name, ',') &&
        (iss >> x) && (iss.ignore() && (iss >> y))) {
        return create(type, name, x, y);
    } else {
        throw std::invalid_argument("Invalid line format for NPC: " + line);
    }
}