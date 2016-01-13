
#ifndef PL_H
#define PL_H

#include "Pawn.h"
#include<vector>
#include<string>
using namespace std;

class Player
{
public:
	Player();
	vector<Pawn> pawns;// the player's active pawns 
	string name;// either "black" or "white"
	bool is_AI;// set to true if Player is AI
	Player(string s, bool cond);// constructor
	void createPawns();

};


#endif