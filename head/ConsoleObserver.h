#ifndef CONSOLE_OBSERVER_H
#define CONSOLE_OBSERVER_H

#include "Observer.h"

// Конкретный наблюдатель, который выводит сообщения в консоль.
class ConsoleObserver : public Observer {
public:
    void onKill(NPC& killer, NPC& victim) override;
};

#endif 