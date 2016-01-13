

#include <iostream>
#include <vector>
#include <string>
#include "AB_Pruning.h"
#include "Pawn.h"
#include "Player.h"


using namespace std;

class Pawntest
{
public:
	Pawntest();
	void set_game_board();
	void display_board();
	void command_list(Player&);
	bool move_pawn(Player&, int);
	bool attack_pawn(Player&, int, int);
	bool is_game_done(string);
	void set_players();
	void update_game(int[5][3], Player&);
	bool no_more_moves(string);
public:
	int game_board[5][3];// game board is a 5x3 2D int array
	AB_Pruning search;
	Player black_player;
	Player white_player;

};

// Pawntest constructor
Pawntest::Pawntest(){
	set_players();
	set_game_board();
}

// which player is AI?
void Pawntest::set_players(){

	bool valid = false;
	int input;
	string cpu;

	while (!valid){

		cout << "\nEnter pawns controlled by A.I. (white or black): ";
		cin >> cpu;
		if (cpu == "white"){
			black_player = Player("Black", false);
			white_player = Player("White", true);
			valid = true;
		}
		else if (cpu == "black"){
			black_player = Player("Black", true);
			white_player = Player("White", false);
			valid = true;
		}
		else{
			cout << "Please enter either 'white' or 'black'" << endl;
		}
		
	}// close validation
}

void Pawntest::set_game_board()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			game_board[i][j] = 0; //0 means empty in that position
		}
	}

	black_player.pawns[0].location_row = 0;
	black_player.pawns[0].location_col = 0;
	black_player.pawns[1].location_row = 0;
	black_player.pawns[1].location_col = 1;
	black_player.pawns[2].location_row = 0;
	black_player.pawns[2].location_col = 2;

	game_board[0][0] = 1;
	game_board[0][1] = 2;
	game_board[0][2] = 3;

	white_player.pawns[0].location_row = 4;
	white_player.pawns[0].location_col = 0;
	white_player.pawns[1].location_row = 4;
	white_player.pawns[1].location_col = 1;
	white_player.pawns[2].location_row = 4;
	white_player.pawns[2].location_col = 2;

	game_board[4][0] = 4;
	game_board[4][1] = 5;
	game_board[4][2] = 6;
}


