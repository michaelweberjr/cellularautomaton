#pragma once

#include <vector>

class Creature;
typedef int CreatureID;

const int DEGREES_OF_FREEDOM = 4;

const int DIR_UP = 0;
const int DIR_RIGHT = 1;
const int DIR_DOWN = 2;
const int DIR_LEFT = 3;

class Board
{
private:
    int sizeX, sizeY;
    int turnCount;

    // 1d board array of Organism*
    Creature** cells;

    std::vector<Creature*> garbage;
    void cleanup();

public:
    Board(int newSizeX, int newSizeY, int antCount, int doodleBugCount);
    ~Board();

    void step();
    void print();
    bool isEmpty(int x, int y);
    CreatureID getCreatureID(int x, int y);
    void setCell(int x, int y, Creature* creature);
    void eraseCell(int x, int y);
    void getRandomDir(int startX, int startY, bool findFirst, int& outX, int& outY);
};
