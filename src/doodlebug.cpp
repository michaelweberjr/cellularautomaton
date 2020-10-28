#include "doodlebug.h"
#include "ant.h";
#include "board.h"

CREATURE_STATIC_DATA(DoodleBug);

void DoodleBug::step(Board& board)
{
    bool triedDir[DEGREES_OF_FREEDOM] = { false, false, false, false };
    bool ateAnAnt = false;

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

        int tempX = getX();
        int tempY = getY();
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

        if (board.getCreatureID(tempX, tempY) == Ant::getAntID())
        {
            //std::cout << "Doodle ate and move: (" << getX() << ", " << getY() << ") to (" << tempX << ", " << tempY << ")" << std::endl;
            ateAnAnt = true;
            board.eraseCell(tempX, tempY);
            board.setCell(tempX, tempY, this);
            board.setCell(getX(), getY(), nullptr);
            setX(tempX);
            setY(tempY);
            turnsToStarving = 0;
            break;
        }
        else
        {
            triedDir[dir] = true;
        }
    }

    if (ateAnAnt)
    {
        setMoved();
    }
    else
    {
        if (++turnsToStarving == TURNS_TO_STARVE)
        {
            board.eraseCell(getX(), getY());
            return;
        }
        else
        {
            Creature::step(board);
        }
    }

    if (++turnsToBreeding == TURNS_TO_BREED)
    {
        int tempX, tempY;
        board.getRandomDir(getX(), getY(), false, tempX, tempY);

        if (tempX != -1)
        {
            DoodleBug* newDood = new DoodleBug(tempX, tempY);
            board.setCell(tempX, tempY, newDood);
        }

        turnsToBreeding = 0;
    }
}