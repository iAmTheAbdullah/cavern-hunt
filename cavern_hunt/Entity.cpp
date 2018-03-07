#include "Entity.h"

using namespace std;

// Constructor Function
Entity::Entity() {}
// Destructor Function
Entity::~Entity() {}
// Function which obtains and validates the input from the user
int Entity::player_move(int player_position)
{
	// Asks for input from the user
	cin >> entity_move;

	// Validates the input the user made for the variable "entity_move"
	while ((entity_move != '1') && (entity_move != '2') && (entity_move != '3') && (entity_move != '4')) {
		cout << "Invalid move! Please enter '1' for up, '2' for left, '3' for down or '4' for right: ";
		cin >> entity_move;
	}

	return move_entity(entity_move, player_position);
}
// Moves the Entity to the place it asked to be moved to
int Entity::move_entity(char entity_move, int player_monster_position)
{
	//Switch case to match the input with the appropriate calculation for the new position
	switch (entity_move) {
	case '1': // UP
		player_monster_position -= 10;
		break;
	case '2': // LEFT
		player_monster_position -= 1;
		break;
	case '3': // DOWN
		player_monster_position += 10;
		break;
	case '4': // RIGHT
		player_monster_position += 1;
		break;
	}

	return player_monster_position;
}
// Function which makes the moves for the Monster itself (an AI)
int Entity::move_monster(int monster_position, int player_position)
{
	// Sets the (x,y) coordinates for the Player and Monster respectively
	int y_player = player_position / 10;
	int x_player = player_position % 10;
	int y_monster = monster_position / 10;
	int x_monster = monster_position % 10;

	// Checks if the Player is above the Monster
	if (y_player < y_monster) {
		// Checks if the Player is on the Monster's left or right
		if (x_player < x_monster) return move_entity('1', monster_position);
		else return move_entity('1', monster_position);
	}
	// Checks if the Player is on the same row as the Monster
	else if (y_player == y_monster) {
		// Checks if the Player is on the Monster's left or right
		if (x_player < x_monster) return move_entity('2', monster_position);
		else return move_entity('4', monster_position);
	}
	// Checks if the Player is below the Monster
	else if (y_player > y_monster) {
		// Checks if the Player is on the Monster's left or right
		if (x_player < x_monster) return move_entity('3', monster_position);
		else return move_entity('3', monster_position);
	}
	// Checks if the Player is on the same column as the Monster
	else if (x_player == x_monster) {
		// Checks if the Player is above or below the Monster
		if (y_player < y_monster) return move_entity('1', monster_position);
		else return move_entity('3', monster_position);
	}
}