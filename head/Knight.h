#ifndef KNIGHT_H
#define KNIGHT_H

#include "NPC.h"

//класс рыцаря
class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y) : NPC(name, x, y) {}

    std::string type() const override { return "Knight"; }

    bool accept(Visitor& visitor, NPC& other) override;
};

#endif 