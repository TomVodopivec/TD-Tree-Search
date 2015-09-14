#ifndef _TOM_GAME_TICTACTOE_
#define _TOM_GAME_TICTACTOE_

//includes
#include "..\games\Game_Gomoku.hpp"

/**
Definiton of the Tic Tac Toe game engine.

Scoring: win 1, lose 0 (see defines)
*/
#pragma once
class Game_TicTacToe : public Game_Gomoku
{

public:

	//default values
	static const int TICTACTOE_BOARD_LENGTH;
	static const int TICTACTOE_WIN_CONNECTED_PIECES;
	static const double TICTACTOE_SCORE_START;
	static const double TICTACTOE_SCORE_WIN;
	static const double TICTACTOE_SCORE_LOSE;
	static const double TICTACTOE_SCORE_DRAW;

	//public procedures - engine
	Game_TicTacToe(Game_Engine* source_game = TOMGAME_ENGINE_CONSTRUCTOR_NO_COPY);	//Constructor
	virtual ~Game_TicTacToe(void);							//Destructor

	//public procedures - support
	Game_Engine* Create_Duplicate_Game(bool copy_state = TOMGAME_ENGINE_COPY_GAME_STATE, const bool copy_history = TOMGAME_ENGINE_COPY_GAME_HISTORY);

	//hash key functions (transpositions)
	int HashKey_getNumStates();
	int HashKey_getNumStateActions();
	int HashKey_getCurrentState();
	int HashKey_getCurrentStateAction(int action);

protected:
	//private procedures
	void Init_Settings();
	int  Check_Game_Win(int selected_move);

};



#endif