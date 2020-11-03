#pragma once
#include "creature.h"

class Mantis : public Creature
{
	CREATURE_REGISTER(Mantis, "mantis", 3, [](int x, int y) { return new Mantis(x, y); } );

private:
	static const int TURNS_TO_BREED = 5;
	static const int TURNS_TO_STARVE = 3;

	int turnsToBreeding;
	int turnsToStarving;

public:
	Mantis(int startX, int startY, bool needsToMove = false) : Creature(id, startX, startY, needsToMove), turnsToBreeding(0), turnsToStarving(0) {}

	virtual void step(Board& board);
	virtual char toChar() const { return 'M'; }
};

