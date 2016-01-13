#include"Player.h"


// constructor
Player::Player(){

}

// constructor
Player::Player(string s, bool cond){
	is_AI = cond;
	name = s;
	createPawns();
}

void Player::createPawns(){

	if (name == "Black"){
		for (int i = 1; i < 4; i++){// create 3 pawns
			Pawn temp;
			temp.id = i;
			pawns.push_back(temp);
		}
	}
	else{ // control white pawns
		for (int i = 4; i < 7; i++){// create 3 pawns
			Pawn temp;
			temp.id = i;
			pawns.push_back(temp);
		}
	}
}