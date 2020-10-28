
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "board.h"
#include "creature.h"
#include "ant.h"

int main()
{
    srand(time(0));
    Board board = Board(20, 20, 100, 5);

    Creature::printRegistry();
    cout << endl;

    while (true)
    {
        board.print();

        cout << "Press enter to go to the next turn or 'Q' to quit..." << endl;
        char input = cin.get();
        if (input == 'q' || input == 'Q') break;

        board.step();
    }
}
