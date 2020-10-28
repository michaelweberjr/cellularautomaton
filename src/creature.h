#pragma once

#include <vector>
#include <string>
#include <utility>
#include <functional>

class Board;
class CreaturePriority;

typedef int CreatureID;

#define CREATURE_REGISTER(CREATURE_CLA, STR_NAME, PRIORITY, CREATURE_PR)  \
    private:    \
    static CreatureID id;   \
    friend class constructor;   \
    struct constructor {    \
        constructor() { \
            CREATURE_CLA::id = Creature::registerCreatureType((STR_NAME), (PRIORITY), (CREATURE_PR));   \
        }   \
    };  \
    static constructor cons;   \
    public: \
    static CreatureID get##CREATURE_CLA##ID() { return id; } \


#define CREATURE_STATIC_DATA(CREATURE_CLA)  \
    CreatureID CREATURE_CLA::id = -1;  \
    CREATURE_CLA::constructor CREATURE_CLA::cons = CREATURE_CLA::constructor() \


class Creature
{
protected:
    typedef std::function<Creature* (int, int)> FactoryPr;
    typedef std::pair<std::string, FactoryPr> RegistryItem;
    typedef std::vector<RegistryItem> RegistryList;

private:
    int x, y;
    bool needsToMove;
    CreatureID typeID;

    static RegistryList& getRegistry();
    static void addPriority(CreatureID id, unsigned int priority);

protected:
    void setMoved() { needsToMove = false; }
    static CreatureID registerCreatureType(std::string name, unsigned int priority, FactoryPr);

public:
    static const CreatureID emptyID = -1;
    static const CreatureID anyID = -2;

    Creature(CreatureID id, int startX, int startY, bool needsToMove = false) : typeID(id), x(startX), y(startY), needsToMove(needsToMove) {}
    virtual ~Creature() { }

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    bool status() const { return needsToMove; }
    void reset() { needsToMove = true; }
    CreatureID getID() const { return typeID; }

    virtual void step(Board& board);
    virtual char toChar() const = 0;

    static void printRegistry();
    static CreaturePriority*& getPriorityList();
    static Creature* factory(CreatureID id, int x, int y);
};

class CreaturePriority
{
public:
    CreaturePriority* next;
    unsigned int priority;
    std::vector<CreatureID> list;

    CreaturePriority(unsigned int priority, CreatureID id) : next(nullptr), priority(priority), list({id}) {}
};
