#include <iostream>

#include "creature.h"
#include "board.h"

Creature::RegistryList& Creature::getRegistry()
{
    static RegistryList registry;
    return registry;
}

CreaturePriority*& Creature::getPriorityList()
{
    static CreaturePriority *head = nullptr;
    return head;
}

CreatureID Creature::registerCreatureType(std::string name, unsigned int priority, FactoryPr pre)
{
    RegistryList& registry = getRegistry();
    if (registry.size() == 28)
    {
        std::cout << "Exceeded creature registry size of: 28" << std::endl;
        exit(2);
    }

    registry.emplace_back(std::make_pair(name, pre));
    CreatureID id = (CreatureID)(1 << (registry.size()-1));
    addPriority(id, priority);
    return id;
}

void Creature::addPriority(CreatureID id, unsigned int priority)
{
    CreaturePriority*& head = getPriorityList();
    if (head == nullptr)
    {
        head = new CreaturePriority(priority, id);
    }
    else if (head->priority > priority)
    {
        auto temp = new CreaturePriority(priority, id);
        temp->next = head;
        head = temp;
    }
    else
    {
        CreaturePriority* curr = head;
        while (curr != nullptr)
        {
            if (curr->priority == priority)
            {
                curr->ids |= id;
                break;
            }
            else if (curr->next == nullptr)
            {
                curr->next = new CreaturePriority(priority, id);
                break;
            }
            else if (curr->priority < priority && priority < curr->next->priority)
            {
                CreaturePriority* temp = new CreaturePriority(priority, id);
                temp->next = curr->next;
                curr->next = temp;
                break;
            }

            curr = curr->next;
        }
    }
}

Creature* Creature::factory(CreatureID id, int x, int y)
{
    auto registry = getRegistry();
    int ind = -1;
    while (id > 0)
    {
        id >>= 1;
        ind++;
    }
    if(registry.size() <= ind)
        throw new std::string("Cannot find creautre of type id: ");
    return registry[ind].second(x, y);
}

void Creature::step(Board& board)
{
    needsToMove = false;

    int tempX, tempY;
    board.getRandomDir(x, y, tempX, tempY);

    if (tempX != -1)
    {
        //std::cout << "Basic move[" << getID() << "]: (" << getX() << ", " << getY() << ") to (" << tempX << ", " << tempY << ")" << std::endl;
        board.moveCell(x, y, tempX, tempY);
        x = tempX;
        y = tempY;
    }
}

using namespace std;
void Creature::printRegistry()
{
    auto registry = getRegistry();
    cout << "Registry size: " << registry.size() << endl;
    for (int i = 1; i <= registry.size(); i++)
    {
        cout << "ID[" << indexToID(i) << "]: " << registry[i-1].first << endl;
    }
    cout << "Priority List: " << endl;
    auto list = getPriorityList();
    while (list != nullptr)
    {
        cout << list->priority << ": ";
        for (int i = 1; i <= registry.size(); i++) 
            if((list->ids & indexToID(i)) == indexToID(i))
                cout << indexToID(i) << " ";
        cout << endl;
        list = list->next;
    }
}