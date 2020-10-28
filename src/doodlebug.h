#pragma once

#include "creature.h"

class Doodlebug : public Creature
{
    CREATURE_REGISTER(Doodlebug, "doodlebug", 0, [](int x, int y) { return new Doodlebug(x, y); });

private:
    static const int TURNS_TO_BREED = 8;
    static const int TURNS_TO_STARVE = 3;

    int turnsToBreeding;
    int turnsToStarving;

public:
    Doodlebug(int startX, int startY, bool needsToMove = false) : Creature(id, startX, startY, needsToMove), turnsToBreeding(0), turnsToStarving(0) {}

    virtual void step(Board& board);
    virtual char toChar() const { return 'X'; }
};
