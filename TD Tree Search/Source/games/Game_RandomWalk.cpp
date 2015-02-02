//include header
#include "Game_RandomWalk.hpp"

//constructor
Game_RandomWalk::Game_RandomWalk(Game_Engine* source_game)
{

	//game definition
	game_name = "RandomWalk";
	is_deterministic = true;
	is_episodic = true;
	revealsScoreInfo = false;			//does the game reveal the minimally and maximally achievable score to the players (if true, these must be defined accordingly)
	allows_transpositions = true;		//HashKeys functions for this game must be implemented, this means that states (or state-actions) must be identifiable and that the search space is reasonably large to fit in memory
	minScore = 0.0;
	maxScore = 1.0;

	//call initialization procedures
	if(source_game == TOMGAME_ENGINE_CONSTRUCTOR_NO_COPY)
		Initialize();
	else
		Copy_Initialize(source_game);
}

//destructor
Game_RandomWalk::~Game_RandomWalk(void)
{
	//release memory space
	Clear_Memory();
}

//create duplicate game
Game_Engine* Game_RandomWalk::Create_Duplicate_Game(bool copy_state, bool copy_history)
{
	//create new game by copying settings of this game
	Game_RandomWalk* new_game = new Game_RandomWalk(this);

	//set current state of new game
	if(copy_state)
		new_game->Copy_Game_State_From(this, copy_history);
	else
		new_game->Game_Reset();
		
	//return pointer to new game object
	return new_game;
}

//init game settings
void Game_RandomWalk::Init_Settings()
{
	
	//general game settings
	board_length = 1;
	board_height = 1;
	board_size = board_length * board_height;
	number_players = 1;
	maximum_allowed_moves = 2;
	maximum_plys = DEFAULT_MAXPLIES;
	param_score_win = DEFAULT_REWARD_WIN;
	param_score_lose = DEFAULT_REWARD_LOSE;
	param_score_draw = DEFAULT_REWARD_MAXPLIES;
	param_score_step = DEFAULT_REWARD_STEP;

	//maxScore = TODO
	//minScore = TODO

	//general debug settings
	show_warnings = TOM_DEBUG;

}

//copy settings from source_game
void Game_RandomWalk::Copy_Settings(Game_Engine* source_game)
{

	//general game settings
	board_length = source_game->board_length;
	board_height = source_game->board_height;
	board_size = source_game->board_size;
	number_players = source_game->number_players;
	maximum_allowed_moves = source_game->maximum_allowed_moves;
	maximum_plys = source_game->maximum_plys;
	param_score_win = source_game->param_score_win;
	param_score_lose = source_game->param_score_lose;
	param_score_draw = source_game->param_score_draw;
	param_score_step = ((Game_RandomWalk*)source_game)->param_score_step;

	//general debug settings
	show_warnings = source_game->show_warnings;

}

void Game_RandomWalk::Allocate_Memory()
{
	//allocate resources - game state
	board_state = new char[board_size];
	current_number_moves = new int[number_players];
	current_moves = new bool*[number_players];
	current_moves_list = new int*[number_players];
	for(int i = 0; i < number_players; i++){
		current_moves[i] = new bool[maximum_allowed_moves];
		current_moves_list[i] = new int[maximum_allowed_moves];
		for (int a = 0; a < maximum_allowed_moves; a++){
			current_moves[i][a] = true;
			current_moves_list[i][a] = a;
		}
	}
	score = new double[number_players];

	//allocate resources - history
	history_moves = new int[maximum_plys+1];	//added +1 to because of initial game state (when no actions were taken yet)
	history_moves[0] = -1;						//action tag for initial state MUST be -1, otherwise HashKey_get(action) won't return the correct value

	//allocate resources - visualization

	//define constant values - visualization

	//DEBUG
	//for(int i = 0; i < maximum_allowed_moves+1; i++)
	//	printf(" %d",history_moves[i]);
	//printf("\n");
}

void Game_RandomWalk::Clear_Memory()
{
	//release memory space
	delete[] board_state;
	delete[] current_number_moves;
	for(int i = 0; i < number_players; i++){
		delete[] current_moves[i];
		delete[] current_moves_list[i];
	}
	delete[] current_moves;
	delete[] current_moves_list;
	delete[] score;
	delete[] history_moves;
}

/**
Reset to initial values (restart game)
WARNING: move list is not created
*/
void Game_RandomWalk::Game_Reset()
{
	//reset game state variables
	board_state[0] = (int)((DEFAULT_LENGTH - 1) / 2);

	current_number_moves[0] = maximum_allowed_moves;
	current_moves[0][0] = true;
	current_moves[0][1] = true;
	
	score[0] = 0.0;

	current_player = 0;
	game_ended = false;

	//reset history
	current_plys = 0;

	starting_state = board_state[0];
}

