#include "State.h"
#include<iostream>
#include<vector>
using namespace std;

State::State()
{
}

State::State(int val){
	value = val;
	alpha = -9999999999;// ^^^^
	beta = 99999999999;// ^^^^
}

State::State(int game[5][3]){

	// make a deep copy of the 2D array, store in cur_board
	for (int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			board[i][j] = game[i][j];
		}
	}
}

void State::copyBoard(int game[5][3]){
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++){
			board[i][j] = game[i][j];
		}
	}
}

State::~State()
{
}


void State::display_board()
{
	cout << "*---*---*---*" << endl;
	cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << board[3][0] << " | " << board[3][1] << " | " << board[3][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
	cout << "| " << board[4][0] << " | " << board[4][1] << " | " << board[4][2] << " |" << endl;
	cout << "*---*---*---*" << endl;
}


void State::setAlpha(int a){
	alpha = a;
}

void State::setBeta(int b){
	beta = b;
}
