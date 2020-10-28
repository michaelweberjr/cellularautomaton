
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "board.h"
#include "creature.h"
#include "ant.h"
#include "doodlebug.h"
#include "mantis.h"

int main()
{
    srand((unsigned int)time(0));
    vector<pair<CreatureID, int>> initialBoard = { make_pair(Ant::getAntID(), 100), make_pair(Mantis::getMantisID(), 2), make_pair(Doodlebug::getDoodlebugID(), 5) };
    Board board = Board(20, 20, initialBoard);

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
