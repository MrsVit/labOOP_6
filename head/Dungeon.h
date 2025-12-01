#ifndef DUNGEON_H
#define DUNGEON_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <string>

// Главный класс редактора подземелья, управление нпс-шками
class Dungeon {
private:
    std::vector<std::unique_ptr<NPC>> npcs_;
    std::vector<std::unique_ptr<Observer>> observers_;

public:
    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void print() const;
    void battle(int range);
    void addObserver(std::unique_ptr<Observer> observer);
    void notifyKill(NPC& killer, NPC& victim);

    size_t size() const { return npcs_.size(); }
    NPC& get(size_t index) { return *npcs_[index]; }
    const NPC& get(size_t index) const { return *npcs_[index]; }

    Dungeon* getDungeonPtr() { return this; }
};

#endif 