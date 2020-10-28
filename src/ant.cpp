#include "ant.h"
#include "board.h"

CREATURE_STATIC_DATA(Ant);

void Ant::step(Board& board)
{
    Creature::step(board);

    if (++turnsToBreeding == TURNS_TO_BREED)
    {
        int tempX, tempY;
        board.getRandomDir(getX(), getY(), tempX, tempY);

        if (tempX != -1)
        {
            Ant* newAnt = new Ant(tempX, tempY);
            board.setCell(id, tempX, tempY);
        }

        turnsToBreeding = 0;
    }
}