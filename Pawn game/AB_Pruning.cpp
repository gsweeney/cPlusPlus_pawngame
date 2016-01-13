#include "AB_Pruning.h"
#include<vector>
#include<string>


AB_Pruning::AB_Pruning()
{
}


AB_Pruning::~AB_Pruning()
{
}


// **MINIMAX USES ALPHA BETA PRUNING
//void AB_Pruning::minimax(State& root, Player& blk, Player& wh, int depth){
void AB_Pruning::minimax(State& root, Player& blk, Player& wh){
	// which pawns are the AI's?
	if (blk.is_AI){
		name = "Black";
	} 
	else{
		name = "White";
	}

	root.setAlpha(-999999999);// -infinity
	root.setBeta(999999999);// + infinity


	// get new states of root
	get_new_states("max", root);

	// for each new state
	for (State *leaf : root.leaves){

		// set alpha and beta equal to root state
		leaf->setAlpha(root.alpha);
		leaf->setBeta(root.beta);
		
		// send state to min, creating game tree, return beta value
		//leaf->beta = min(*leaf, depth - 1);
		leaf->beta = min(*leaf);
		// check to see if this state is the best next state
		if (leaf->beta > root.alpha){

			// update value for best next state
			root.alpha = leaf->beta;

			// set root board to leaf board, this gives NEXT BEST MOVE
			root.copyBoard(leaf->board);
		}
	}
}// close minimax


// **MAX function
//int AB_Pruning::max(State& n, int depth){
int AB_Pruning::max(State& n){
	int alpha;

	// generate new states if not a terminal move
	if (n.value != 100 || n.value != -100){
		get_new_states("max", n);
	}

	// base case-- BOTTOM OF TREE OR DEPTH limit reached
	if (n.leaves.size() == 0){//n.leaves.size() == 0 || depth == 0
		n.value = value(n);// return the value of the state
		return n.value;
	}
	// recursive case
	else{
		// for each new state
		for (State *leaf : n.leaves){

			// set alpha and beta equal to parent state
			leaf->setAlpha(n.alpha);
			leaf->setBeta(n.beta);

			// send state to min, creating game tree, return alpha value
			//alpha = min(*leaf, depth - 1);
			alpha = min(*leaf);

			// delete the leaf state (it was created using new in get_new_states)
			//leaf->display_board();// ! test
			delete (leaf);

			// a new maximum alpha found?
			if (alpha > n.alpha){
				n.alpha = alpha;
			}

			// PRUNE IF ALPHA > PARENT'S BETA
			if (n.alpha > n.beta){
				break;// 'prune'- stop searching
			}
		}
	}
	// done searching 
	n.leaves.clear();// ensure vector leaves is empty
	return n.alpha;
}// close max


// **MIN function
//int AB_Pruning::min(State& n, int depth){
int AB_Pruning::min(State& n){
	int beta;

	// if not a terminal state
	if (n.value != 100 || n.value != -100){
		get_new_states("min", n);
	}

	// base case -- BOTTOM OF GAME TREE OR DEPTH LIMIT REACHED
	if (n.leaves.size() == 0){// n.leaves.size() == 0 || depth == 0
		n.value = value(n);// return the value of the state
		return n.value;
	}
	// recursive case
	else{
		// for each new state
		for (State *leaf : n.leaves){

			// set alpha and beta equal to parent state
			leaf->setAlpha(n.alpha);
			leaf->setBeta(n.beta);

			// send state to max, creating game tree, return beta value
			//beta = max(*leaf, depth - 1);
			beta = max(*leaf);

			// delete the leaf state (it was created using new in get_new_states)
			//leaf->display_board();// ! test
			delete (leaf);

			// a new minimum beta found?
			if (beta < n.beta){
				n.beta = beta;
			}

			// PRUNE IF BETA < PARENT'S ALPHA
			if (n.beta < n.alpha){
				break;// 'prune' - stop searching
			}
		}
	}
	// done searching
	n.leaves.clear();// ensure vector leaves is empty
	return n.beta;
}// close min


