#pragma once

#include <vector>
#include <utility>

class Creature;
typedef int CreatureID;
const CreatureID EMPTY_ID = -1;

const int DEGREES_OF_FREEDOM = 8;
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
    Board(int newSizeX, int newSizeY, std::vector<std::pair<CreatureID, int>>& initialBoard);
    ~Board();

    void step();
    void print();
    bool isEmpty(int x, int y);
    CreatureID getCreatureID(int x, int y);
    void getRandomDir(int startX, int startY, int& outX, int& outY, CreatureID searchID = EMPTY_ID, bool ordinal = true, int distance = 1);
    void moveCell(int startX, int startY, int endX, int endY);
    void setCell(CreatureID id, int x, int y);
    void eraseCell(int x, int y);
};
