
#ifndef AB_H
#define AB_H

#include "State.h"
#include <string>
#include "Player.h"
#include "Pawn.h"

class AB_Pruning
{
public:
	AB_Pruning();
	~AB_Pruning();
	void minimax(State& root, Player&, Player&);
	int min(State&);
	int max(State&);
	void get_new_states(string, State&);
	int value(State& );
	int row_win(State& );
	int all_gone(State& );
	int blocked(State&);
	int attack(State&);
	static bool move_diagonal(int, int[5][3], int, int);
	string name;
};

#endif