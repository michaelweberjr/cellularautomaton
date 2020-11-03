#pragma once

#include "creature.h"

class Doodlebug : public Creature
{
    CREATURE_REGISTER(Doodlebug, "doodlebug", 0, [](int x, int y) { return new Doodlebug(x, y); });

private:
    static const int TURNS_TO_BREED = 3;
    static const int TURNS_TO_STARVE = 3;

    int turnsToBreeding;
    int turnsToStarving;

public:
    Doodlebug(int startX, int startY, bool needsToMove = false) : Creature(id, startX, startY, needsToMove), turnsToBreeding(0), turnsToStarving(0) {}

    virtual void step(Board& board);
    virtual char toChar() const { return 'X'; }
    void setStarving(int starving) { turnsToStarving = starving; }
    void setBreeding(int breeding) { turnsToBreeding = breeding; }
};

class DoodlebugNesting : public Creature
{
    CREATURE_REGISTER(DoodlebugNesting, "doodlebug_nesting", 1, [](int x, int y) { return new DoodlebugNesting(x, y); });

private:
    static const int TURNS_TO_STARVE = 3;
    int turnsToStarving;
    int turnsToBreeding;

public:
    DoodlebugNesting(int startX, int startY, bool needsToMove = false) : Creature(id, startX, startY, needsToMove), turnsToStarving(0) {}

    virtual void step(Board& board);
    virtual char toChar() const { return 'X'; }
    void setStarving(int starving) { turnsToStarving = starving; }
    void setBreeding(int breeding) { turnsToBreeding = breeding; }
};

class DoodlebugLarva : public Creature
{
    CREATURE_REGISTER(DoodlebugLarva, "doodlebug_larva", 2, [](int x, int y) { return new DoodlebugLarva(x, y); });

private:
    static const int TURNS_TO_HATCH = 3;

    int turnsToHatch;

public:
    DoodlebugLarva(int startX, int startY, bool needsToMove = false) : Creature(id, startX, startY, needsToMove), turnsToHatch(0) {}

    virtual void step(Board& board);
    virtual char toChar() const { return 'l'; }
};