// given a parent State, create all possible next moves
void AB_Pruning::get_new_states(string s, State& parent){
	int a, b, c, d, e, f;// pawn # we are looking for
	int last_row;
	int row_op;

	if (s == "max"){// in get_new_states, player is max

		if (name == "Black"){// max is AI, AI has black pawns, look for pawns 1,2,3
			a = 1; b = 2; c = 3; last_row = 4; row_op = 1;
			d = 4; e = 5; f = 6;
		}
		else{// AI has white pawns, look for pawns 4,5,6
			a = 4; b = 5; c = 6; last_row = 0; row_op = -1;
			d = 1; e = 2; f = 3;
		}
	}
	if (s == "min"){// in get_new_states, player is min

		if (name == "Black"){// look for pawns 4,5,6
			a = 4; b = 5; c = 6; last_row = 0; row_op = -1;
			d = 1; e = 2; f = 3;
		}
		else{// look for pawns 1,2,3
			a = 1; b = 2; c = 3; last_row = 4; row_op = 1;
			d = 4; e = 5; f = 6;
		}
	}

	if (a == 1){// start creating states starting from the back row, this gives black pawns that are closer to winning a priority
		// loop through game board looking for black pawns
		for (int i = 4; i >= 0; i--){
			for (int j = 2; j >= 0; j--){
				if (parent.board[i][j] == a || parent.board[i][j] == b || parent.board[i][j] == c){// pawn found
					// #1...can pawn attack diagonal left(diagonal int value is d,e,f)
					if (j != 0 && i != 0){
						if (parent.board[i + row_op][j - 1] == d || parent.board[i + row_op][j - 1] == e || parent.board[i + row_op][j - 1] == f){
							// create a new state
							State *st = new State(parent.board);
							st->board[i + row_op][j - 1] = st->board[i][j];
							st->board[i][j] = 0;

							// add new state to parent's leaves
							parent.leaves.push_back(st);
						}
					}
					// #2...can pawn attack diagonal right(diagonal int value is d,e,f)
					if (j != 2 && i != 4){
						if (parent.board[i + row_op][j + 1] == d || parent.board[i + row_op][j + 1] == e || parent.board[i + row_op][j + 1] == f){
							// create a new state
							State *st = new State(parent.board);
							st->board[i + row_op][j + 1] = st->board[i][j];
							st->board[i][j] = 0;

							// add new state to parent's leaves
							parent.leaves.push_back(st);
						}
					}
					// #3....can the pawn move forward (space ahead is 0)
					if (i != last_row && parent.board[i + row_op][j] == 0){
						// create a new state
						State *st = new State(parent.board);
						st->board[i + row_op][j] = st->board[i][j];
						st->board[i][j] = 0;

						// add new state to parent's leaves
						parent.leaves.push_back(st);
					}
				}
			}
		}
	
	}// end black pawns
	if (a == 4){// start creating states from the front of the board, this gives white pawns that are closer to winning a priority
		// loop through game board looking for white pawns
		for (int i = 0; i <= 4; i++){
			for (int j = 0; j <= 2; j++){
				if (parent.board[i][j] == a || parent.board[i][j] == b || parent.board[i][j] == c){// pawn found
					// #1...can pawn attack diagonal left(diagonal int value is d,e,f)
					if (j != 0 && i != 0){
						if (parent.board[i + row_op][j - 1] == d || parent.board[i + row_op][j - 1] == e || parent.board[i + row_op][j - 1] == f){
							// create a new state
							State *st = new State(parent.board);
							st->board[i + row_op][j - 1] = st->board[i][j];
							st->board[i][j] = 0;

							// add new state to parent's leaves
							parent.leaves.push_back(st);
						}
					}
					// #2...can pawn attack diagonal right(diagonal int value is d,e,f)
					if (j != 2 && i != 4){
						if (parent.board[i + row_op][j + 1] == d || parent.board[i + row_op][j + 1] == e || parent.board[i + row_op][j + 1] == f){
							// create a new state
							State *st = new State(parent.board);
							st->board[i + row_op][j + 1] = st->board[i][j];
							st->board[i][j] = 0;

							// add new state to parent's leaves
							parent.leaves.push_back(st);
						}
					}
					// #3....can the pawn move forward (space ahead is 0)
					if (i != last_row && parent.board[i + row_op][j] == 0){
						// create a new state
						State *st = new State(parent.board);
						st->board[i + row_op][j] = st->board[i][j];
						st->board[i][j] = 0;

						// add new state to parent's leaves
						parent.leaves.push_back(st);
					}
				}
			}
		}

	}// end white pawns
}// close get_new_states


// given a state, find the value (of end states only)
int AB_Pruning::value(State& s){

	int value = 0;

	value = row_win(s); // check if a pawn is in opposite row

	if (value == 0){
		value = all_gone(s);// all opponent pawns are gone
	}
	if (value == 0){
		value = blocked(s);// there are no more moves
	}
	// give extra value to states eliminating opponent pawns
	value += attack(s);

	return value;
}// close value


// check if the state has a pawn in the opposite row - a winning state
int AB_Pruning::row_win(State& s){
	
	int value = 0;
	
	// check row 4 for pawns 1,2,3
	for (int i = 1; i < 4; i++){
		if (s.board[4][0] == i || s.board[4][1] == i || s.board[4][2] == i){// pawn is in last row
			if (name =="Black"){// if AI is Black, return 100
				value = 100;
			}
			else{// if AI is White, return -1
				value = -100;
			}	
		}
	}

	// check row 0 for pawns 4,5,6
	for (int i = 4; i < 7; i++){
		if (s.board[0][0] == i || s.board[0][1] == i || s.board[0][2] == i){// pawn is in last row
			if (name == "Black"){// if AI is Black, return -1
				value = -100;
			}
			else{// if AI is White, return +1
				value = +100;
			}
		}
	}

	return value;
}// close row_win


