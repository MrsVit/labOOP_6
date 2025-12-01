#ifndef DRUID_H
#define DRUID_H

#include "NPC.h"

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y) : NPC(name, x, y) {}

    std::string type() const override { return "Druid"; }

    bool accept(Visitor& visitor, NPC& other) override;
};

#endif 