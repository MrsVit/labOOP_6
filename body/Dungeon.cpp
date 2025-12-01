#include "../head/Dungeon.h"
#include "../head/NPC.h"
#include "../head/BattleVisitor.h"
#include "../head/NPCFactory.h"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>

void Dungeon::addNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Coordinates must be in [0, 500]");
    }
    auto npc = NPCFactory::create(type, name, x, y);
    npcs_.push_back(std::move(npc));
}

void Dungeon::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Cannot open " + filename);
    for (const auto& npc : npcs_) {
        file << npc->type() << "," << npc->name << "," << npc->x << "," << npc->y << "\n";
    }
}

void Dungeon::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open " + filename);
    npcs_.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                auto npc = NPCFactory::loadFromLine(line);
                npcs_.push_back(std::move(npc));
            } catch (const std::exception& e) {
                std::cerr << "⚠️  Skip line: " << line << " — " << e.what() << "\n";
            }
        }
    }
}

void Dungeon::print() const {
    std::cout << "=== NPCs (" << npcs_.size() << ") ===\n";
    for (size_t i = 0; i < npcs_.size(); ++i) {
        const auto& npc = *npcs_[i];
        std::cout << "[" << i << "] " << npc.type() << " '" << npc.name
                  << "' @ (" << npc.x << ", " << npc.y << ")\n";
    }
    std::cout << "====================\n";
}

void Dungeon::battle(int range) {
    if (range < 0) throw std::invalid_argument("Range must be >= 0");

    std::vector<size_t> toRemove;

    for (size_t i = 0; i < npcs_.size(); ++i) {
        for (size_t j = i + 1; j < npcs_.size(); ++j) {
            NPC& a = *npcs_[i];
            NPC& b = *npcs_[j];

            int dx = a.x - b.x;
            int dy = a.y - b.y;
            if (dx * dx + dy * dy <= range * range) {
                BattleVisitor visitorA(a, *this);
                BattleVisitor visitorB(b, *this);

                bool killB = a.accept(visitorA, b);
                bool killA = b.accept(visitorB, a);

                if (killA) toRemove.push_back(i);
                if (killB) toRemove.push_back(j);
            }
        }
    }

    std::sort(toRemove.begin(), toRemove.end(), std::greater<>());
    toRemove.erase(std::unique(toRemove.begin(), toRemove.end()), toRemove.end());

    for (size_t idx : toRemove) {
        npcs_.erase(npcs_.begin() + idx);
    }
}

void Dungeon::addObserver(std::unique_ptr<Observer> observer) {
    observers_.push_back(std::move(observer));
}

void Dungeon::notifyKill(NPC& killer, NPC& victim) {
    for (auto& obs : observers_) {
        obs->onKill(killer, victim);
    }
}