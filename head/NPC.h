#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>

/* S: только база NPCшек
O: нельзя модифицирорвать, можно масштабировать
L: подклассы заменяемы без изменения поведения
I: минимальный интерфейс
D: базируется на абстракциях
*/
class NPC {
public:
    virtual ~NPC() = default;

    virtual std::string type() const = 0;
    virtual bool accept(class Visitor& visitor, NPC& other) = 0;

    std::string name;
    int x, y;

protected:
    NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
};

#endif 