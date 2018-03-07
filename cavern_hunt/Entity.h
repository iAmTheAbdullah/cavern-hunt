#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity {
public:
	// Constructor
	Entity();
	// Destructor
	~Entity();
	// Function Prototypes
	int player_move(int player_position);
	int move_entity(char entity_move, int player_monster_position);
	int move_monster(int player_position, int monster_position);

private:
	char entity_move;
};

#endif