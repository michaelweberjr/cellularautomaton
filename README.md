# Cellular Automaton
Version 2.0 of the Doodlebug homework project from NYU Tandom Bridge program: [hw13](https://github.com/michaelweberjr/TandomBridge/blob/main/mw4732_hw13.cpp)
This features a fully automated Creature class for registering creatures and factory method for creating new ones.

This version includes "3" different types of creatures:
* Ant: moves in one random direction every turn and breeds a new ant into a free adjacant cell every 3 turns
* Mantis: does not move, instead it will jump from it's location to up to four steps away to eat an ant. It breeds every 5th turn.
* Doodlebug: first trys to move and eat ant or a mantis. If it cannot then moves like an ant. Every 3rd turn the doodlebug produces a larva. 
* The larve does nothing but will die if there is no adjacant doodlebug and will turn into a doodlebug after three turns
* The doodlebug turns into a nesting doodlebug and will stay adjacant to the larva until it turns into a doodlebug
