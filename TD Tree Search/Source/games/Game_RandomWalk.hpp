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

	//consts - default values
	static const int	DEFAULT_WALK_LENGTH;
	static const int	DEFAULT_MAXPLIES;
	static const double	DEFAULT_REWARD_START;
	static const double	DEFAULT_REWARD_WIN;
	static const double	DEFAULT_REWARD_LOSE;
	static const double	DEFAULT_REWARD_STEP;
	static const double DEFAULT_REWARD_MAXPLIES;

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
	virtual void Output_Settings(bool calledByDescription = false);

	//public variables - game settings
	int config_walk_length;
	double param_score_step;

	//public variables - game state
	int HashKey_getNumStates();
	int HashKey_getNumStateActions();
	int HashKey_getCurrentState();
	int HashKey_getCurrentStateAction(int action);

	//public variables - game history

	//public variables - experiments, visualization and debug
	void Compute_OptimalStateValues();

	//statics
	static const char * settingsLabels[];
	static const char * settingsFormat[];

protected:
	//private procedures
	void Init_Settings();
	void Allocate_Memory();
	void Clear_Memory();
	//void Clear_Constants();
	void Copy_Settings(Game_Engine* source_game);
	int  Game_Dynamics(int selected_move);
	int	 Check_Game_Win(int position);

	//private procedures - support
	int	 Human_Move_Input();

	//public procedures - debug and visualization
	void Output_Board_State(char* printLinePrefix = "");

	//private variables - game state
	int starting_state;

};



#endif