/**
Copies game state from target game
WARNING: move list is not copied

@param history_copy_start_index Defines the ammount of moves from beginning where to start copying history (useful if most of the target game is same as source)
*/
void Game_RandomWalk::Copy_Game_State_From(Game_Engine* source, const bool copy_history, int history_copy_start_index)
{
	//copygame state variables
	for(int i = 0; i < board_size; i++){
		board_state[i] = source->board_state[i];
	}
	for(int j = 0; j < number_players; j++){
		current_number_moves[j] = source->current_number_moves[j];
		for(int i = 0; i < maximum_allowed_moves; i++){
			current_moves[j][i] = source->current_moves[j][i];
			//current_moves_list[j][i] = source->current_moves_list[j][i];	//making a list of moves in this phase is usually a waste of computation time
		}
		score[j] = source->score[j];
	}
	current_player = source->current_player;
	game_ended = source->game_ended;

	//copy history
	current_plys = source->current_plys;
	if(copy_history){
		for(int i = history_copy_start_index+1; i < current_plys+1; i++){
			history_moves[i] = source->history_moves[i];
		}
	}

	starting_state = ((Game_RandomWalk*)source)->starting_state;
}

/**
Rule defining next player on move: two-player game

@return Next player on move
*/
int Game_RandomWalk::Get_Next_Player(int player)
{
	return Get_Next_Player_TwoPlayer(player);
}

void Game_RandomWalk::Make_Moves_List()
{
	//nothing to do here (moves list is fixed all the time)
}

/**
@return 1 if game ended, 0 otherwise
*/
int Game_RandomWalk::Game_Dynamics(int selected_move)
{
	//execute move
	if (selected_move == 0)
		this->board_state[0]--;
	else if (selected_move == 1)
		this->board_state[0]++;

	//check ending condition
	Check_Game_Win(this->board_state[0]);

	//update avaliable moves
	if (this->game_ended){
		this->current_number_moves[0] = 0;
		this->current_moves[0][0] = false;
		this->current_moves[0][1] = false;
	}
	
	//update current player
	this->current_player = this->current_player;

	//return feedback
	return (int)(this->game_ended);
}

int Game_RandomWalk::Check_Game_Win(int position)
{
	if (position == DEFAULT_LENGTH - 1){
		this->score[0] += this->param_score_win;
		this->game_ended = true;
	}
	else if (position == 0)
	{
		this->score[0] += this->param_score_lose;
		this->game_ended = true;
	}
	else{
		if (this->current_plys < this->maximum_plys - 1){	// -1 is because current_plays was not yet increased after last move
			this->score[0] += this->param_score_step;
			this->game_ended = false;
		}
		else{
			this->score[0] += this->param_score_draw;
			this->game_ended = true;
		}
	}

	return this->game_ended;
}

int Game_RandomWalk::HashKey_getNumStates()
{
	return DEFAULT_LENGTH;
}

int Game_RandomWalk::HashKey_getNumStateActions()
{
	return (DEFAULT_LENGTH-2) * 2 + 1;	//added +1 because of the initial state (that has no preceeding action)
}

int Game_RandomWalk::HashKey_getCurrentState()
{
	return board_state[0];
}

int Game_RandomWalk::HashKey_getCurrentStateAction(int action)
{
	int key = HashKey_getCurrentState();

	if (action >= 0)
		key = (key - 1) * 2 + action + 1; //added +1 because of the initial state that has key value 0
	else{
		if ((action == -1) && (key == starting_state))
			key = 0;	//initial state (should be called ONLY at the beginning of the game and with action = -1)
		else{
			gmp->Print("ERROR: Game_RandomWalk::HashKey_getCurrent(action) : Invalid action specified (%d) in non-starting game state (%d), initial state = %d\n", action, key, starting_state);
			key = -1;
		}
	}

	return key;
}

/**
Procedure for human move input
*/
int Game_RandomWalk::Human_Move_Input()
{
	int move_num, error, inVal1;

	//repeat until selected move is valid
	move_num = -1;
	while (move_num == -1){

		//print to standard output and get input
		fflush(stdout);
		cout << "Waiting for player" << current_player + 1 << " input 0 or 1: ";

		//check for input error
		error = scanf("%d", &inVal1);
		if (error == 0){
			cin.clear();
			cin.ignore();
			cout << "invalid input!" << endl;

			//check if input value valid
		}
		else{
			move_num = inVal1;
			if (Validate_Move(move_num) == false){
				cout << "invalid move!" << endl;
				move_num = -1;
			}
		}
	}

	//return human input value
	return move_num;
}

/**
Output current game state to standard output.
*/
void Game_RandomWalk::Output_Board_State(char* printLinePrefix)
{
	gmp->Print("\n");
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("%d", board_state[0]);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("PLY: %2d \t Last move: %d", current_plys, history_moves[current_plys]);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n");
	fflush(stdout);

}