//include header
#include "Game_TicTacToe.hpp"

//TEMPORARILY MOVED HERE FROM HEADER: is already valid by the c++11 standard (in-header static const double initialization), but is not yet implemented in VS2013
const int	 Game_TicTacToe::TICTACTOE_BOARD_LENGTH = 3;
const int	 Game_TicTacToe::TICTACTOE_WIN_CONNECTED_PIECES = 3;
const double Game_TicTacToe::TICTACTOE_SCORE_START = 0.5;
const double Game_TicTacToe::TICTACTOE_SCORE_WIN = 1.0;
const double Game_TicTacToe::TICTACTOE_SCORE_LOSE = 0.0;
const double Game_TicTacToe::TICTACTOE_SCORE_DRAW = 0.5;

//constructor
Game_TicTacToe::Game_TicTacToe(Game_Engine* source_game)
{

	//game definition
	game_name = "TicTacToe";
	is_deterministic = true;
	is_episodic = true;
	revealsScoreInfo = true;			//does the game reveal the minimally and maximally achievable score to the players (if true, these must be defined accordingly)
	allows_transpositions = true;		//HashKeys functions for this game must be implemented, this means that states (or state-actions) must be identifiable and that the search space is reasonably large to fit in memory

	//call initialization procedures
	if(source_game == TOMGAME_ENGINE_CONSTRUCTOR_NO_COPY)
		Initialize();
	else
		Copy_Initialize(source_game);
}

//destructor
Game_TicTacToe::~Game_TicTacToe(void)
{
	if (is_initialized){

		//release memory space
		Clear_Memory();

		is_initialized = false;
	}
}

//create duplicate game
Game_Engine* Game_TicTacToe::Create_Duplicate_Game(bool copy_state, bool copy_history)
{
	//create new game by copying settings of this game
	Game_TicTacToe* new_game = new Game_TicTacToe(this);

	//set current state of new game
	if(copy_state)
		new_game->Copy_Game_State_From(this, copy_history);
	else
		new_game->Game_Reset();
		
	//return pointer to new game object
	return new_game;
}

void Game_TicTacToe::Init_Settings()
{
	//init game settings
	board_length = TICTACTOE_BOARD_LENGTH;
	board_height = TICTACTOE_BOARD_LENGTH;
	board_size = board_length * board_height;
	number_players = 2;
	maximum_allowed_moves = board_size;
	maximum_plys = board_size;
	win_connected_pieces = TICTACTOE_WIN_CONNECTED_PIECES;
	param_score_start = TICTACTOE_SCORE_START;
	param_score_win = TICTACTOE_SCORE_WIN;
	param_score_lose = TICTACTOE_SCORE_LOSE;
	param_score_draw = TICTACTOE_SCORE_DRAW;
	 
	//init debug settings
	show_warnings = TOM_DEBUG;
}

//hardcoded win combinations for 3x3 tic tac toe
int Game_TicTacToe::Check_Game_Win(int selected_move)
{
	int win = 0;

	if(selected_move == 0){
		if	(
				((board_state[1] == current_player+1) && (board_state[2] == current_player+1)) ||
				((board_state[3] == current_player+1) && (board_state[6] == current_player+1)) ||
				((board_state[4] == current_player+1) && (board_state[8] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 1){
		if	(
				((board_state[0] == current_player+1) && (board_state[2] == current_player+1)) ||
				((board_state[4] == current_player+1) && (board_state[7] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 2){
		if	(
				((board_state[0] == current_player+1) && (board_state[1] == current_player+1)) ||
				((board_state[4] == current_player+1) && (board_state[6] == current_player+1)) ||
				((board_state[5] == current_player+1) && (board_state[8] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 3){
		if	(
				((board_state[0] == current_player+1) && (board_state[6] == current_player+1)) ||
				((board_state[4] == current_player+1) && (board_state[5] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 4){
		if	(
				((board_state[0] == current_player+1) && (board_state[8] == current_player+1)) ||
				((board_state[1] == current_player+1) && (board_state[7] == current_player+1)) ||
				((board_state[2] == current_player+1) && (board_state[6] == current_player+1)) ||
				((board_state[3] == current_player+1) && (board_state[5] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 5){
		if	(
				((board_state[2] == current_player+1) && (board_state[8] == current_player+1)) ||
				((board_state[3] == current_player+1) && (board_state[4] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 6){
		if	(
				((board_state[0] == current_player+1) && (board_state[3] == current_player+1)) ||
				((board_state[2] == current_player+1) && (board_state[4] == current_player+1)) ||
				((board_state[7] == current_player+1) && (board_state[8] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 7){
		if	(
				((board_state[1] == current_player+1) && (board_state[4] == current_player+1)) ||
				((board_state[6] == current_player+1) && (board_state[8] == current_player+1))
			)
			win = 1;
	} else if (selected_move == 8){
		if	(
				((board_state[2] == current_player+1) && (board_state[5] == current_player+1)) ||
				((board_state[0] == current_player+1) && (board_state[4] == current_player+1)) ||
				((board_state[6] == current_player+1) && (board_state[7] == current_player+1))
			)
			win = 1;
	}

	return win;
}

int Game_TicTacToe::HashKey_getNumStates()
{
	return 19683;	//3 to the power of 9
}

int Game_TicTacToe::HashKey_getNumStateActions()
{
	return 19683 * 9 + 1;	//added +1 because of the initial state (that has no preceeding action)
}

int Game_TicTacToe::HashKey_getCurrentState()
{
	int key = 0;
	int power = 1;
	for (int s = 0; s < 9; s++){
		key += ((int)(board_state[s]) * power);
		power *= 3;
	}
	return key;
}

int Game_TicTacToe::HashKey_getCurrentStateAction(int action)
{
	int key = HashKey_getCurrentState();

	if (action >= 0)
		key = key * 9 + action + 1; //added +1 because of the initial state that has key value 0
	else{
		if ((action == -1) && (key == 0))
			key = 0;	//initial state (should be called ONLY at the beginning of the game and with action = -1)
		else{
			gmp->Print("ERROR: Game_RandomWalk::HashKey_getCurrent(action) : Invalid action specified (%d) in non-starting game state (%d), initial state = %d\n", action, key, 0);
			key = -1;
		}
	}

	return key;
}