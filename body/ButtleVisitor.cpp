#include "../head/BattleVisitor.h"
#include "../head/Dungeon.h"
#include "../head/Knight.h"
#include "../head/Druid.h"
#include "../head/Elf.h"

bool BattleVisitor::visitKnight(NPC& other) {
    // Рыцарь убивает эльфа
    if (dynamic_cast<Elf*>(&other)) {
        killed_ = true;
        dungeon_.notifyKill(attacker_, other);
        return true;
    }
    return false;
}

bool BattleVisitor::visitDruid(NPC& other) {
    // Друид убивает друидов
    if (dynamic_cast<Druid*>(&other)) {
        killed_ = true;
        dungeon_.notifyKill(attacker_, other);
        return true;
    }
    return false;
}

bool BattleVisitor::visitElf(NPC& other) {
    // Эльф убивает друида и рыцаря
    if (dynamic_cast<Druid*>(&other) || dynamic_cast<Knight*>(&other)) {
        killed_ = true;
        dungeon_.notifyKill(attacker_, other);
        return true;
    }
    return false;
}