void Pawntest::display_board()
{
	cout << "*---*---*---*" << endl;
	cout << "| " << game_board[0][0] << " | " << game_board[0][1] << " | " << game_board[0][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << game_board[1][0] << " | " << game_board[1][1] << " | " << game_board[1][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << game_board[2][0] << " | " << game_board[2][1] << " | " << game_board[2][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << game_board[3][0] << " | " << game_board[3][1] << " | " << game_board[3][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << game_board[4][0] << " | " << game_board[4][1] << " | " << game_board[4][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
}


void Pawntest::update_game(int update[5][3], Player& p){
	// player's active pawns?

	// set them all to dead
	for(Pawn &pawn: p.pawns){
		pawn.death = true;
	}

	// update board
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++){
			game_board[i][j] = update[i][j];
			
			//update pawns
			for (Pawn &pawn : p.pawns){
				if (pawn.id == game_board[i][j]){
					
					pawn.death = false;
					pawn.location_row = i;
					pawn.location_col = j;
				}
				
			}

		}
	}
	
}

void Pawntest::command_list(Player& p)
{
	cout << p.name << "'s turn" << endl;

	if (p.is_AI){
		//get the current game state - the root of the game tree
		State root = State(game_board);

		// depth of search tree
		//int depth = 50;

		// get the next move for AI
		//search.minimax(root, black_player, white_player, depth);
		search.minimax(root, black_player, white_player);


		// new move found 
		update_game(root.board, p);
	}
	else{// let user play the game

		bool turn_end = false;
		bool success = false;

		while (turn_end == false)
		{
			int pawn_id = 0;
			success = false;
			while (success == false)
			{
				if (p.name == "Black")
				{
					cout << "Select the pawn to move or attack (1 ~ 3)" << endl;
					cin >> pawn_id;
					if (pawn_id == 1 || pawn_id == 2 || pawn_id == 3)
						success = true;
					else
						cout << "Invalid input" << endl;
				}
				else if (p.name == "White")
				{
					cout << "Select the pawn to move or attack (4 ~ 6)" << endl;
					cin >> pawn_id;
					if (pawn_id == 4 || pawn_id == 5 || pawn_id == 6)
						success = true;
					else
						cout << "Invalid input" << endl;
				}

			}

			int command;
			int direction;
			success = false;
			while (success == false)
			{

				cout << "Select the command (1:move, 2:attack)" << endl;

				cin >> command;
				if (command == 1)
					success = true;
				else if (command == 2)
				{
					cout << "select the attack direction (1:left, 2:right)" << endl;
					cin >> direction;
					if (direction == 1 || direction == 2)
						success = true;
					else
						cout << "Invalid input" << endl;
				}
				else
					cout << "Invalid input" << endl;
			}

			///command starts
			bool command_work = false;

			if (command == 1)
			{
				command_work = move_pawn(p, pawn_id);
				if (command_work == true)
					turn_end = true;
				else
					cout << "The command is invalid" << endl;
			}
			else if (command == 2)
			{
				command_work = attack_pawn(p, pawn_id, direction);
				if (command_work == true)
					turn_end = true;
				else
					cout << "The command is invalid" << endl;
			}
		}
	}
}

bool Pawntest::move_pawn(Player& p, int pawn_id)
{
	if (p.name == "Black")
	{
		int pawn_index = pawn_id - 1;
		int current_row = p.pawns[pawn_index].location_row;
		int current_col = p.pawns[pawn_index].location_col;

		if (p.pawns[pawn_index].death == true)
			return false;
		if (game_board[current_row + 1][current_col] != 0)
			return false;

		p.pawns[pawn_index].location_row += 1;
		game_board[current_row + 1][current_col] = pawn_id;
		game_board[current_row][current_col] = 0;
		return true;
	}
	else if (p.name == "White")
	{
		int pawn_index = pawn_id - 4;
		int current_row = p.pawns[pawn_index].location_row;
		int current_col = p.pawns[pawn_index].location_col;

		if (p.pawns[pawn_index].death == true)
			return false;
		if (game_board[current_row - 1][current_col] != 0)
			return false;

		p.pawns[pawn_index].location_row -= 1;
		game_board[current_row - 1][current_col] = pawn_id;
		game_board[current_row][current_col] = 0;
		return true;
	}
}

bool Pawntest::attack_pawn(Player& p, int pawn_id, int direction) //direct 1 = left direct 2 = right
{
	if (p.name == "Black")
	{
		int pawn_index = pawn_id - 1;
		int current_row = p.pawns[pawn_index].location_row;
		int current_col = p.pawns[pawn_index].location_col;
		if (p.pawns[pawn_index].death == true)
			return false;

		if (direction == 1) //attack left
		{
			int attack_row = current_row + 1;
			int attack_col = current_col - 1;
			if (attack_row < 0 || attack_row > 4 || attack_col < 0 || attack_col > 2)
				return false;
			else
			{
				if (game_board[attack_row][attack_col] == 4 || game_board[attack_row][attack_col] == 5 || game_board[attack_row][attack_col] == 6)
				{
					if (game_board[attack_row][attack_col] == 4)
						white_player.pawns[0].death = true;
					if (game_board[attack_row][attack_col] == 5)
						white_player.pawns[1].death = true;
					if (game_board[attack_row][attack_col] == 6)
						white_player.pawns[2].death = true;

					p.pawns[pawn_index].location_row = attack_row;
					p.pawns[pawn_index].location_col = attack_col;
					game_board[current_row][current_col] = 0;
					game_board[attack_row][attack_col] = pawn_id;

					return true;
				}
				else
					return false;
			}
		}
		else if (direction == 2)
		{
			int attack_row = current_row + 1;
			int attack_col = current_col + 1;
			if (attack_row < 0 || attack_row > 4 || attack_col < 0 || attack_col > 2)
				return false;
			else
			{
				if (game_board[attack_row][attack_col] == 4 || game_board[attack_row][attack_col] == 5 || game_board[attack_row][attack_col] == 6)
				{
					if (game_board[attack_row][attack_col] == 4)
						white_player.pawns[0].death = true;
					if (game_board[attack_row][attack_col] == 5)
						white_player.pawns[1].death = true;
					if (game_board[attack_row][attack_col] == 6)
						white_player.pawns[2].death = true;

					p.pawns[pawn_index].location_row = attack_row;
					p.pawns[pawn_index].location_col = attack_col;
					game_board[current_row][current_col] = 0;
					game_board[attack_row][attack_col] = pawn_id;

					return true;
				}
				else
					return false;
			}
		}

	}
	else if (p.name == "White")
	{
		int pawn_index = pawn_id - 4;
		int current_row = p.pawns[pawn_index].location_row;
		int current_col = p.pawns[pawn_index].location_col;
		if (p.pawns[pawn_index].death == true)
			return false;

		if (direction == 1) //attack left
		{
			int attack_row = current_row - 1;
			int attack_col = current_col - 1;
			if (attack_row < 0 || attack_row > 4 || attack_col < 0 || attack_col > 2)
				return false;
			else
			{
				if (game_board[attack_row][attack_col] == 1 || game_board[attack_row][attack_col] == 2 || game_board[attack_row][attack_col] == 3)
				{
					if (game_board[attack_row][attack_col] == 1)
						black_player.pawns[0].death = true;
					if (game_board[attack_row][attack_col] == 2)
						black_player.pawns[1].death = true;
					if (game_board[attack_row][attack_col] == 3)
						black_player.pawns[2].death = true;

					p.pawns[pawn_index].location_row = attack_row;
					p.pawns[pawn_index].location_col = attack_col;
					game_board[current_row][current_col] = 0;
					game_board[attack_row][attack_col] = pawn_id;

					return true;
				}
				else
					return false;
			}
		}
		else if (direction == 2)
		{
			int attack_row = current_row - 1;
			int attack_col = current_col + 1;
			if (attack_row < 0 || attack_row > 4 || attack_col < 0 || attack_col > 2)
				return false;
			else
			{
				if (game_board[attack_row][attack_col] == 1 || game_board[attack_row][attack_col] == 2 || game_board[attack_row][attack_col] == 3)
				{
					if (game_board[attack_row][attack_col] == 1)
						black_player.pawns[0].death = true;
					if (game_board[attack_row][attack_col] == 2)
						black_player.pawns[1].death = true;
					if (game_board[attack_row][attack_col] == 3)
						black_player.pawns[2].death = true;

					p.pawns[pawn_index].location_row = attack_row;
					p.pawns[pawn_index].location_col = attack_col;
					game_board[current_row][current_col] = 0;
					game_board[attack_row][attack_col] = pawn_id;

					return true;
				}
				else
					return false;
			}
		}
	}
}

bool Pawntest::no_more_moves(string last_move){

	bool game_over = false;
	int move_123 = 0;
	int move_456 = 0;

	// check if all pawns are blocked FOR EITHER PLAYER
	// loop through game board
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++){
			// check if black pawns 1,2,3 can move
			if (game_board[i][j] == 1 || game_board[i][j] == 2 || game_board[i][j] == 3){
				if (i != 4 && game_board[i + 1][j] == 0 || AB_Pruning::move_diagonal(1, game_board, i, j)){// if space in front is 0, diagonals are either 4,5,6
					move_123++;
				}
			}
			// check if white pawns 4,5,6 can move
			if (game_board[i][j] == 4 || game_board[i][j] == 5 || game_board[i][j] == 6){
				if (i != 0 && game_board[i - 1][j] == 0 || AB_Pruning::move_diagonal(-1, game_board, i, j)){// if space in front is 0, diagonals are either 1,2,3
						move_456++;
				}
			}
		}
	}
	

	if (black_player.is_AI){// AI has black pawns
		if (move_123 == 0 && move_456 != 0){// AI loses
			game_over = true;
			cout << white_player.name << " player won!" << endl;
		}
		if (move_123 == 0 && move_456 == 0 || move_123 != 0 && move_456 == 0){// AI wins
			game_over = true;
			cout << last_move << " player won!" << endl;
		}
	}
	else{// AI has white pawns
		if (move_123 == 0 && move_456 == 0 || move_123 == 0 && move_456 != 0){// AI wins
			game_over = true;
			cout << last_move << " player won!" << endl;
		}
		if (move_123 != 0 && move_456 == 0 ){// AI loses
			game_over = true;
			cout << black_player.name << " player won!" << endl;
		}
	}
	
	return game_over;
}

// check game status
bool Pawntest::is_game_done(string s)
{
	int num_black_death = 0;
	int num_white_death = 0;
	int black_reach = 0;
	int white_reach = 0;
	for (unsigned int i = 0; i < 3; i++)
	{
		if (black_player.pawns[i].death == true)
		{
			num_black_death++;
		}
		if (white_player.pawns[i].death == true)
		{
			num_white_death++;
		}

		if (black_player.pawns[i].location_row == 4)
			black_reach = 1;
		if (white_player.pawns[i].location_row == 0)
			white_reach = 1;
	}
	if (num_black_death == 3)
	{
		cout << "White player won!" << endl;
		return true;
	}
	if (num_white_death == 3)
	{
		cout << "Black player won!" << endl;
		return true;
	}
	if (black_reach == 1)
	{
		cout << "Black player won!" << endl;
		return true;
	}
	if (white_reach == 1)
	{
		cout << "White player won!" << endl;
		return true;
	}
	if (no_more_moves(s)){
		
		return true;
	}

	return false;
}