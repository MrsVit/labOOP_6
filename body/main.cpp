#include "../head/Dungeon.h"
#include "../head/ConsoleObserver.h"
#include "../head/FileObserver.h"
#include <iostream>
#include <memory>

int main() {
    Dungeon dungeon;
    dungeon.addObserver(std::make_unique<ConsoleObserver>());
    dungeon.addObserver(std::make_unique<FileObserver>());

    while (true) {
        std::cout << "\n1. Add NPC (Knight/Druid/Elf)\n"
                  << "2. Print NPCs\n"
                  << "3. Save to file\n"
                  << "4. Load from file\n"
                  << "5. Battle (enter range)\n"
                  << "6. Quit\n> ";

        int cmd;
        if (!(std::cin >> cmd)) break;

        try {
            switch (cmd) {
                case 1: {
                    std::string type, name;
                    int x, y;
                    std::cout << "Type (Knight/Druid/Elf): "; std::cin >> type;
                    std::cout << "Name: "; std::cin >> name;
                    std::cout << "x (0–500): "; std::cin >> x;
                    std::cout << "y (0–500): "; std::cin >> y;
                    dungeon.addNPC(type, name, x, y);
                    std::cout << " Added.\n";
                    break;
                }
                case 2: dungeon.print(); break;
                case 3: {
                    std::string f; std::cout << "Filename: "; std::cin >> f;
                    dungeon.saveToFile(f);
                    std::cout << " Saved to " << f << "\n";
                    break;
                }
                case 4: {
                    std::string f; std::cout << "Filename: "; std::cin >> f;
                    dungeon.loadFromFile(f);
                    std::cout << " Loaded from " << f << "\n";
                    break;
                }
                case 5: {
                    int r; std::cout << "Battle range: "; std::cin >> r;
                    std::cout << "  Battle started (range = " << r << ")...\n";
                    dungeon.battle(r);
                    std::cout << " Battle finished.\n";
                    break;
                }
                case 6: std::cout << "Bye!\n"; return 0;
                default: std::cout << "Invalid command.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error:( " << e.what() << "\n";
        }
    }
    return 0;
}