#ifndef OBSERVER_H
#define OBSERVER_H

#include "NPC.h"

// Абстрактный класс Observer. Определяет интерфейс для наблюдателей.
// Следует принципу Dependency Inversion: Dungeon зависит от абстракции Observer,
// а не от конкретных реализаций.
class Observer {
public:
    virtual ~Observer() = default;

    // Метод, который вызывается при убийстве NPC.
    virtual void onKill(NPC& killer, NPC& victim) = 0;
};

#endif // OBSERVER_H