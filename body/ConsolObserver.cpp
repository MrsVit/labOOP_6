#include "../head/ConsoleObserver.h"
#include <iostream>

void ConsoleObserver::onKill(NPC& killer, NPC& victim) {
    std::cout << "[KILL] " << killer.name << " (" << killer.type() << ") killed "
              << victim.name << " (" << victim.type() << ")" << std::endl;
}