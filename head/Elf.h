#ifndef ELF_H
#define ELF_H

#include "NPC.h"


class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}

    std::string type() const override { return "Elf"; }

    bool accept(Visitor& visitor, NPC& other) override;
};

#endif 