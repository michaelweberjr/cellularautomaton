#include <iostream>
using namespace std;

#include "board.h"
#include "creature.h"

Board::Board(int newSizeX, int newSizeY, vector<pair<CreatureID, int>>& initialBoard)
    : sizeX(newSizeX), sizeY(newSizeY), turnCount(1)
{
    int totalSpaces = sizeX * sizeY;

    cells = new Creature * [totalSpaces];
    for (int i = 0; i < totalSpaces; i++)
    {
        cells[i] = nullptr;
    }

    int remainingSpaces = totalSpaces;
    for(int c = 0; c < initialBoard.size(); c++)
    {
        for (int i = 0; i < initialBoard[c].second; i++)
        {
            int space = rand() % remainingSpaces--;
            int spaceCount = 0;
            for (int j = 0; j < totalSpaces; j++)
            {
                if (cells[j] == nullptr)
                {
                    if (++spaceCount == space)
                    {
                        int x = j % sizeY;
                        int y = j / sizeY;
                        cells[j] = Creature::factory(initialBoard[c].first, x, y);
                        break;
                    }
                }
            }
        }
    }
}

void Board::step()
{
    turnCount++;

    // Run each creature in priority order
    auto priority = Creature::getPriorityList();
    while (priority != nullptr)
    {
        for (int i = 0; i < sizeX * sizeY; i++)
        {
            if (cells[i] != nullptr && cells[i]->status())
            {
                for (int j = 0; j < priority->list.size(); j++)
                {
                    if(priority->list[j] == cells[i]->getID())
                        cells[i]->step(*this);
                }
            }
        }
        priority = priority->next;
    }

    // reset all of the organisms
    for (int i = 0; i < sizeX * sizeY; i++)
    {
        if (cells[i] != nullptr)
        {
            cells[i]->reset();
        }
    }

    cleanup();
}

void Board::setCell(CreatureID id, int x, int y)
{
    int cell = y * sizeX + x;
    if (cells[cell] != nullptr) eraseCell(x, y);
    cells[cell] = Creature::factory(id, x, y);
}

void Board::moveCell(int startX, int startY, int endX, int endY)
{
    int cellStart = startY * sizeX + startX;
    int cellEnd = endY * sizeX + endX;
    if (cells[cellStart] == nullptr) return;
    if (cells[cellEnd] != nullptr) eraseCell(endX, endY);
    cells[cellEnd] = cells[cellStart];
    cells[cellStart] = nullptr;
}

void Board::eraseCell(int x, int y)
{
    int cell = y * sizeX + x;
    garbage.push_back(cells[cell]);
    cells[cell] = nullptr;
}

void Board::getRandomDir(int startX, int startY, int& outX, int& outY, CreatureID searchID, bool ordinal, int distance)
{
    bool triedDir[DEGREES_OF_FREEDOM] = { 0 };

    int degreesOfFreedom = ordinal ? 4 : 8;

    for (int i = 0; i < degreesOfFreedom; i++)
    {
        int dir = rand() % (degreesOfFreedom - i);
        int dirCount = 0;
        for (int j = 0; j < degreesOfFreedom; j++)
        {
            if (!triedDir[j])
            {
                if (dir == dirCount++)
                {
                    dir = j;
                    break;
                }
            }
        }

        int tempX = startX;
        int tempY = startY;
        switch (dir)
        {
        case DIR_UP:
            tempY -= distance;
            break;
        case DIR_RIGHT:
            tempX += distance;
            break;
        case DIR_DOWN:
            tempY += distance;
            break;
        case DIR_LEFT:
            tempX -= distance;
            break;
        }

        CreatureID id = getCreatureID(tempX, tempY);
        if (searchID == Creature::emptyID && isEmpty(tempX, tempY)) 
        {
            outX = tempX;
            outY = tempY;
            return;
        }
        else if (searchID == id || (searchID == Creature::anyID && id != Creature::emptyID && id != -3))
        {
            outX = tempX;
            outY = tempY;
            return;
        }

        triedDir[dir] = true;
    }

    outX = -1;
    outY = -1;
}

bool Board::isEmpty(int x, int y)
{
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY)
    {
        return false;
    }

    int cell = y * sizeX + x;
    if (cells[cell] == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

CreatureID Board::getCreatureID(int x, int y)
{
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY)
    {
        return -3;
    }

    if (isEmpty(x, y)) return Creature::emptyID;
    else
    {
        int cell = y * sizeX + x;
        return cells[cell]->getID();
    }
}

void Board::print()
{
    cout << "Turn[" << turnCount << "]:" << endl;

    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            int cell = i * sizeY + j;
            if (cells[cell] == nullptr)
            {
                cout << "-";
            }
            else
            {
                cout << cells[cell]->toChar();
            }
        }
        cout << endl;
    }
}

void Board::cleanup()
{
    for (int i = 0; i < garbage.size(); i++)
    {
        delete garbage[i];
    }

    garbage.clear();
}

Board::~Board()
{
    for (int i = 0; i < sizeX * sizeY; i++)
    {
        if (cells[i] != nullptr)
        {
            delete cells[i];
        }
    }

    cleanup();
    delete[] cells;
}