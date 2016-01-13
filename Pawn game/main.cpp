#include <iostream>
#include "Pawntest.h"


using namespace std;

int main()
{
	cout << "Welcome to Pawn game world!" << endl;
	cout << "\twhite pawns move first" << endl;
	cout << "\tblack pawns move second" << endl;
	/*
		default constructor for class Pawntest.
			1. sets player types (AI or Not)
			2. ...then sets the game board
	*/
	Pawntest test;
	
	// start the game
	cout << "\npawns 1,2,3 are black pawns and pawns 4,5,6 are white pawns." << endl;
	test.display_board();
	cout << endl;
	bool game_done = false;// game control

	// game loop
	while (game_done == false)
	{
		// white pawns move
		test.command_list(test.white_player);// if human player
		test.display_board();
		game_done = test.is_game_done(test.white_player.name);
		cout << endl;

		// check if black pawns have won
		if (game_done == true)
			break;

		// black pawns move
		test.command_list(test.black_player);// if human player
		test.display_board();
		game_done = test.is_game_done(test.black_player.name);
		cout << endl;
	}

}