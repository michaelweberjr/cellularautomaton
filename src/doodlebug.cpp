#include "doodlebug.h"
#include "ant.h"
#include "mantis.h"
#include "board.h"
#include <iostream>
CREATURE_STATIC_DATA(Doodlebug);

void Doodlebug::step(Board& board)
{
    int tempX, tempY;
    ++turnsToBreeding;
    ++turnsToStarving;

    board.getRandomDir(getX(), getY(), tempX, tempY, DoodlebugLarva::getDoodlebugLarvaID(), false);
    if (tempX != -1)
    {
        board.setCell(DoodlebugNesting::getDoodlebugNestingID(), getX(), getY());
        reinterpret_cast<DoodlebugNesting*>(board.getCell(getX(), getY()))->setStarving(turnsToStarving);
        reinterpret_cast<DoodlebugNesting*>(board.getCell(getX(), getY()))->setBreeding(turnsToBreeding);
        board.getCell(getX(), getY())->reset();
        return;
    }
    
    board.getRandomDir(getX(), getY(), tempX, tempY, Ant::getAntID() | Mantis::getMantisID());

    if (tempX != -1)
    {
        //std::cout << "Doodle eat and move[" << getID() << "]: (" << getX() << ", " << getY() << ") to (" << tempX << ", " << tempY << ")" << std::endl;
        setMoved();
        board.moveCell(getX(), getY(), tempX, tempY);
        setX(tempX);
        setY(tempY);
        turnsToStarving = 0;
    }
    else
    {
        if (turnsToStarving == TURNS_TO_STARVE)
        {
            board.eraseCell(getX(), getY());
            return;
        }
        else
        {
            Creature::step(board);
        }
    }

    if (turnsToBreeding == TURNS_TO_BREED)
    {
        board.getRandomDir(getX(), getY(), tempX, tempY);

        if (tempX != -1)
        {
            board.setCell(DoodlebugLarva::getDoodlebugLarvaID(), tempX, tempY);
        }

        turnsToBreeding = 0;
    }
}

CREATURE_STATIC_DATA(DoodlebugNesting);

void DoodlebugNesting::step(Board& board)
{
    int tempX, tempY;
    setMoved();
    ++turnsToBreeding;
    ++turnsToStarving;
    board.getRandomDir(getX(), getY(), tempX, tempY, DoodlebugLarva::getDoodlebugLarvaID(), false);

    if (tempX == -1)
    {
        board.setCell(Doodlebug::getDoodlebugID(), getX(), getY());
        reinterpret_cast<Doodlebug*>(board.getCell(getX(), getY()))->setStarving(turnsToStarving);
        reinterpret_cast<Doodlebug*>(board.getCell(getX(), getY()))->setBreeding(turnsToBreeding);
        board.getCell(getX(), getY())->reset();
        return;
    }

    if (tempX != -1)
    {
        // for any square that a doodlebug is adjacent to a Larva then there are only two squares to move to
        int dir = (rand() % 2 == 0) ? -1 : 1;
        if (tempX == getX())
        {
            if (board.getCreatureID(getX() + dir, getY()) & (Ant::getAntID() | Mantis::getMantisID()))
            {
                tempX = getX() + dir;
                tempY = getY();
            }
            else if (board.getCreatureID(getX() - dir, getY()) & (Ant::getAntID() | Mantis::getMantisID()))
            {
                tempX = getX() - dir;
                tempY = getY();
            }
            else
            {
                tempX = -1;
            }
        }
        else if (tempY == getY())
        {
            if (board.getCreatureID(getX(), getY() + dir) & (Ant::getAntID() | Mantis::getMantisID()))
            {
                tempX = getX();
                tempY = getY() + dir;
            }
            else if (board.getCreatureID(getX(), getY() - dir) & (Ant::getAntID() | Mantis::getMantisID()))
            {
                tempX = getX();
                tempY = getY() - dir;
            }
            else
            {
                tempX = -1;
            }
        }
        else
        {
            int dirX = getX() < tempX ? 1 : -1;
            int dirY = getY() < tempY ? 1 : -1;
            CreatureID idX = board.getCreatureID(getX() + dirX, getY()) & (Ant::getAntID() | Mantis::getMantisID());
            CreatureID idY = board.getCreatureID(getX(), getY() + dirY) & (Ant::getAntID() | Mantis::getMantisID());
            if (dir == 1)
            {
                if (idX)
                {
                    tempX = getX() + dirX;
                    tempY = getY();
                }
                else if (idY)
                {
                    tempX = getX();
                    tempY = getY() + dirY;
                }
                else tempX = -1;
            }
            else
            {
                if (idY)
                {
                    tempX = getX();
                    tempY = getY() + dirY;
                }
                else if (idX)
                {
                    tempX = getX() + dirX;
                    tempY = getY();
                }
                else tempX = -1;
            }
        }
    }

    if (tempX != -1)
    {
        std::cout << "Doodle eat and move[" << getID() << "]: (" << getX() << ", " << getY() << ") to (" << tempX << ", " << tempY << ")" << std::endl;
        board.moveCell(getX(), getY(), tempX, tempY);
        setX(tempX);
        setY(tempY);
        turnsToStarving = 0;
    }
    else if (turnsToStarving == TURNS_TO_STARVE)
    {
        board.eraseCell(getX(), getY());
        return;
    }
}

CREATURE_STATIC_DATA(DoodlebugLarva);

void DoodlebugLarva::step(Board& board)
{
    setMoved();

    int tempX, tempY;
    board.getRandomDir(getX(), getY(), tempX, tempY, DoodlebugNesting::getDoodlebugNestingID(), false);

    if (tempX == -1)
    {
        board.eraseCell(getX(), getY());
        return;
    }

    if (++turnsToHatch == TURNS_TO_HATCH)
    {
        board.setCell(Doodlebug::getDoodlebugID(), getX(), getY());
    }
}