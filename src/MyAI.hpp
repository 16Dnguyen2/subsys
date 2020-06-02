// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Jian Li
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class MyAI : public Agent
{
public:
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================

	int** board;
	int remTiles;
	bool foundMine = false;

	//Functions
    MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY );
	~MyAI();
    Action getAction ( int number ) override;

	void nearCheck(int x, int y, int* nearTiles);
	int boundCheck(int x, int y);
	void modXY(int* x, int* y, int i);
	
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
