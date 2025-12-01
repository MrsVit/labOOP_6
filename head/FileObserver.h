#ifndef FILE_OBSERVER_H
#define FILE_OBSERVER_H

#include "Observer.h"
#include <fstream>

// запись в лог.тхт
class FileObserver : public Observer {
private:
    std::ofstream logFile_;

public:
    FileObserver();
    ~FileObserver();

    void onKill(NPC& killer, NPC& victim) override;
};

#endif