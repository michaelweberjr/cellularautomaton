#include <iostream>
using namespace std;

#include "board.h"
#include "creature.h"
#include "ant.h"
#include "doodlebug.h"

Board::Board(int newSizeX, int newSizeY, int antCount, int doodleBugCount)
    : sizeX(newSizeX), sizeY(newSizeY), turnCount(1)
{
    int totalSpaces = sizeX * sizeY;

    cells = new Creature*[totalSpaces];
    for (int i = 0; i < totalSpaces; i++)
    {
        cells[i] = nullptr;
    }

    int remainingSpaces = totalSpaces;
    for (int i = 0; i < antCount; i++)
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
                    cells[j] = new Ant(x, y, true);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < doodleBugCount; i++)
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
                    cells[j] = new DoodleBug(x, y, true);
                    break;
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

void Board::setCell(int x, int y, Creature* creature)
{
    cells[y * sizeX + x] = creature;
}

void Board::eraseCell(int x, int y)
{
    int cell = y * sizeX + x;
    garbage.push_back(cells[cell]);
    cells[cell] = nullptr;
}

void Board::getRandomDir(int startX, int startY, bool findFirst, int& outX, int& outY)
{
    bool triedDir[DEGREES_OF_FREEDOM] = { false, false, false, false };

    for (int i = 0; i < DEGREES_OF_FREEDOM; i++)
    {
        int dir = rand() % (DEGREES_OF_FREEDOM - i);
        int dirCount = 0;
        for (int j = 0; j < DEGREES_OF_FREEDOM; j++)
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
            tempY--;
            break;
        case DIR_RIGHT:
            tempX++;
            break;
        case DIR_DOWN:
            tempY++;
            break;
        case DIR_LEFT:
            tempX--;
            break;
        }

        if (isEmpty(tempX, tempY))
        {
            outX = tempX;
            outY = tempY;
            return;
        }
        else
        {
            if (findFirst)
            {
                outX = -1;
                outY = -1;
                return;
            }

            triedDir[dir] = true;
        }
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
        return -1;
    }

    if (isEmpty(x, y)) return -1;
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