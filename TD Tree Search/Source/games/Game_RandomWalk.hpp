#ifndef _TOM_TOYGAME_RANDOMWALK_
#define _TOM_TOYGAME_RANDOMWALK_

//#includes
#include "..\core\Game_Engine.hpp"

/**
Definiton of the Random Walk toy game.
*/
#pragma once
class Game_RandomWalk : public Game_Engine
{

public:

	//default values
#define DEFAULT_LENGTH				5		//currently maximum 255 (or 127, not sure, due to 'char' type implementation of Game_Engine)
#define DEFAULT_MAXPLIES			10000
#define DEFAULT_REWARD_WIN			1.0
#define DEFAULT_REWARD_LOSE			0.0
#define DEFAULT_REWARD_STEP			0.0
#define DEFAULT_REWARD_MAXPLIES		0.0

	//public procedures - engine
	Game_RandomWalk(Game_Engine* source_game = TOMGAME_ENGINE_CONSTRUCTOR_NO_COPY);	//Constructor
	virtual ~Game_RandomWalk(void);													//Destructor
	void Game_Reset();

	//public procedures - support
	void Copy_Game_State_From(Game_Engine* source, const bool copy_history = TOMGAME_ENGINE_COPY_GAME_HISTORY, int history_copy_start_index = 0);
	Game_Engine* Create_Duplicate_Game(bool copy_state = TOMGAME_ENGINE_COPY_GAME_STATE, const bool copy_history = TOMGAME_ENGINE_COPY_GAME_HISTORY);
	using Game_Engine::Get_Next_Player;
	int Get_Next_Player(int);
	virtual void Make_Moves_List();

	//public procedures - debug and visualization

	//public variables - game settings
	double param_score_step;

	//public variables - game state
	int HashKey_getNumStates();
	int HashKey_getNumStateActions();
	int HashKey_getCurrentState();
	int HashKey_getCurrentStateAction(int action);

	//public variables - game history

	//public variables - debug


protected:
	//private procedures
	void Init_Settings();
	void Allocate_Memory();
	void Clear_Memory();
	void Clear_Constants();
	void Copy_Settings(Game_Engine* source_game);
	int  Game_Dynamics(int selected_move);
	int	 Check_Game_Win(int position);

	//private procedures - support
	int	 Human_Move_Input();

	//public procedures - debug and visualization
	void Output_Board_State(char* printLinePrefix = "");

	//private variables - game state
	char starting_state;

};



#endif