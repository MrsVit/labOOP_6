#include "../head/FileObserver.h"
#include <iostream>
#include <ctime>

FileObserver::FileObserver() : logFile_("log.txt", std::ios::app) {
    if (!logFile_) {
        std::cerr << "Error: Cannot open log.txt for writing." << std::endl;
    } else {
        // Добавляем метку времени при открытии файла
        std::time_t now = std::time(nullptr);
        logFile_ << "=== Log started at: " << std::ctime(&now);
        logFile_.flush();
    }
}

FileObserver::~FileObserver() {
    if (logFile_) {
        logFile_ << "=== Log ended.\n\n";
        logFile_.close();
    }
}

void FileObserver::onKill(NPC& killer, NPC& victim) {
    if (logFile_) {
        logFile_ << "[KILL] " << killer.name << " (" << killer.type() << ") killed "
                 << victim.name << " (" << victim.type() << ")" << std::endl;
        logFile_.flush(); // Немедленно записываем в файл
    }
}