#include "../head/NPC.h"
#include "../head/Knight.h"
#include "../head/Druid.h"
#include "../head/Elf.h"
#include "../head/Visitor.h"

bool Knight::accept(Visitor& visitor, NPC& other) {
    if (auto* knight = dynamic_cast<Knight*>(&other)) {
        return visitor.visitKnight(*knight);
    }
    if (auto* druid = dynamic_cast<Druid*>(&other)) {
        return visitor.visitDruid(*druid);
    }
    if (auto* elf = dynamic_cast<Elf*>(&other)) {
        return visitor.visitElf(*elf);
    }
    return false; 
}

bool Druid::accept(Visitor& visitor, NPC& other) {
    if (auto* knight = dynamic_cast<Knight*>(&other)) {
        return visitor.visitKnight(*knight);
    }
    if (auto* druid = dynamic_cast<Druid*>(&other)) {
        return visitor.visitDruid(*druid);
    }
    if (auto* elf = dynamic_cast<Elf*>(&other)) {
        return visitor.visitElf(*elf);
    }
    return false;
}

bool Elf::accept(Visitor& visitor, NPC& other) {
    if (auto* knight = dynamic_cast<Knight*>(&other)) {
        return visitor.visitKnight(*knight);
    }
    if (auto* druid = dynamic_cast<Druid*>(&other)) {
        return visitor.visitDruid(*druid);
    }
    if (auto* elf = dynamic_cast<Elf*>(&other)) {
        return visitor.visitElf(*elf);
    }
    return false;
}