// check if all of opponents pawns are gone in state -  a winning state
int AB_Pruning::all_gone(State& s){
	int value = 0;
	int count_123 = 0;
	int count_456 = 0;

	// loop through game board
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++){
			// check if pawns 1,2,3 are gone
			if (s.board[i][j] == 1 || s.board[i][j] == 2 || s.board[i][j] == 3){
				count_123++;
			}
			// check if pawns 4,5,6 are gone
			if (s.board[i][j] == 4 || s.board[i][j] == 5 || s.board[i][j] == 6){
				count_456++;
			}
		}
	}
	if (name == "Black"){// AI has black pawns
		if (count_123 == 0){// AI loses
			value = -100;
		}
		if (count_456 == 0){// AI wins
			value = 100;
		}
	}
	else{// AI has white pawns
		if (count_123 == 0){// AI wins
			value = 100;
		}
		if (count_456 == 0){// AI loses
			value = -100;
		}
	}

	return value;
}// close all_gone


// check if pawn can move diagonally
bool AB_Pruning::move_diagonal(int num, int board[5][3], int row, int col){
	bool valid = false;

	// check bounds to the left and right of array
	if (col == 0){// check to the right only
		if (num == -1 ){
			if (board[row + num][col + 1] == 1 || board[row + num][col + 1] == 2 || board[row + num][col + 1] == 3){
				valid = true;
			}
		}
		if (num == 1){
			if (board[row + num][col + 1] == 4 || board[row + num][col + 1] == 5 || board[row + num][col + 1] == 6){
				valid = true;
			}
		}
	}
	else if (col == 2){// check to the left only
		if (num == -1){
			if (board[row + num][col - 1] == 1 || board[row + num][col - 1] == 2 || board[row + num][col - 1] == 3){
				valid = true;
			}
		}
		if (num == 1){
			if (board[row + num][col - 1] == 4 || board[row + num][col - 1] == 5 || board[row + num][col - 1] == 6){
				valid = true;
			}
		}
	}
	else{// col is 1, check both directions
		if (num == -1){
			if (board[row + num][col - 1] == 1 || board[row + num][col - 1] == 2 || board[row + num][col - 1] == 3 ||
				board[row + num][col + 1] == 1 || board[row + num][col + 1] == 2 || board[row + num][col + 1] == 3){
				valid = true;
			}
		}
		if (num == 1){
			if (board[row + num][col - 1] == 4 || board[row + num][col - 1] == 5 || board[row + num][col - 1] == 6 ||
				board[row + num][col + 1] == 4 || board[row + num][col + 1] == 5 || board[row + num][col + 1] == 6){
				valid = true;
			}
		}
	}

	return valid;
}// close move_diagonal


// check if pawn can move anywhere - opponent cannot move is a winning state
int AB_Pruning::blocked(State& s){
	int value = 0;

	int move_123 = 0;
	int move_456 = 0;

	// loop through game board
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++){
			// check if pawns 1,2,3 can move
			if (s.board[i][j] == 1 || s.board[i][j] == 2 || s.board[i][j] == 3){
				if (i != 4 && s.board[i+1][j] == 0 || move_diagonal(1, s.board, i, j)){// if space in front is 0, diagonals are either 4,5,6
					move_123++;
				}
			}
			// check if pawns 4,5,6 can move
			if (s.board[i][j] == 4 || s.board[i][j] == 5 || s.board[i][j] == 6){
				if (i != 0 && s.board[i - 1][j] == 0 || move_diagonal(-1, s.board, i, j)){// if space in front is 0, diagonals are either 1,2,3
					move_456++;
				}
			}
		}
	}

	if (name == "Black"){// AI has black pawns
		if (move_123 == 0 && move_456 != 0){// AI loses
			value = -100;
		}
		if (move_123 == 0 && move_456 == 0){// AI wins
			value = 100;
		}
	}
	else{// AI has white pawns
		if (move_123 == 0 && move_456 == 0){// AI wins
			value = 100;
		}
		if (move_123 != 0 && move_456 == 0){// AI loses
			value = -100;
		}
	}

	return value;
}// close blocked


// give state a higher value if it has less opponent pawns
int AB_Pruning::attack(State& s){
	int value = 30;// start at 30, decrease if enemy found
	int e1, e2, e3;//enemy pawns
	int total_enemies = 0;

	// the lower # of enemy pawns, the higher the value
	if(name == "Black"){
		// want a low number of white pawns 4 5 6
		e1 = 4; e2 = 5; e3 = 6;
	}
	else{
		// want a low number of black pawns 1 2 3
		e1 = 1; e2 = 2; e3 = 3;
	}


	// loop through state
	for(int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++){
			// if enemy pawn found, value - 10
			if (s.board[i][j] == e1 || s.board[i][j] == e2|| s.board[i][j] == e3){
				value -= 10;
			}
		}
	}
	return value;
}// close attack