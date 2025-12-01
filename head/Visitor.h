#ifndef VISITOR_H
#define VISITOR_H

class NPC;

class Visitor {
public:
    virtual ~Visitor() = default;

    // Методы для каждого типа NPCшек
    virtual bool visitKnight(NPC& other) = 0;
    virtual bool visitDruid(NPC& other) = 0;
    virtual bool visitElf(NPC& other) = 0;
};

#endif 