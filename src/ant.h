#pragma once

#include "creature.h"

class Ant : public Creature
{
    CREATURE_REGISTER(Ant, "ant", 10, [](int x, int y) { return new Ant(x, y); });

private:
    int turnsToBreeding;
    static const int TURNS_TO_BREED = 3;

public:
    Ant(int startX, int startY, bool needsToMove = false) : Creature(id, startX, startY, needsToMove), turnsToBreeding(0) {}

    virtual void step(Board& board);
    virtual char toChar() const { return 'o'; }
};
