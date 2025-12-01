#ifndef BATTLE_VISITOR_H
#define BATTLE_VISITOR_H

#include "Visitor.h"
#include <string>

class NPC;
class Dungeon; // forward declaration

class BattleVisitor : public Visitor {
private:
    NPC& attacker_;
    Dungeon& dungeon_; 
    bool killed_ = false;

public:
    BattleVisitor(NPC& attacker, Dungeon& dungeon)
        : attacker_(attacker), dungeon_(dungeon) {}

    bool killed() const { return killed_; }

    bool visitKnight(NPC& other) override;
    bool visitDruid(NPC& other) override;
    bool visitElf(NPC& other) override;
};

#endif