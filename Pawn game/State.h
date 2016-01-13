
#include<iostream>
#include<vector>
using namespace std;

class State
{
public:
	State();
	State(int);
	State(int[5][3]);
	~State();
	int value;// value of state
	int alpha;// track max
	int beta;// track min
	vector<State*> leaves;// children nodes
	int board[5][3];
	void setAlpha(int);
	void setBeta(int);
	void display_board();
	void copyBoard(int game[5][3]);
};

