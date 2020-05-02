// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"

MyAI::MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ) : Agent()
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
	
	rowDimension = _rowDimension;
    colDimension = _colDimension;
	totalMines   = _totalMines;
	
	board = new int*[rowDimension];
	for(int x = 0; x < rowDimension; ++x)
		board[x] = new int[colDimension];
	
	for(int x = 0; x < rowDimension; ++x)
		for(int y = 0; y < colDimension; ++y)
			board[x][y] = -1;
	agentX = _agentX;
	agentY = _agentY;
	board[_agentX][_agentY] = 0;
	remTiles = (rowDimension * colDimension) - 1;
	
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

MyAI::~MyAI(){
	for(int y = 0; y < colDimension; ++y)
		delete[] board[y];
	delete[] board;
}

Agent::Action MyAI::getAction( int number )
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
	
	if(remTiles == totalMines)
		return {LEAVE,-1,-1};
	board[agentX][agentY] = number;
	
	/*
	for(int x2 = 0; x2 < rowDimension; ++x2){
		for(int y2 = 0; y2 < colDimension; ++y2)
			cout << board[x2][y2] << "	";
		cout << endl;
		}
	cout << number << endl;
	*/
	
	//Unveil zeros	
	for(int x = 0; x < rowDimension; ++x){
		for(int y = 0; y < colDimension; ++y){
			int nearTiles[10];
			nearCheck(x, y, nearTiles);
			
			for(int i = 0; i < 10; ++i){
				if(nearTiles[i] == -1)
					continue;
				
				if(nearTiles[i] == 0 && board[x][y] == -1){									
					agentX = x;
					agentY = y;
					--remTiles;
					return {UNCOVER, x, y};
				}
			}
		}
	}
	
	//Choose leftover tiles
	int risk = 999;
	int lowX = -1;
	int lowY = -1;
	for(int x = 0; x < rowDimension; ++x){
		for(int y = 0; y < colDimension; ++y){
			int check = 0;
			
			if(board[x][y] == -1){
				int nearTiles[10];
				nearCheck(x, y, nearTiles);
				
				for(int i = 0; i < 10; ++i){
					if(nearTiles[i] != -1)
						check += nearTiles[i];
				}
				
				if(check < risk){
					risk = check;
					lowX = x;
					lowY = y;
				}
			}
		}
	}
	
	if(lowX != -1 && lowY != -1){
		--remTiles;
		return {UNCOVER, lowX, lowY};
	}
	
    return {LEAVE,-1,-1};
	
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

}


// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

void MyAI::nearCheck(int x, int y, int* nearTiles)
{
	//Uses numpad notation to mark tiles, xy corrolates to 5.
	nearTiles[0] = -1;
	nearTiles[5] = -1;
	
	for(int i = 0; i < 10; ++i)
		switch(i){
			case 1:
				nearTiles[1] = boundCheck(x-1,y-1);
				break;
			case 2:
				nearTiles[2] = boundCheck(x,y-1);
				break;
			case 3:
				nearTiles[3] = boundCheck(x+1,y-1);
				break;
			case 4:
				nearTiles[4] = boundCheck(x-1,y);
				break;
			//case 5
			case 6:
				nearTiles[6] = boundCheck(x+1,y);
				break;
			case 7:
				nearTiles[7] = boundCheck(x-1,y+1);
				break;	
			case 8:
				nearTiles[8] = boundCheck(x,y+1);
				break;
			case 9:
				nearTiles[9] = boundCheck(x+1,y+1);
				break;				
			default:
				break;
		}
	return;
}

int MyAI::boundCheck(int x, int y)
{
	if(x < 0 || x >= rowDimension ||
		y < 0 || y >= colDimension)
		return -1;
	return board[x][y];
}

// ======================================================================
// YOUR CODE ENDS
// ======================================================================
