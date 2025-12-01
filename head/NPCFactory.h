#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "NPC.h"
#include <string>
#include <memory>

// Фабричный класс для создания NPC.
// Следует принципу Factory Method: делегирует создание объектов подклассам.
// Также позволяет загружать NPC из строки (например, из файла).
class NPCFactory {
public:
    // Создает NPC по типу, имени и координатам.
    static std::unique_ptr<NPC> create(const std::string& type, const std::string& name, int x, int y);

    // Загружает NPC из строки формата "Type,Name,X,Y".
    static std::unique_ptr<NPC> loadFromLine(const std::string& line);
};

#endif // NPC_FACTORY_H