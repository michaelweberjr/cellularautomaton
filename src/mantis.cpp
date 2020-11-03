#include "mantis.h"
#include "board.h"
#include "ant.h"

CREATURE_STATIC_DATA(Mantis);

void Mantis::step(Board& board)
{
    int tempX = 0, tempY = 0;

    int dir = 4;
    while(dir > 1 && tempX != -1)
        board.getRandomDir(getX(), getY(), tempX, tempY, Ant::getAntID(), false, dir--);

    if (tempX != -1)
    {
        //std::cout << "Mantis eat and move[" << getID() << "]: (" << getX() << ", " << getY() << ") to (" << tempX << ", " << tempY << ")" << std::endl;
        setMoved();
        board.moveCell(getX(), getY(), tempX, tempY);
        setX(tempX);
        setY(tempY);
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
        board.getRandomDir(getX(), getY(), tempX, tempY);

        if (tempX != -1)
        {
            board.setCell(id, tempX, tempY);
        }

        turnsToBreeding = 0;
    }
}
