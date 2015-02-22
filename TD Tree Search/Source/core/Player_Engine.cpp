//include circular reference
//#include "Game_Engine.hpp"

//include header
#include "Player_Engine.hpp"

/**
Constructor for general game player.
*/
Player_Engine::Player_Engine(Game_Engine* game, int player_number)
{
	//default settings
	this->player_number = player_number;
	this->external_reset_enabled = TOMPLAYER_EXTERNAL_RESET_ENABLED;
	this->final_output_enabled = TOMPLAYER_FINAL_OUTPUT_ENABLED;
	this->visualization_depth = TOMPLAYER_VISUALIZATION_DEPTH;

	//bind game player to game object, even if it is NULL
	this->game = game;
}


double Player_Engine::Neural_Network_Threshold_Function(double input_weight_sum, THRESHOLD_FUNCTIONS::TYPE function_type)
{

	if (function_type == THRESHOLD_FUNCTIONS::SIGMOID_CENTER_ZERO){
		return (1.0 / (1.0 + exp(-input_weight_sum)) - 0.5);

	}
	else if (function_type == THRESHOLD_FUNCTIONS::SIGMOID){
		return (1.0 / (1.0 + exp(-input_weight_sum)));

	}
	else if (function_type == THRESHOLD_FUNCTIONS::STEP){
		return ((double)(input_weight_sum > 0.0));

	}
	else if (function_type == THRESHOLD_FUNCTIONS::LINEAR){
		return (input_weight_sum);

	}
	else{
		//wrong parameter call
		gmp->Print(stderr, "Player_AI_RL::Neural_Network_Threshold_Function: ERROR: incorrect function_type: %d\n", function_type);
		return -1;

	}

}

//allocate memory and initialize variables
void Player_Engine::Initialize()
{
	//set init flag
	is_initialized = true;

	//initialize settings
	Init_Settings();

	//allocate resources
	Allocate_Memory();
	
	//reset game state
	Reset();
}

//use this if settings are changed after initialization
void Player_Engine::Apply_Settings()
{
	Clear_Memory();
	Allocate_Memory();
	Reset();
}

/**
Reset settings and change to new game.

@param game If this equals NULL then player will not be reallocated but only reset to initial values
*/
void Player_Engine::Reset_Settings(Game_Engine* game)
{
	if(game != NULL){
		Clear_Memory();
		this->game = game;
		Initialize();
	}else{
		if(this->game != NULL){
			Init_Settings();
			Reset();
		}
	}
}

/**
Human player
*/
Player_Human::Player_Human(Game_Engine* game) : Player_Engine(game)
{
	//player definition
	player_name = "Human";
}

int Player_Human::Get_Move()
{
	return game->Human_Move_Input();
}

/**
Random move player
*/
Player_Random::Player_Random(Game_Engine* game) : Player_Engine(game)
{
	//player definition
	player_name = "Random";
}

int Player_Random::Get_Move()
{
	return game->Select_Move_Random();
}

/**
Passive move player (does not play moves or most neutral one)
*/
Player_Passive::Player_Passive(Game_Engine* game) : Player_Engine(game)
{
	//player definition
	player_name = "Passive";
}
int Player_Passive::Get_Move()
{
	return game->Select_Move_Passive();
}

/**
Player that plays always the same move: int move is public
*/
Player_SameMove::Player_SameMove(Game_Engine* game) : Player_Engine(game)
{
	//player definition
	player_name = "SameMove";

	//init
	move = 0;
}
int Player_SameMove::Get_Move()
{
	return move;
}

