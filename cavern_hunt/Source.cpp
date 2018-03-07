#include <iostream>
#include "Entity.h"

using namespace std;

// Global variables
char grid[10][10]; // The grid for the game
char player = 'P', monster = 'M', special_item = 'T', border = '*'; // These are used for being displayed on the console
int x, y, x_player, y_player, x_monster, y_monster, x_special_item, y_special_item; // The (x,y) coordinates for the placeholders, the Player, the Monster and the Special Item respectively
int no_of_turns; // A score for the player
int run, turn, end_game, continue_game; // Variables which decide how the game is played
char Input; // Takes the input from the user for the Player
Entity Player, Monster; // Player and Monster objects created from the Entity Class

// Function Prototypes
void cavern_hunt();
void initialise_grid();
void draw_grid();
void found_item();
void captured_or_hit_grid();
int send_to_position(int entity_type);
void update_position(int entity_type, int position);

// Main function of the program
int main()
{
	int sentValue = 1; // A sentinel value for the whole program
	char choice; // A choice for the menu

	while (sentValue == 1) {
		cout << "WELCOME TO CAVERN HUNT! CHOOSE ONE OF THE FOLLOWING OPTIONS BELOW" << endl;
		cout << "\t1. Start the game" << endl;
		cout << "\t0. Quit" << endl;

		cout << "Enter what you would like to do: ";
		cin >> choice;

		while ((choice != '1') && (choice != '0')) {
			cout << "Wrong Option! Please choose one of the following options available: ";
			cin >> choice;
		}

		system("cls");

		switch (choice) {
		case '1':
			cavern_hunt();
			break;
		case '0':
			sentValue = 0;
			break;
		}
	}

	return 0;
}
// The main game
void cavern_hunt()
{
	no_of_turns = 0, run = 1, turn = 1, end_game = 0, continue_game = 1;

	initialise_grid();
	draw_grid();

	while (run == 1) {
		cout << "Turn: " << no_of_turns << endl;
		if (turn == 1) {
			turn = 0;
			cout << "Enter '1' to go up, '2' to go left, '3' to go down or '4' to go right: ";
			update_position(1, Player.player_move(send_to_position(1)));
		}
		else {
			turn = 1;
			no_of_turns++;
			update_position(2, Monster.move_monster(send_to_position(2), send_to_position(1)));
			system("cls");
		}
		system("cls");
		draw_grid();
		found_item();
		captured_or_hit_grid();
	}
}
// Initialises the grid
void initialise_grid()
{
	grid[y_player][x_player] = ' ';
	grid[y_monster][x_monster] = ' ';
	grid[y_special_item][x_special_item] = ' ';
	// Initialises the upper and lower parts of the grid borders
	for (int i = 0; i < 10; i++) {
		grid[0][i] = border;
		grid[10 - 1][i] = border;
	}
	// Initialises the left and right parts of the grid borders
	for (int j = 1; j < 10 - 1; j++) {
		grid[j][0] = border;
		grid[j][10 - 1] = border;
	}
	// Assigning the positions for the Special Item, the Player and the Monster
	x_player = 1;
	y_player = 1;
	x_monster = 10 - 2;
	y_monster = 10 - 2;
	x_special_item = 1 + (rand() % 8);
	y_special_item = 1 + (rand() % 8);
}
// Draws the grid onto the console
void draw_grid()
{
	grid[y_player][x_player] = player;
	grid[y_monster][x_monster] = monster;
	grid[y_special_item][x_special_item] = special_item;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << grid[i][j] << ' ';
		}
		cout << endl;
	}
}
// Checks if the Player has found the Special Item
void found_item()
{
	if ((y_player == y_special_item) && (x_player == x_special_item)) {
		if (end_game == 1) {
			if (continue_game == 1) end_game = 0;
			run = 0;
		}
		else {
			cout << "YOU HAVE FOUND THE SPECIAL ITEM! YOU HAVE WON THE GAME!" << endl;
			cout << "You found the special item after " << no_of_turns << "th turn.\n" << endl;
			if (!continue_game) end_game = 1;
			run = 0;
		}
	}
}
// Checks if the Player has been captured by the Monster
void captured_or_hit_grid()
{
	// Checks if the player has hit the wall
	if ((y_player == 0) || (y_player == 10 - 1) || (x_player == 0) || (x_player == 10 - 1)) {
		cout << "You have gone outside the grid! Game Over!" << endl;
		cout << "You lost after your " << no_of_turns << "th turn.\n" << endl;
		run = 0;
		if (end_game == 0) end_game = 1;
	}
	// Checks if the player and monster are in the same position on the grid
	else if ((y_monster == y_player) && (x_monster == x_player)) {
		if (end_game == 1) {
			if (continue_game == 1) end_game = 0;
			run = 0;
		}
		else {
			cout << "You have been captured! Game Over!" << endl;
			cout << "The monster caught you after your " << no_of_turns << "th turn.\n" << endl;
			if (!continue_game) end_game = 1;
			run = 0;
		}
	}
}
// Gets the current position of the player and monster which get converted into positions on the grid
int send_to_position(int entity_type)
{
	if (entity_type == 1) {
		x = x_player;
		y = y_player;
	}
	else {
		x = x_monster;
		y = y_monster;
	}

	int position = (y * 10) + x;

	return position;
}
// Updates the position of the player and monster
void update_position(int entity_type, int position)
{
	y = position / 10;
	x = position % 10;

	if (entity_type == 1) {
		grid[y_player][x_player] = ' ';
		y_player = y;
		x_player = x;
	}
	else {
		grid[y_monster][x_monster] = ' ';
		y_monster = y;
		x_monster = x;
	}
}