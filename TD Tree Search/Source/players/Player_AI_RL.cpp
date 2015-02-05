//include header
#include "Player_AI_RL.hpp"

/**
Constructor for AI UCT player module calling general game player constructor

@param game Pointer to a Game_Engine object (or derivated class)
*/
Player_AI_RL::Player_AI_RL(Game_Engine* game, int player_number) : Player_Engine(game, player_number)
{
	//player definition
	this->player_name = "PlayerAIRL";
	this->is_initialized = false;
	this->is_allocated = false;

	//temporary moved from Init_Settings()
	Func_App_UCT_num_params = FUNC_APPROX_NUM_PARAMS;

	//call initialization procedures
	if (game != NULL)
		Initialize();
}

//destructor
Player_AI_RL::~Player_AI_RL(void)
{
	Clear_Memory();
}

//allocate memory and initialize variables
void Player_AI_RL::Initialize()
{
	//set init flag
	is_initialized = true;

	//initialize settings
	Init_Settings();

	//allocate resources
	Allocate_Memory();

	//reset game state
	New_Game2();
}

void Player_AI_RL::Init_Settings()
{
	//init optimization settings
	internal_game_force_copy = OPTIMIZATION_INTERNAL_FORCE_COPY;

	//UCT_param_SimPerIter = TOMPLAYER_AI_UCT_TOMTEST_PARAM_SIMULATIONS_PER_ITER;

	//init configuration

	config_preset_algorithm = DEFAULT_PRESET_ALGORITHM;

	config_control_policy = DEFAULT_CONTROL_POLICY;
	config_policy_evaluation = DEFAULT_POLICY_EVALUATION;
	config_TDupdateType = DEFAULT_TD_UPDATE_TYPE;
	config_trace_type = DEFAULT_Q_TRACE_TYPE;
	config_trace_exploratory_reset = DEFAULT_TRACE_EXPLORATORY_RESET;
	config_transpositions = DEFAULT_USE_TRANSPOSITIONS;
	config_rollout_assumption = DEFAULT_ROLLOUT_ASSUMPTION;

	config_offpolicy_backup_recheck_best = DEFAULT_OFFPOLICY_BACKUP_RECHECK_BEST;
	config_nonEpisodicTasks_updateInterval = DEFAULT_NONEPISODICTASKS_UPDATEINTERVAL;

	config_num_new_nodes_per_episode = DEFAULT_NUM_NEW_NODES_PER_EPISODE;

	config_opponent_alignment = DEFAULT_OPPONENT_ALIGNMENT;
	config_opponent_policy = DEFAULT_OPPONENT_POLICY;

	config_alpha_type = DEFAULT_UPDATESTEP_ALPHA_TYPE;

	config_ucb_visit_type = DEFAULT_UCB_VISITS_TYPE;
	config_ucb_norm_type = DEFAULT_UCB_NORMALIZATION_TYPE;
	config_ucb_norm_global = DEFAULT_UCB_NORMALIZATION_GLOBAL_TYPE;
	config_ucb_norm_local = DEFAULT_UCB_NORMALIZATION_LOCAL_TYPE;

	par_egreedy_e = DEFAULT_PAR_EPSILON;
	par_ucb_c = DEFAULT_PAR_UCB_C;

	par_task_gamma = DEFAULT_PAR_TASK_GAMMA;
	par_td_alpha = DEFAULT_PAR_TD_ALPHA;
	par_td_lambda = DEFAULT_PAR_TD_LAMBDA;
	par_td_initVal = DEFAULT_PAR_TD_INITVAL;

	par_num_episodes = DEFAULT_NUM_EPISODES_PER_MOVE;
	par_num_simulatedActions_perMove = DEFAULT_SIMULATEDACTIONS_PER_MOVE;
	par_simulated_horizon_lenght = DEFAULT_SIMULATED_HORIZON_LENGTH;
	config_memory_limitMB = (double)DEFAULT_MEMORY_LIMIT_MB;

	config_numerical_correction = DEFAULT_NUMERICAL_CORRECTION;

	//visualization
	config_output_depth =			DEFAULT_OUTPUT_DEPTH;
	config_output_simGameState =	DEFAULT_OUTPUT_SIMGAMESTATE_DEPTH;
	config_output_trajectory =		DEFAULT_OUTPUT_TRAJECTORY_DEPTH;
	config_output_memory =			DEFAULT_OUTPUT_MEMORY_DEPTH;
	config_output_summary =			DEFAULT_OUTPUT_SUMMARY_DEPTH;
	config_output_currentInfo =		DEFAULT_OUTPUT_CURRENTINFO_DEPTH;
	config_output_TDbackup =		DEFAULT_OUTPUT_TDBACKUP_DEPTH;
	config_output_pause =			DEFAULT_OUTPUT_PAUSE_DEPTH;

	config_output_memory_treeDepth = DEFAULT_OUTPUT_MEMORY_TREEDEPTH;

	////old
	//output_level_headers_created = false;

	////debug variables
	//debug_dbl_cnt1 = 0;
	//debug_dbl_cnt2 = 0;

	//set parameters by the selected preset - overrides certain settings, depending on which preset was selected
	Apply_Preset_Config(this->config_preset_algorithm);
}

void Player_AI_RL::Allocate_Memory()
{
	//allocate resources
	internalGame = game->Create_Duplicate_Game();
	simulatedGame = game->Create_Duplicate_Game();
	//simulatedGame_startingState = game->Create_Duplicate_Game();

	////simulations feedback structures
	//sim_feedback_scores_avg = new double[game->number_players];
	//sim_feedback_scores_var = new double[game->number_players];
	//sim_feedback_scores = new double*[UCT_param_SimPerIter];
	//for (int i = 0; i < UCT_param_SimPerIter; i++)
	//	sim_feedback_scores[i] = new double[game->number_players];
	//sim_feedback_plys = new double[UCT_param_SimPerIter];

	//memory strucure
	int hashMapSize = 0;
	if (config_transpositions != (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){		// get size of table if using transpositions
		hashMapSize = game->HashKey_getNum(config_transpositions);
		if (hashMapSize == 0)
			gmp->Print("WARNING: Player_AI_RL::Allocate_Memory() : game %s does not allow transpositions, switching to TRANSPOSITIONS_DISABLED\n", game->game_name.c_str());
	}

	memory = new HashTree(config_memory_limitMB, hashMapSize);

	//history of rewards in for last episode (for offline backups)
	if (internalGame->is_episodic)
		trajectory_maxLength = internalGame->maximum_plys + 1;		//added +1 to because of initial game state (when no actions were taken yet)
	else
		trajectory_maxLength = config_nonEpisodicTasks_updateInterval + 1;	//added +1 to because of initial game state (when no actions were taken yet)
	trajectory = new trajectoryRecord[trajectory_maxLength];

	this->is_allocated = true;
}

void Player_AI_RL::Clear_Memory()
{
	//clean up memory
	if (this->is_allocated){
		delete(internalGame);
		delete(simulatedGame);
		delete(memory);
		delete[] trajectory;

		////simulations feedback structures
		//delete(simulatedGame_startingState);
		//delete[] sim_feedback_scores_avg;
		//delete[] sim_feedback_scores_var;
		//for (int i = 0; i < UCT_param_SimPerIter; i++)
		//	delete[] sim_feedback_scores[i];
		//delete[] sim_feedback_scores;
		//delete[] sim_feedback_plys;

		this->is_allocated = false;
	}
}

//public procedure: signal player that new game has been started
void Player_AI_RL::New_Game()
{
	Reset();		//calls reset1(), newGame(), newGame1()
}

//public procedure: reset player (reset all learning values)
void Player_AI_RL::Reset()
{
	memory->Reset();
	return New_Game2();
}

void Player_AI_RL::New_Game2()
{

	//RESET internal game copy
	this->internalGame->Copy_Game_State_From(game);

	//the active starting state (node) for each simulation - the root node for each episode
	this->internalGameActiveNode = NULL;

	//zero the counters
	this->numEpisodes_lastMove = 0;
	this->numEpisodes_total = 0;
	this->numSimulatedActions_lastEpisode = 0;
	this->numSimulatedActions_lastMove = 0;
	this->numSimulatedActions_total = 0;
	this->numNewStates_lastEpisode = 0;
	this->numVisitedKnownStates_lastEpisode = 0;
	this->sumSimulatedRewards_lastEpisode = 0.0;
	this->sumSimulatedRewards_lastMove = 0.0;
	this->sumSimulatedRewards_total = 0.0;

	this->maximumObservedReturn = -DBL_MAX;
	this->minimumObservedReturn = DBL_MAX;

	if (this->internalGame->revealsScoreInfo){
		this->maximumKnownReturn = this->internalGame->maxScore;
		this->minimumKnownReturn = this->internalGame->minScore;
		if ( this->minimumKnownReturn >= this->maximumKnownReturn ){
			gmp->Print("WARNING: Player_AI_RL::New_Game2() : maxScore (%f) and minScore (%f) not defined correctly in game %s\n", this->maximumKnownReturn, this->minimumKnownReturn, this->internalGame->game_name.c_str());
			this->maximumKnownReturn = -DBL_MAX;
			this->minimumKnownReturn = DBL_MAX;
		}
	}
	else{
		this->maximumKnownReturn = -DBL_MAX;
		this->minimumKnownReturn = DBL_MAX;
	}

	//set parameters by the selected preset - overrides certain settings, depending on which preset was selected
	Apply_Preset_Config(this->config_preset_algorithm);

	//figure out whether numerical correction is possible for given settings
	this->numerical_correction_possible = 0;
	if (
		(
		(!((this->config_num_new_nodes_per_episode != -1) && (this->config_rollout_assumption != ROLLOUT_NODE_ASSUME_INITIAL_VALUE))) &&
		(this->config_transpositions == Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED) &&
		(this->config_policy_evaluation != EVALUATION_TDLAMBDA_OFFPOLICY_Q_LEARNING)
		) || 
		(
		(!((this->config_trace_type == Q_TRACE_ACCUMULATING) && (this->config_alpha_type == ALPHA_CONSTANT))) &&
		(!((this->config_trace_exploratory_reset == Q_TRACE_EXPLORATORY_RESET_ENABLED) && (this->config_TDupdateType == TD_UPDATE_OFFLINE)))
		//also not yet sure when DEFAULT_NUM_NEW_NODES_PER_EPISODE different than -1
		)
		){
		this->numerical_correction_possible = 1;
	}

	//vizualization and debug variables
	outInfoCounter = 0;
}

//set parameters by the selected preset - overrides certain settings, depending on which preset was selected
void Player_AI_RL::Apply_Preset_Config(PRESET_ALGORITHMS preset)
{
	if (preset == NO_PRESET_ALGORITHM)
	{
		//// list of all settable parameters:
		//this->config_preset_algorithm;
		//this->config_control_policy;
		//this->config_policy_evaluation;
		//this->config_TDupdateType;
		//this->config_trace_type;
		//this->config_trace_exploratory_reset;
		//this->config_transpositions;
		//this->config_offpolicy_backup_recheck_best;
		//this->config_nonEpisodicTasks_updateInterval;
		//this->config_num_new_nodes_per_episode;
		//this->config_rollout_assumption;
		//this->config_alpha_type;
		//this->config_ucb_visit_type;
		//this->config_ucb_norm_type;
		//this->config_ucb_norm_global;
		//this->config_ucb_norm_local;
		//this->config_opponent_alignment;
		//this->config_opponent_policy;
		//this->par_egreedy_e;
		//this->par_ucb_c;
		//this->par_task_gamma;
		//this->par_td_alpha;
		//this->par_td_lambda;
		//this->par_td_initVal;
		//this->par_num_episodes;
		//this->par_num_simulatedActions_perMove;
		//this->par_simulated_horizon_lenght;
		//this->config_memory_limitMB;

		//// subset of the list above, relevant for presets:
		//this->config_control_policy;
		//this->config_policy_evaluation;
		//this->config_TDupdateType;
		//this->config_trace_type;
		//this->config_trace_exploratory_reset;
		//this->config_num_new_nodes_per_episode;
		//this->config_rollout_assumption;
		//this->config_alpha_type;
		//this->par_td_lambda;
	}

	else if (preset == ALGORITHM_FIRSTVISIT_MC_ONPOLICY)
	{
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_ONPOLICY;
		this->config_TDupdateType = TD_UPDATE_OFFLINE;
		this->config_trace_type = Q_TRACE_REPLACING;
		//this->config_rollout_assumption = ROLLOUT_NODE_ASSUME_CONVERGED_REWARD;	//this is probably needed (not sure yet) when gamma < 1
		this->config_alpha_type = ALPHA_MONTE_CARLO;
		this->par_td_lambda = 1.0;
	}

	else if (preset == ALGORITHM_EVERYVISIT_MC_ONPOLICY)
	{
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_ONPOLICY;
		this->config_TDupdateType = TD_UPDATE_OFFLINE;
		this->config_trace_type = Q_TRACE_ACCUMULATING;
		//this->config_rollout_assumption = ROLLOUT_NODE_ASSUME_CONVERGED_REWARD;	//this is probably needed (not sure yet) when gamma < 1
		this->config_alpha_type = ALPHA_MONTE_CARLO;
		this->par_td_lambda = 1.0;
	}

	else if (preset == ALGORITHM_TD_ZERO_ONPOLICY)
	{
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_ONPOLICY;
		this->par_td_lambda = 0.0;
	}

	else if (preset == ALGORITHM_TD_LAMBDA)
	{
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_ONPOLICY;
	}

	else if (preset == ALGORITHM_ONLINE_WATKINS_Q)
	{
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_OFFPOLICY_Q_LEARNING;
		this->config_TDupdateType = TD_UPDATE_ONLINE;	//may also be OFFLINE_INPLACE
		this->config_trace_exploratory_reset = Q_TRACE_EXPLORATORY_RESET_ENABLED;
	}

	else if (preset == ALGORITHM_ONLINE_NAIVE_Q)
	{
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_OFFPOLICY_Q_LEARNING;
		this->config_TDupdateType = TD_UPDATE_ONLINE;	//may also be OFFLINE_INPLACE
		this->config_trace_exploratory_reset = Q_TRACE_EXPLORATORY_RESET_DISABLED;
	}

	//else if (preset == ALGORITHM_PENGS_Q)
	//{
		// not implemented yet
	//}

	else if (preset == ALGORITHM_UCT)
	{
		this->config_control_policy = CONTROL_UCB;
		this->config_policy_evaluation = EVALUATION_TDLAMBDA_ONPOLICY;
		this->config_TDupdateType = TD_UPDATE_OFFLINE;
		this->config_trace_type = Q_TRACE_REPLACING;
		this->config_num_new_nodes_per_episode = 1;
		//this->config_rollout_assumption = ROLLOUT_NODE_ASSUME_CONVERGED_REWARD;	//this is probably needed when gamma < 1
		this->config_alpha_type = ALPHA_MONTE_CARLO;
		this->par_td_lambda = 1.0;
	}
	
	////safety checks
	//if((this->config_trace_exploratory_reset == Q_TRACE_EXPLORATORY_RESET_ENABLED) && (this->config_TDupdateType == TD_UPDATE_OFFLINE) && (this->config_transpositions == Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){
	//	gmp->Print("\nWARNING: Player_AI_RL::Apply_Preset_Config(): configuration may diverge: Q_TRACE_EXPLORATORY_RESET_ENABLED should not be used with TD_UPDATE_OFFLINE when using transpositions");
	//}


}

//public procedure: returns players next selected move
int Player_AI_RL::Get_Move()
{
	int moveNumber;
	int number_internal_moves;

#if(DEBUG_TRACE_SELECTED_NODE)
	gmp->Print("TRACE_NODE_SEL:  ply iter action     value      N      R     Qval\n");
#endif

	//debug: display tree state
	//STDprint_UCTtree_state();
	//STDprintTreeVal(root);

	//How many moves were made in external game since last Get_Move() call
	number_internal_moves = (game->current_plys - internalGame->current_plys);

	//Update memory structures according to external position changes
	//replay moves in internal game and update currently selected tree/table entry
	//Also creates first root node (and initial hash table entry) before game start
	Update_Memory_After_External_Change(number_internal_moves);

	//Execute UCT algortihm and select best action
	moveNumber = RL_Algorithm();

	// visualization and debug
	Output_ExternalMove_Level();

	//return selected move
	return moveNumber;
}

/**
Update memory structures according to external position changes (replay moves in internal game and update currently selected tree/table entry).
If transpositions are not used set new root and delete parts of the tree that are irrelevant.

*/
void Player_AI_RL::Update_Memory_After_External_Change(int number_actions)
{
	int hashKey = -1;
	int actionID = -1;

	//check if external game should be copied to or replayed in internal game
	bool replayGame = (game->is_deterministic == true) && (internal_game_force_copy == false);

	//make a copy of the external game and store it as internalGame
	if (replayGame == false)
		internalGame->Copy_Game_State_From(game, true, internalGame->current_plys - 1);

	//play all players moves in internal copy of game (including own last external move) and update memory structures
	for (int a = number_actions - 1; a >= 0; a--){

		//get action from external game history
		actionID = game->history_moves[game->current_plys - a];

		//perform selected action on internal copy of the game, return the hashKey of the next active state (if needed for transpositions).
		if (replayGame == true)
			std::tie(std::ignore, std::ignore, hashKey) = RL_Perform_Action(internalGame, actionID);
		
		//delete irrelevant parts of the tree when transpositions are not used
		if (this->config_transpositions == (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED))
			this->internalGameActiveNode = memory->Crop_Tree_ActionID(actionID);	//sets new active node

	}

	// set new active node (get next state record) when using transpositions
	if (this->config_transpositions != (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){

		// needed for state-action transpositions to correctly initialize the game-starting state
		if (this->config_transpositions == (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_STATEACTIONS)){
			if (replayGame == false){
				gmp->Print("ERROR: Player_AI_RL::Update_Memory_After_External_Change() : player does not yet support state-action transpositions on non-determinisic games or with 'force copy' flag set.\n");
				//TODO: copying state currently not supported for state-action transpositions because ...
				//we need to get the state-action hash key value of one moment before this player's move ...
				//so this needs to be implemented in the After_Move() procedure; IF transpositions == state-action, otherwise it is not neede
				//also make sure (improve Game_Engine) that After_Move() is called whenever a game is being played: actually it should be wrapped around into Play_Move() ... samo with Before_Move()
			}
			else if (number_actions == 0){
				//only to initialize starting state
				if (this->internalGameActiveNode == NULL){
					actionID = internalGame->history_moves[internalGame->current_plys];
					hashKey = internalGame->HashKey_getCurrentStateAction(actionID);
				}
				//otherwise does not change active node
			}
		}

		// needed for state transpositions to correctly initialize the game-starting state
		if (this->config_transpositions == (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_STATES)){
			if ((number_actions == 0) || (replayGame == false))
				hashKey = internalGame->HashKey_getCurrentState();
		}

		// set new active node (get next state record) when using transpositions
		this->internalGameActiveNode = memory->hashMap[hashKey];
	}

	// memorize new state if it was not memorized yet -> also changes root node if transpositions are not used
	if (this->internalGameActiveNode == NULL)
		this->internalGameActiveNode = AddNode(internalGame, hashKey, NULL, -1);



	//DEBUG: check if move history of external and internal game is equal
#if(DEBUG_HISTORY_COPY_CHECK)
	for (int i = 0; i <= game->current_plys; i++){
		if (game->history_moves[i] != internalGame->history_moves[i]){
			printf("PLAYER AI UCT: UCT_Update_Internal_Game(): game copy error - external and internal game history does not match at index %d: ext %d int %d ... RESETTING UCT PLAYER\n", i, game->history_moves[i], internalGame->history_moves[i]);
			i = game->current_plys + 1;
			Reset();
		}
	}
#endif

}

int Player_AI_RL::RL_Algorithm()
{

	// reset counters for current external move
	this->numSimulatedActions_lastMove = 0;
	this->numEpisodes_lastMove = 0;
	this->sumSimulatedRewards_lastMove = 0.0;

	//execute MCTS iterations with given computational budget
	bool computationalBudgetAvailable = true;
	while (computationalBudgetAvailable){

		//RESET simulated game position to initial state
		simulatedGame->Copy_Game_State_From(internalGame, false);

		//reinforcement learning algorithms
		computationalBudgetAvailable = RL_Single_Episode();

		//DEBUG
		//internalGame->output_chains_to_STD();
		//simulatedGame->output_chains_to_STD();
		//simulatedGame->output_state_to_STD();
		//printf("sim player %d\n",simulatedGame->current_player);

		//DEBUG
#if(VISUALIZE_LEVEL_UCT)
		printf("\nSim num %2d     score", this->numEpisodes_lastMove);
		//for(int t = 0; t < game->number_players; t++)
		//	printf("  %3.5f",final_rewards[t]);
#if(!VISUALIZE_UCT_ACTIONS_TREE)
		printf("     root  %2d", UCTroot->action_index);
#else
		printf("     tree  %2d", UCTroot->action_index);
		printf("%s", visualizeActionsTree.str().c_str());
		visualizeActionsTree.str("");		//set stringstream to empty
		visualizeActionsTree.clear();		//clear flags
#endif
#if(VISUALIZE_UCT_ACTIONS_PLAYOUT)
		printf("    \t playout:");
		printf("%s", visualizeActionsPlayout.str().c_str());
		visualizeActionsPlayout.str("");	//set stringstream to empty
		visualizeActionsPlayout.clear();	//clear flags
#endif
#endif

#if(DEBUG_TREE_EXPANSION_SIM)
		//Output_UCT_Tree();
		Output_UCT_Tree_Node_Children(UCTroot);
#endif


	}

	//DEBUG
#if(DEBUG_TREE_EXPANSION)
	Output_UCT_Tree();
#endif

	//increase global counter of invoked UCT plys
	//UCT_num_plys++;

	// ---- select the best evaluated move ---- //

	//return best action from root, fully greedy
	int greedyFinalAction;
	std::tie(greedyFinalAction, std::ignore, std::ignore, std::ignore, std::ignore)
		= RL_Control_Egreedy(internalGame, internalGameActiveNode, 0.0, REWARD_MAXIMIZE);

	return greedyFinalAction;

	// --- DO NOT WRITE CODE BELOW THIS LINE ---- it will not be executed because of the return's above

}

bool Player_AI_RL::RL_Single_Episode()
{

	//if (this->numEpisodes_lastMove >= 14)
	//	printf("stop");

	// return variables
	bool computeNextEpisode = true;	

	// local variables
	HashTree::TreeNode* currentState = internalGameActiveNode;
	HashTree::TreeNode* successorState;
	int isTerminalState = simulatedGame->game_ended;
	REWARD_GOALS rewardGoal;

	// reset counters for current episode
	this->numNewStates_lastEpisode = 0;
	this->numSimulatedActions_lastEpisode = 0;
	this->numVisitedKnownStates_lastEpisode = 1;	//how many of the states in this trajectory (episode) were already memorized (known) before this episode, init on 1 because of the starting state (root node)
	this->sumSimulatedRewards_lastEpisode = NAN;

	// initialize current episode trace variables
	this->exploratory_move_trace_cutOff = 0;	//needed for Watkin's Q-learning to stop the backups at exploratory moves

	// mark last state visits
	MarkStateVisit(currentState);

	// memorize start of trajectory in current episode, MUST called after RL_StateMarkVisit()
	this->trajectory_length = -1;	//must be set to -1 because the following procedure AddTrajectoryEntry() first increases the conuter and then writes the record
	if (this->internalGame->number_players == 1)
		rewardGoal = REWARD_MAXIMIZE;
	else
		rewardGoal = GOAL_UNKNOWN;
	AddTrajectoryEntry(internalGame->history_moves[internalGame->current_plys], currentState, 0.0, rewardGoal, NAN, NAN);

	// move through the episode until a terminal state is reached
	bool computeNextAction = true;
	while ((isTerminalState == 0) && (computeNextAction))
	{

		//if (this->numEpisodes_lastMove >= 10)
		////if (this->simulatedGame->current_plys >= 60)
		//	printf("stop\n");


		//Output_Trajectory();
		//Output_Memory_State();

		int hashKey;
		double reward;

		int actionID;
		int onPolicy_selected_child_index;
		int bestChild_index;
		double onPolicyChildValue;
		double bestChildValue;

		// safety check if number of allowed moves is equal to the number of moves previously memorized for this state
		if (currentState != NULL){
			if (currentState->num_children != simulatedGame->current_number_moves[simulatedGame->current_player]){

				//if transpositons are used and number of actions is different under the same hash key, then hash function is flawed (because it breaks the markov property - the same state cannot change its number of actions)
				if (this->config_transpositions != (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){
					gmp->Print("ERROR: Player_AI_RL::RL_Single_Episode() : number of allowed actions (%d) does not match memorized number of actions for this state (%d); the HASH function for this game must be flawed (%s, ply %d)\n", simulatedGame->current_number_moves[simulatedGame->current_player], currentState->num_children, simulatedGame->game_name.c_str(), simulatedGame->current_plys);
					return false;
				}
				//if a search tree is grown then it means that the same action may lead to different states (states with different number of actions)
				else{
					//not supported yet
					gmp->Print("WARNING: Player_AI_RL::RL_Single_Episode() : number of allowed actions (%d) does not match memorized number of actions for this state (%d); support for stohastic actions not yet implemented (%s, ply %d), deleting branch\n", simulatedGame->current_number_moves[simulatedGame->current_player], currentState->num_children, simulatedGame->game_name.c_str(), simulatedGame->current_plys);
					memory->Delete_Branch(currentState);
					//this->memory->treeDepth = 0; ??
				}

				// if it is different, then there must be a flaw in the game mechanic (probably an erroneous hash function)
			}
		}

		// control policy for the learning agent
		if (simulatedGame->current_player == this->player_number)
			std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue, rewardGoal)
				= RL_Control_Policy(simulatedGame, currentState, this->config_control_policy, REWARD_MAXIMIZE);

		// opponent model
		else
			std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue, rewardGoal)
				= RL_Opponent_Model(simulatedGame, currentState);

		//Perform selected action on simulated game. Also updates simulated actions counters.
		//Returns: reward following that action, termination flag, hashKey next active state.
		std::tie(reward, isTerminalState, hashKey) = RL_Perform_Action(simulatedGame, actionID);

		// memorize new state (if necessary), link current state and next state, get new state pointer as successorState
		successorState = MemorizeNextState(simulatedGame, currentState, hashKey, onPolicy_selected_child_index);

		// update current state and mark visit
		currentState = successorState;
		MarkStateVisit(currentState);

		// memorize trajectory of current episode, MUST be called after RL_StateMarkVisit()
		AddTrajectoryEntry(actionID, currentState, reward, rewardGoal, onPolicyChildValue, bestChildValue);

		// update memorize structures, includes online policy evaluation
		// MUST be called after RL_StateMarkVisit() and AddTrajectoryEntry()
		HandleEpisodeStep();

		// check whether allowed horizon for simulated games has been met
		if (this->par_simulated_horizon_lenght >= 0){
			if (this->numSimulatedActions_lastEpisode < this->par_simulated_horizon_lenght){
				computeNextAction = false;		//terminate the current episode
			}
		}

		// check whether computational budget has expired (in number of actions)
		if (this->par_num_simulatedActions_perMove >= 0){
			if (this->numSimulatedActions_lastMove < this->par_num_simulatedActions_perMove){
				computeNextAction = false;		//terminate the current episode
				computeNextEpisode = false;		//terminate also the episodes loop
			}
		}

		//check if memory limit was exceeded (depends on allocated nodes)
		if (this->memory->memory_exceeded){
			computeNextAction = false;		//terminate the current episode
			computeNextEpisode = false;		//terminate also the episodes loop
			gmp->Print("WARNING: Player_AI_RL::RL_Single_Episode() : memory budged depleted (limit: %.0f [MB]), at externalMove %d, episode %d, internalMove %d\n", memory->treeMaxMemorySize/1024.0/1024.0, internalGame->current_plys, this->numEpisodes_lastMove, simulatedGame->current_plys);
		}

		// visualization and debug
		Output_SimulatedMove_Level();

	}
	// end of episode

	// final update of memorize structures, includes offline policy evaluation (and last step of online policy evaluation)
	HandleEpisodeEnd();

	// check whether computational budget has expired (in number of episodes)
	if (this->par_num_episodes >= 0){
		if (this->numEpisodes_lastMove >= this->par_num_episodes){
			computeNextEpisode = false;
		}
	}

	// visualization and debug
	Output_Episode_Level();
		
	// return bool whether to simulate another episode (if budget is available)
	return computeNextEpisode;
}

/**
Perform selected action on selected game.
Returns the reward following that action, game termination flag, and the hashKey for the next state (current active state)

*/
std::tuple<double, int, int> Player_AI_RL::RL_Perform_Action(Game_Engine* localGame, int actionID)
{
	// return variables
	double reward;			// reward following the transition
	int isTerminalState;
	int hashKey = -1;

	// get STATE-ACTION hash entry index -> MUST be called BEFORE the move is effectuated, so before game->Play_Move(actionID);
	if (this->config_transpositions == (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_STATEACTIONS))
		hashKey = localGame->HashKey_getCurrentStateAction(actionID);

	// effectuate move on simluated game and observre this player's score
	reward = localGame->score[this->player_number];
	isTerminalState = localGame->Play_Move(actionID);
	reward = localGame->score[this->player_number] - reward;		// reward is represented as the change in score

	// remember highest and lowest observed return
	UpdateKnownReturnBounds(localGame->score[this->player_number]);

	// get STATE hash entry index -> MUST be called AFTER the move was effectuated, so after game->Play_Move(actionID);
	if (this->config_transpositions == (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_STATES))
		hashKey = localGame->HashKey_getCurrentState();

	// update global counters
	this->numSimulatedActions_lastEpisode++;
	this->numSimulatedActions_lastMove++;
	this->numSimulatedActions_total++;
	this->sumSimulatedRewards_lastEpisode = simulatedGame->score[this->player_number];

	// return
	return std::make_tuple(reward, isTerminalState, hashKey);
}

/**
Memorize new state (if necessary) - it is defined by hashKey and/or by selected_child_index.
Link current state and next state.
Return new state pointer as nextState.
*/
HashTree::TreeNode*	Player_AI_RL::MemorizeNextState(Game_Engine* localGame, HashTree::TreeNode* currentState, int hashKey, int selected_child_index)
{
	HashTree::TreeNode* nextState;

	//safety check: if child index is valid and remember last selected child index
	if (currentState != NULL){
		if (selected_child_index >= 0){
			currentState->data->onPolicy_selected_child_index = selected_child_index;
		}
		else{
			gmp->Print("ERROR: Player_AI_RL::MemorizeNextState() : child_seq_index has inccorect value (%d). Control policy may be bugged, it set an erroneous selectedChildIndex.\n", selected_child_index);
			Output_Current_Info("MEMERR    ");
			return false;
		}
	}

	//check if next state was already memorized in a previous episode
	if (this->config_transpositions != (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){
		nextState = memory->hashMap[hashKey];	//if transpositions are used, look in hash table
	}
	else{
		if (currentState != NULL)
			nextState = currentState->children[selected_child_index];	//if transpositions are not used then take the appropriate children
		else
			nextState = NULL;
	}

	//next state is already known
	if (nextState != NULL){

		//update counter of visited nodes that were already known from previous episodes
		this->numVisitedKnownStates_lastEpisode++;

		//if next state was already memorized and transpositions are used then link next state to the current state
		if (this->config_transpositions != (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){
			if (currentState != NULL){
				//this state-action was not yet explored
				if (currentState->children[selected_child_index] == NULL)
					currentState->children[selected_child_index] = nextState;
				//this state-action was already explored before
				else{
					//safety check: if same state-action leads to different states then the task is action-stohastic (action-state transitions with different probabilities) -> this is not yet supported
					if (currentState->children[selected_child_index] != nextState){
						gmp->Print("ERROR: Player_AI_RL::MemorizeNextState() : inequal action trajectory (%p, %p) support for stohastic actions not yet implemented (%s, ply %d), deleting branch\n", currentState->children[selected_child_index], nextState, localGame->game_name.c_str(), localGame->current_plys);
						return false;
					}
				}
			}
			nextState->parent = currentState;	//when transpositions are used, "parent" hold only the LAST parent (it gets overwritten at each visit)
		}

	}

	//next state is not known yet: memorize it and link it to the current state (called from AddNode())
	else{

		// check whether the number of new nodes in this episode has exceeded the allowed threshold
		if ((this->config_num_new_nodes_per_episode < 0) || (this->numNewStates_lastEpisode < this->config_num_new_nodes_per_episode)){
			nextState = AddNode(localGame, hashKey, currentState, selected_child_index);
			this->numNewStates_lastEpisode++;

			// update memory tree statistics
			if ((this->numVisitedKnownStates_lastEpisode + this->numNewStates_lastEpisode) > this->memory->treeDepth)
				this->memory->treeDepth = (this->numVisitedKnownStates_lastEpisode + this->numNewStates_lastEpisode);	// not relevant if transpositions are used
		}

	}

	//return pointer to next state structure (can be NULL)
	return nextState;

}

void Player_AI_RL::UpdateKnownReturnBounds(double lastReturn)
{
	//update min/max bounds for observed returns
	if (lastReturn > this->maximumObservedReturn)
		this->maximumObservedReturn = lastReturn;
	if (lastReturn < this->minimumObservedReturn)
		this->minimumObservedReturn = lastReturn;

	//update min/max bounds for known returns
	if (this->maximumObservedReturn > this->maximumKnownReturn)
		this->maximumKnownReturn = this->maximumObservedReturn;
	if (this->minimumObservedReturn < this->minimumKnownReturn)
		this->minimumKnownReturn = this->minimumObservedReturn;
}

// mark visit of a state
void Player_AI_RL::MarkStateVisit(HashTree::TreeNode* visitedNode)
{
	if (visitedNode != NULL){

		//update total visits counter
		visitedNode->data->num_visited_total += 1.0;
		
		//update visits counter once by episode (equals to total visits counter if transpositions are not used)
		if (visitedNode->data->last_visit_episode < this->numEpisodes_total)
			visitedNode->data->num_visited_episodes += 1.0;

		//update last visit timestamps
		visitedNode->data->last_visit_episode = this->numEpisodes_total;
		visitedNode->data->last_visit_mainGameStep = this->internalGame->current_plys;
		visitedNode->data->last_visit_simulatedGameStep = this->simulatedGame->current_plys;
	}
}

void Player_AI_RL::AddTrajectoryEntry(int action, HashTree::TreeNode* state, double reward, REWARD_GOALS rewardGoal, double onPolicyChildValue, double bestActionValue)
{
	this->trajectory_length++;
	if (this->trajectory_length < this->trajectory_maxLength){
		this->trajectory[this->trajectory_length].action = action;
		this->trajectory[this->trajectory_length].state = state;
		this->trajectory[this->trajectory_length].reward = reward;
		this->trajectory[this->trajectory_length].goal = rewardGoal;
		this->trajectory[this->trajectory_length].bestActionValue = bestActionValue;
		if (onPolicyChildValue == bestActionValue)
			this->trajectory[this->trajectory_length].exploratoryAction = 0;
		else
			this->trajectory[this->trajectory_length].exploratoryAction = 1;
		if (state != NULL)
			this->trajectory[this->trajectory_length].stateVisitsTotal = state->data->num_visited_total;
		else
			this->trajectory[this->trajectory_length].stateVisitsTotal = 0.0;
	}
	else{
		gmp->Print("ERROR: Player_AI_RL::AddTrajectoryEntry() : Trajectory counter invalid value %d / %d\n", this->trajectory_length, this->trajectory_maxLength);
	}
}

std::tuple<int, int, int, double, double, Player_AI_RL::REWARD_GOALS> Player_AI_RL::RL_Control_Policy(Game_Engine* localGame, HashTree::TreeNode* currentState, CONTROL_POLICIES policy, REWARD_GOALS rewardGoal)
{
	int actionID;
	int onPolicy_selected_child_index;
	int bestChild_index;
	double onPolicyChildValue;
	double bestChildValue;

	if (policy == CONTROL_EGREEDY)
		std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue)
		= RL_Control_Egreedy(localGame, currentState, this->par_egreedy_e, rewardGoal);
	else if (policy == CONTROL_UCB)
		std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue)
		= RL_Control_UCB(localGame, currentState, this->par_ucb_c, rewardGoal);

	return std::make_tuple(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue, rewardGoal);
}

std::tuple<int, int, int, double, double, Player_AI_RL::REWARD_GOALS> Player_AI_RL::RL_Opponent_Model(Game_Engine* localGame, HashTree::TreeNode* currentState)
{

	int actionID;
	int onPolicy_selected_child_index;
	int bestChild_index;
	double onPolicyChildValue;
	double bestChildValue;
	REWARD_GOALS rewardGoal;

	// check opponent's alignment
	if (this->config_opponent_alignment == OPPONENT_ADVERSARY)
		rewardGoal = REWARD_MINIMIZE;
	else if (this->config_opponent_alignment == OPPONENT_COOPERATIVE)
		rewardGoal = REWARD_MAXIMIZE;

	// check opponent's policy
	if (this->config_opponent_policy == OPPONENT_SELFPLAY)
		std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue, rewardGoal) = RL_Control_Policy(localGame, currentState, this->config_control_policy, rewardGoal);
	else if (this->config_opponent_policy == OPPONENT_RANDOM)
		std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue) = RL_Control_Egreedy(localGame, currentState, 1.0, rewardGoal);
	else if (this->config_opponent_policy == OPPONENT_GREEDY)
		std::tie(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue) = RL_Control_Egreedy(localGame, currentState, 0.0, rewardGoal);

	return std::make_tuple(actionID, onPolicy_selected_child_index, bestChild_index, onPolicyChildValue, bestChildValue, rewardGoal);
}

HashTree::TreeNode*	Player_AI_RL::AddNode(Game_Engine* localGame, int hashKey, HashTree::TreeNode* parent, int child_seq_index)
{

	//create new data structure
	HashTree::TreeNode* newNode = new HashTree::TreeNode();

	//update hash table entry
	if (this->config_transpositions != (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED))
		memory->hashMap[hashKey] = newNode;

	//update parent and link tree nodes
	if (parent == NULL){

		//check if we are creating a new tree root node
		if (this->config_transpositions == (Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED)){
			//safety check #1
			if (this->memory->root != NULL){
				gmp->Print("WARNING: Player_AI_RL::AddNode() : Node without parent created, despite root is not NULL. Erasing whole tree beneath current root and seeting new node as new root.");
				this->memory->Delete_Branch(this->memory->root);
				this->memory->treeDepth = 0;
			}

			//safety check #2
			if ((this->memory->numAllocNodes != 0) || (this->memory->allocMemorySize != 0)){
				gmp->Print("ERROR: Player_AI_RL::AddNode() : tree incorrectly deleted after changing root node : remaining nodes %d, remaining memory size %.0f [B]\n", this->memory->numAllocNodes, this->memory->allocMemorySize);
			}

			//set new root
			this->memory->root = newNode;
			this->memory->treeDepth = 1;
		}

	}
	else{

		//safety check
		if (child_seq_index >= 0){
			//link parent to children
			parent->children[child_seq_index] = newNode;
		}
		else{
			gmp->Print("ERROR: Player_AI_RL::AddNode() : child_seq_index has inccorect value (%d). Control policy may be bugged, it set an erroneous selectedChildIndex.\n", child_seq_index);
		}
	}
	newNode->hashKey = hashKey;		//index in hash table of transpositions (holds invalid value if transpositions are not in use)
	newNode->parent = parent;		//warning: hash table entries remember only first parent, so don't rely on this value when backpropagating
	newNode->in_parent_seq_index = child_seq_index;

	newNode->num_children = localGame->current_number_moves[localGame->current_player];
	newNode->children = new HashTree::TreeNode*[newNode->num_children];
	newNode->childrenActions = new int[newNode->num_children];

	localGame->Make_Moves_List();
	for (int c = 0; c < newNode->num_children; c++){
		newNode->children[c] = NULL;
		newNode->childrenActions[c] = localGame->current_moves_list[localGame->current_player][c];
	}

	newNode->data = new HashTree::StateActionRecord();
	newNode->data->actionID = localGame->history_moves[localGame->current_plys];	//last move ID

	//increase memory counters
	memory->numAllocNodes++;
	memory->allocMemorySize += (sizeof(HashTree::TreeNode) + newNode->num_children * sizeof(HashTree::TreeNode*) + sizeof(HashTree::StateActionRecord));
	if (memory->allocMemorySize > memory->treeMaxMemorySize){
		memory->memory_exceeded = true;
		gmp->Print("WARNING: Player_AI_RL::AddNode() : tree size exceeded : memory size %.0f [B], allowed size %.0f\n", memory->allocMemorySize, memory->treeMaxMemorySize);
	}
	//printf("size: %0.f\n", memory->treeMaxMemorySize);

	ResetNode(newNode);
	return newNode;

}

void Player_AI_RL::ResetNode(HashTree::TreeNode* newNode)
{
	newNode->data->Q_value = this->par_td_initVal;
	newNode->data->offline_delta_Q = 0.0;
	newNode->data->Z_traceTag = -1;

	newNode->data->num_visited_total = 0.0;
	newNode->data->num_visited_episodes = 1.0;		//must be set on 1 because last_visit_episode is initialized to the value of current episode (wouldn't get updated the first time)
	newNode->data->last_estimated_value = NAN;


	newNode->data->maxObservedReturn = -DBL_MAX;
	newNode->data->minObservedReturn = DBL_MAX;
	newNode->data->maxBranchQval = this->par_td_initVal;
	newNode->data->minBranchQval = this->par_td_initVal;
	newNode->data->maxChildQval = this->par_td_initVal;
	newNode->data->minChildQval = this->par_td_initVal;

	newNode->data->created_mainGameStep = this->internalGame->current_plys;
	newNode->data->created_episode = this->numEpisodes_total;
	newNode->data->created_simulatedGameStep = this->simulatedGame->current_plys;

	newNode->data->last_visit_mainGameStep = this->internalGame->current_plys;
	newNode->data->last_visit_episode = this->numEpisodes_total;
	newNode->data->last_visit_simulatedGameStep = this->simulatedGame->current_plys;

	newNode->data->onPolicy_selected_child_index = -1;
	newNode->data->offPolicy_selected_child_value = NAN;
}

// procedure called after each step/action in the episode
void Player_AI_RL::HandleEpisodeStep()
{

	// online policy evaluation (update value function)
	if (this->config_TDupdateType == TD_UPDATE_ONLINE){
		RL_TDsingleBackup(this->trajectory_length - 1, this->par_task_gamma, this->par_td_alpha, this->par_td_lambda);
		UpdateTrajectoryBounds();	//refresh min/max Q-values (and target values) - UCB control policy needs this for normalization of Q-value
	}
	else{

		//if game is continuous then offline (after termination) updates are not possible, thus a periodic offline (batch) update is executed
		if (internalGame->is_episodic == false)
		{
			// batch update after a periodic interval
			if (this->trajectory_length >= config_nonEpisodicTasks_updateInterval){
				RL_TDofflineBackup();
				this->trajectory_length = 0;
				this->numNewStates_lastEpisode = 0;
				//TOIMP: implement to improve learning performance on continuing tasks when updating offline (this may naver be used), so don't bother, but otherwise the idea is: it could be improved by never really erasing the whole trajectory (like now that we put the conuter on zero), but the last X samples could always remain in the memory
			}

		}
	}

}

// procedure called after episode termination (after terminal state is reached)
void Player_AI_RL::HandleEpisodeEnd()
{
	// last (after episode end) online backup
	if (this->config_TDupdateType == TD_UPDATE_ONLINE){
		RL_TDsingleBackup(this->trajectory_length, this->par_task_gamma, this->par_td_alpha, this->par_td_lambda);
		UpdateTrajectoryBounds();	//refresh min/max Q-values (and target values) - UCB control policy needs this for normalization of Q-value
	}
	// offline (batch) policy evaluation (update value function)
	else{
		RL_TDofflineBackup();
	}

	// increase global counters
	this->numEpisodes_lastMove++;
	this->numEpisodes_total++;
	this->sumSimulatedRewards_lastMove += simulatedGame->score[this->player_number];
	this->sumSimulatedRewards_total += simulatedGame->score[this->player_number];

}

// offline (batch) policy evaluation (update value function)
void Player_AI_RL::RL_TDofflineBackup()
{
	if ((this->config_TDupdateType == TD_UPDATE_OFFLINE) || (this->config_TDupdateType == TD_UPDATE_OFFLINE_INPLACE)){
		
		//backup all steps in the trajectory
		for (int t = 0; t <= this->trajectory_length; t++)
			RL_TDsingleBackup(t, this->par_task_gamma, this->par_td_alpha, this->par_td_lambda);

		//if Q-value updates were not inplace, then apply the changes at this point
		if (this->config_TDupdateType != TD_UPDATE_OFFLINE_INPLACE)
			UpdateTrajectoryOfflineValues();

	}
	//else{	//TODO: TD_UPDATE_OFFLINE_ASYNC
	//}

	UpdateTrajectoryBounds();	//refresh min/max Q-values (and target values) - UCB control policy needs this for normalization of Q-value
}

// apply the value changes that were stored in the offline backups
void Player_AI_RL::UpdateTrajectoryOfflineValues()
{
	HashTree::TreeNode* node;

	//iterate backwards through trajectory (from last state to initial state)
	for (int t = this->trajectory_length; t >= 0; t--){
		node = this->trajectory[t].state;
		if (node != NULL){
			node->data->Q_value += node->data->offline_delta_Q;
			node->data->Q_value = NumericalErrorCorrection(node->data->Q_value);	//check for numerical error
			node->data->offline_delta_Q = 0.0;
		}
	}
}

// refresh min/max Q-values (and target values) - UCB control policy needs this for normalization of Q-value
void Player_AI_RL::UpdateTrajectoryBounds()
{
	double sumRewards = 0.0;		//the return (sum of rewards)
	double maxQval = -DBL_MAX;		//highest Q-value
	double minQval = DBL_MAX;		//lowest Q-value

	HashTree::TreeNode* node;
	double nodeQval = this->par_td_initVal;

	//iterate backwards through trajectory (from last state to initial state)
	for (int t = this->trajectory_length; t >= 0; t--){

		//update return
		sumRewards *= this->par_task_gamma;
		sumRewards += this->trajectory[t].reward;

		node = this->trajectory[t].state;
		if (node != NULL){

			//update max/min return for current state
			if (sumRewards > node->data->maxObservedReturn)
				node->data->maxObservedReturn = sumRewards;
			if (sumRewards < node->data->minObservedReturn)
				node->data->minObservedReturn = sumRewards;

			//update max/min Q-value for current state's branch (all known paths from current state towards the end)
			if (maxQval > node->data->maxBranchQval)
				node->data->maxBranchQval = maxQval;
			if (minQval < node->data->minBranchQval)
				node->data->minBranchQval = minQval;

			//update max/min Q-value for current state's children
			if (nodeQval > node->data->maxChildQval)
				node->data->maxChildQval = nodeQval;
			if (nodeQval < node->data->minChildQval)
				node->data->minChildQval = nodeQval;

			//update propagated max/min Q-value --- self Qvalue bound is not counted when setting bounds for own state, but only upwards to the root (initial state)
			nodeQval = node->data->Q_value;
			if (nodeQval > maxQval)
				maxQval = nodeQval;
			if (nodeQval < minQval)
				minQval = nodeQval;
		}
	}

}

/**
A single TD(lambda) backup.

WARNING: argument trajectory_index must have a value between 0 and less than this->trajectory_counter
*/

void Player_AI_RL::RL_TDsingleBackup(int trajectory_index, double gamma, double alpha, double lambda, char* printLinePrefix)
{
	//if (this->numEpisodes_total == 115)
	//	this->config_output_TDlambdaBackup = 2;

	HashTree::TreeNode* node;
	HashTree::TreeNode* nextNode;
	HashTree::TreeNode* backupNode;
	double stateVal;
	double nextStateVal;
	double reward, TDerror;
	int exploratory_move_trace_reset = 0;

	//get state in trajectory
	node = this->trajectory[trajectory_index].state;
	stateVal = RL_GetAssumedStateValue(node);

	//needed for replacing traces
	if (node != NULL)
		node->data->Z_traceTag = -1;

	//TODO Q_TRACE_ACTIONEXCLUSIVE
	//remember last action taken in parent (is this already memorized?)
	//if(this->config_trace_type == Q_TRACE_ACTIONEXCLUSIVE)
	//if lastAction != currentAction (so probably a parent will need to be checked)
	//    node->data->Z_traceTag = this->this->trajectory_length + 1 //this record should not be updated anymore in this episode

	//is state non-terminal?
	if (trajectory_index < this->trajectory_length){

		//get next state in trajectory
		nextNode = this->trajectory[trajectory_index + 1].state;
		nextStateVal = RL_GetAssumedStateValue(nextNode);

		//off-policy TD: check whether best action was choosen
		if (this->config_policy_evaluation == EVALUATION_TDLAMBDA_OFFPOLICY_Q_LEARNING)
		{
			//get the value of the best child
			if (this->config_offpolicy_backup_recheck_best == false){
				//memorized by the control policy selection check)
				nextStateVal = this->trajectory[trajectory_index + 1].bestActionValue;
			}
			else{
				//compute the value of the best child at this moment (might have changed since the control policy checked, only in case when transpositions are used and offline inplace backups, or when using async backups)
				node->data->offPolicy_selected_child_value = RL_GetBestActionValue(node, this->trajectory[trajectory_index + 1].goal);	//get best-valued node (by greedy policy)
				if (node->data->offPolicy_selected_child_value > nextStateVal){
					nextStateVal = node->data->offPolicy_selected_child_value;
					this->trajectory[trajectory_index + 1].exploratoryAction = 1;
				}
			}
		}

		//set eligibility traces prior to this state to zero if action is exploratory?
		if (this->config_trace_exploratory_reset == Q_TRACE_EXPLORATORY_RESET_ENABLED)
			exploratory_move_trace_reset = this->trajectory[trajectory_index + 1].exploratoryAction;	//true or false
	}
	//if state is terminal, then it's value is zero and move cannot be exploratory
	else{
		nextStateVal = 0.0;
		exploratory_move_trace_reset = 0;
	}


	//get reward for transition to new state
	reward = this->trajectory[trajectory_index].reward;

	//compute the target value for the backup
	TDerror = reward + par_task_gamma * nextStateVal - stateVal;

	//visualization: output TDerror before backup
		Output_TDbackup1(trajectory_index, TDerror, nextStateVal, stateVal, exploratory_move_trace_reset, printLinePrefix);

	//backup the TDerror through all visited states
	if ((TDerror > SMALLEST_TDERROR) || (TDerror < -SMALLEST_TDERROR)){
		double trace = 1.0;
		//interrupt backup if the trace is too small
		for (int b = trajectory_index; (b >= this->exploratory_move_trace_cutOff) && (trace > EPSILON_TRACE_CUTOFF); b--){
			
			backupNode = this->trajectory[b].state;

			//visualization: output backup details
			Output_TDbackup21(b, trajectory_index, trace, backupNode, printLinePrefix);

			//effectuate backup
			if (backupNode != NULL){
				
				//update node (state or state-action) value
				if ((this->config_trace_type == Q_TRACE_ACCUMULATING) || (backupNode->data->Z_traceTag < trajectory_index))		// prevents to update the same node multiple times in a trajectory (hence the replacing traces mechanics)
				{
					//set the step rate "alpha" to calculate value as statistical mean (default for Monte Carlo contorl methods)
					if (this->config_alpha_type == ALPHA_MONTE_CARLO){
						double num_visits;
						if (this->config_trace_type == Q_TRACE_ACCUMULATING)
							num_visits = this->trajectory[b].stateVisitsTotal;		// every-visit MC
						else
							num_visits = backupNode->data->num_visited_episodes;	// first-visit MC
						
						//safety check
						if (num_visits <= 0.0){	
							gmp->Print("ERROR: Player_AI_RL::RL_TDlambdaBackup() : invalid visits value %f\n", num_visits);
							Output_Current_Info("TDERR    ");
						}

						//step rate for statistical mean
						alpha = 1.0 / backupNode->data->num_visited_episodes;
					}

					//update value by TD(lambda)
					if ((this->config_TDupdateType == TD_UPDATE_ONLINE) || (this->config_TDupdateType == TD_UPDATE_OFFLINE_INPLACE)){
						backupNode->data->Q_value += (alpha * trace * TDerror);			// inplace update of Q-value
						backupNode->data->Q_value = NumericalErrorCorrection(backupNode->data->Q_value);	//check for numerical error
					}
					else
						backupNode->data->offline_delta_Q += (alpha * trace * TDerror);	// temporary stored delta of Q-value (added to Q-value at a later time)

					//safety check
					if (this->minimumKnownReturn < this->maximumKnownReturn){
						double checkVal;
						if ((this->config_TDupdateType == TD_UPDATE_ONLINE) || (this->config_TDupdateType == TD_UPDATE_OFFLINE_INPLACE))
							checkVal = backupNode->data->Q_value;
						else
							checkVal = backupNode->data->Q_value + backupNode->data->offline_delta_Q;
						if ((checkVal > this->maximumKnownReturn) || (checkVal < this->minimumKnownReturn)){
							gmp->Print("\nWARNING: Player_AI_RL::RL_TDlambdaBackup() : Q-value out of return bounds %.10f      (min %.10f , max %.10f)     (extMov %d, epis %d, simMov %d)    ", checkVal, this->minimumKnownReturn, this->maximumKnownReturn, this->internalGame->current_plys, this->numEpisodes_lastMove, this->simulatedGame->current_plys);
						}
					}

					//mark update on node, needed for replacing traces mechanics
					backupNode->data->Z_traceTag = trajectory_index;
				}

			}

			//decay trace
			trace *= (gamma * lambda);

			//visualization: output backup details
			Output_TDbackup22(b, backupNode, alpha, printLinePrefix);

		}
	}

	//Watkin's Q(lambda) identified an exploratory move: eligibility traces for all states met until now will be zeroed 
	if (exploratory_move_trace_reset == 1)
		this->exploratory_move_trace_cutOff = trajectory_index + 1;

}

//support function to return the value of a node, considering whether the node was not visited yet then a certain initial value is assumed
double Player_AI_RL::RL_GetAssumedStateValue(HashTree::TreeNode* node)
{
	double stateVal;
	if (node != NULL){
		stateVal = node->data->Q_value;
	}
	else{
		if (this->config_rollout_assumption == ROLLOUT_NODE_ASSUME_INITIAL_VALUE){
			stateVal = this->par_td_initVal;
		}
	}
	return stateVal;
}

//not needed at the moment (was implemented as part of Egreedy and UCB)
double Player_AI_RL::RL_GetBestActionValue(HashTree::TreeNode* node, REWARD_GOALS goal)
{
	//if an off-policy TD method is used (Q-learning), then find the value of the best child
	if (this->config_policy_evaluation == EVALUATION_TDLAMBDA_OFFPOLICY_Q_LEARNING)
	{
		if (node != NULL){
			node->data->offPolicy_selected_child_value = -DBL_MAX;
			for (int c = 0; c < node->num_children; c++){
				HashTree::TreeNode* child = node->children[c];
				double stateValue;

				// check whether state was not visited yet (then use default initial value)
				if (child == NULL)
					stateValue = this->par_td_initVal;
				else
					stateValue = child->data->Q_value;

				//estimate value in base on specified goal
				double estimatedValue;
				if (goal == REWARD_MAXIMIZE)
					estimatedValue = stateValue;
				else if (goal == REWARD_MINIMIZE)
					estimatedValue = -stateValue;
				else
					gmp->Print("ERROR Player_AI_RL::RL_GetBestActionValue(): goal unknown!\n");

				//find best action by a fully-greedy policy
				if (estimatedValue > node->data->offPolicy_selected_child_value)
					node->data->offPolicy_selected_child_value = estimatedValue;
			}

			//correct if the value was negated
			if (goal == REWARD_MINIMIZE)
				node->data->offPolicy_selected_child_value = -node->data->offPolicy_selected_child_value;
		}
		else{
			node->data->offPolicy_selected_child_value = this->par_td_initVal;
		}
	}

	return node->data->offPolicy_selected_child_value;

}

//numerical error check
double Player_AI_RL::NumericalErrorCorrection(double value)
{
	double retVal = value;
	if ((this->numerical_correction_possible == 1) && (this->config_numerical_correction != NUM_CORRECTION_DISABLED)){
		if (this->minimumKnownReturn < this->maximumKnownReturn){
			if (value > this->maximumKnownReturn)
				retVal = this->maximumKnownReturn;
			else if (value < this->minimumKnownReturn)
				retVal = this->minimumKnownReturn;
			if (this->config_numerical_correction == NUM_CORRECTION_ENABLED_WARNINGS){
				if (retVal != value){
					gmp->Print("WARNING: Player_AI_RL::NumErrorCorrect(): Q-value %.10f out of return bounds, correcting to     (min %.10f , max %.10f)     (extMov %d, epis %d, simMov %d)\n", value, this->minimumKnownReturn, this->maximumKnownReturn, this->internalGame->current_plys, this->numEpisodes_lastMove, this->simulatedGame->current_plys);
				}
			}
		}
	}
	return retVal;
}

std::tuple<int, int, int, double, double> Player_AI_RL::RL_Control_Egreedy(Game_Engine* localGame, HashTree::TreeNode* currentState, double par_epsilon, REWARD_GOALS goal)
{
	int selectedActionID = -1;
	int selectedChildIndex = -1;
	int bestChildIndex = -1;
	double selectedChildValue = NAN;
	double bestChildValue = NAN;

	if (currentState != NULL){

		double stateValue;
		double estimatedValue;
		double bestEstimatedValue;

		// loop through all children and find best one by a fully greedy policy
		bestEstimatedValue = -DBL_MAX;
		for (int c = 0; c < currentState->num_children; c++){

			HashTree::TreeNode* child = currentState->children[c];

			// check whether state was not visited yet (then use default initial value)
			if (child == NULL)
				stateValue = this->par_td_initVal;
			else
				stateValue = child->data->Q_value;

			//estimate value in base on specified goal
			if (goal == REWARD_MAXIMIZE)
				estimatedValue = stateValue;
			else if (goal == REWARD_MINIMIZE)
				estimatedValue = -stateValue;
			else
				gmp->Print("ERROR Player_AI_RL::RL_Control_Egreedy(): goal unknown!\n");

			//store estimated value in local record
			if (child != NULL)
				child->data->last_estimated_value = estimatedValue;

			//remember best estimated child
			double tieBraker = EPSILON_TIEBRAKER * (double)rand() * ((double)(RAND_MAX - 1) / (RAND_MAX)) / (RAND_MAX);
			if (estimatedValue + tieBraker > bestEstimatedValue){
				bestEstimatedValue = estimatedValue + tieBraker;
				selectedChildIndex = c;
				selectedChildValue = stateValue;
			}

		}

		//the best child corresponds to the one found by the fully greedy policy
		bestChildIndex = selectedChildIndex;
		bestChildValue = selectedChildValue;

		//choose random action with epsilon chance
		double epsilonChance = (double)rand() * ((double)(RAND_MAX - 1) / (RAND_MAX)) / (RAND_MAX);
		if (epsilonChance < par_epsilon){
			selectedChildIndex = (int)((double)(currentState->num_children) * ((double)rand() * ((double)(RAND_MAX - 1) / (RAND_MAX)) / (RAND_MAX)));
			if (currentState->children[selectedChildIndex] != NULL)
				selectedChildValue = currentState->children[selectedChildIndex]->data->Q_value;
			else
				selectedChildValue = this->par_td_initVal;
		}

		//get actionID (bound to current game)
		selectedActionID = currentState->childrenActions[selectedChildIndex];
	}
	else{
		//if there is no record of current state, then select random action (assumes equal value of all successor states)
		selectedActionID = localGame->Select_Move_Random();
		selectedChildValue = this->par_td_initVal;
		bestChildValue = this->par_td_initVal;
	}

	return std::make_tuple(selectedActionID, selectedChildIndex, bestChildIndex, selectedChildValue, bestChildValue);
}

std::tuple<int, int, int, double, double> Player_AI_RL::RL_Control_UCB(Game_Engine* localGame, HashTree::TreeNode* currentState, double par_C, REWARD_GOALS goal)
{
	int selectedActionID = -1;
	int selectedChildIndex = -1;
	int bestChildIndex = -1;
	double selectedChildValue = NAN;
	double bestChildValue = NAN;

	if (currentState != NULL){

		double stateValue, estimatedValue;
		double bestEstimatedValue;
		double sumVisits;

		//UCB first pass: get the sum of individual tries or to choose a random untried action
		int noVisitsTieBreaker = INT_MIN;
		sumVisits = 0.0;
		bestEstimatedValue = -DBL_MAX;
		for (int c = 0; c < currentState->num_children; c++){

			HashTree::TreeNode* child = currentState->children[c];

			// check whether action was not tried yet (then use default initial value)
			double childVisits = 0.0;
			if (child == NULL){
				stateValue = this->par_td_initVal;
			}
			else{
				//get action value and number of tries
				stateValue = child->data->Q_value;
				if (config_ucb_visit_type == UCB_VISITS_TOTAL)
					childVisits = child->data->num_visited_total;
				else
					childVisits = child->data->num_visited_episodes;
			}
			sumVisits += childVisits;

			//estimate max value in base on specified goal
			if (goal == REWARD_MAXIMIZE)
				estimatedValue = stateValue;
			else if (goal == REWARD_MINIMIZE)
				estimatedValue = -stateValue;
			else
				gmp->Print("ERROR Player_AI_RL::RL_Control_UCB(): goal unknown!\n");

			//remember best estimated action by a fully greedy policy (required for off-policy TD learning methods)
			if (estimatedValue > bestEstimatedValue){
				bestEstimatedValue = estimatedValue;
				bestChildIndex = c;
				bestChildValue = stateValue;
			}

			//action was not yet tried, thus by UCB it gets a POSITIVE INFINITE value
			if (childVisits == 0.0){
				int tieBraker = rand();
				if (tieBraker > noVisitsTieBreaker){
					noVisitsTieBreaker = tieBraker;
					selectedChildIndex = c;
				}
			}
		}

		//UCB second pass: if all actions were already tried at least once, find best according to the UCB equation (this also means that all children are already allocated and thus cannot be NULL)
		if (selectedChildIndex == -1){

			//get normalization bounds
			double minNormValue = DBL_MAX;
			double maxNormValue = -DBL_MAX;
			if (config_ucb_norm_type != UCB_NORMALIZATION_GLOBAL){
				if (config_ucb_norm_local == UCB_NORMALIZATION_LOCAL_OBSERVED){
					maxNormValue = currentState->data->maxObservedReturn;
					minNormValue = currentState->data->minObservedReturn;
				}
				else if (config_ucb_norm_local == UCB_NORMALIZATION_LOCAL_QVAL){
					maxNormValue = currentState->data->maxBranchQval;
					minNormValue = currentState->data->minBranchQval;
				}
				else if (config_ucb_norm_local == UCB_NORMALIZATION_LOCAL_CHILDREN){
					maxNormValue = currentState->data->maxChildQval;
					minNormValue = currentState->data->minChildQval;
				}
			}
			if ((config_ucb_norm_type == UCB_NORMALIZATION_GLOBAL) || ((minNormValue >= maxNormValue) && (config_ucb_norm_type == UCB_NORMALIZATION_LOCAL_GLOBAL))){
				if (config_ucb_norm_global == UCB_NORMALIZATION_GLOBAL_KNOWN){
					maxNormValue = this->maximumKnownReturn;
					minNormValue = this->minimumKnownReturn;
				}
				else if (config_ucb_norm_global == UCB_NORMALIZATION_GLOBAL_OBSERVED){
					maxNormValue = this->maximumObservedReturn;
					minNormValue = this->minimumObservedReturn;
				}
			}

			//are normalization bounds valid?
			if (minNormValue < maxNormValue){

				double childVisits;
				double normalizedValue;

				bestEstimatedValue = -DBL_MAX;
				for (int c = 0; c < currentState->num_children; c++){
					HashTree::TreeNode* child = currentState->children[c];

					//get action value and number of tries
					stateValue = child->data->Q_value;
					if (config_ucb_visit_type == UCB_VISITS_TOTAL)
						childVisits = child->data->num_visited_total;
					else
						childVisits = child->data->num_visited_episodes;

					//normalize
					normalizedValue = (stateValue - minNormValue) / (maxNormValue - minNormValue);

					//consider goal
					if (goal == REWARD_MAXIMIZE)
						estimatedValue = normalizedValue;
					else if (goal == REWARD_MINIMIZE)
						estimatedValue = 1.0 - normalizedValue;
					else
						gmp->Print("ERROR Player_AI_RL::RL_Control_UCB(): goal unknown!\n");

					//UCB equation
					//the equation cannot return an invalid value due to the "UCB first pass" above that skips the "UCB second pass" loop as soon as a single (child->data->num_visits == 0) holds
					estimatedValue = estimatedValue + par_C * sqrt(log(sumVisits) / childVisits);

					//store estimated value in local record
					child->data->last_estimated_value = estimatedValue;

					double tieBraker = EPSILON_TIEBRAKER * (double)rand() * ((double)(RAND_MAX - 1) / (RAND_MAX)) / (RAND_MAX);
					if (estimatedValue + tieBraker > bestEstimatedValue){
						bestEstimatedValue = estimatedValue + tieBraker;
						selectedChildIndex = c;
						selectedChildValue = stateValue;
					}
				}

			}
			else{
				//if normalization bounds are not valid, then this means that all actions lead to same reward, so choice can be random
				selectedChildIndex = (int)((double)rand() * ((double)(RAND_MAX - 1) / (RAND_MAX)) / (RAND_MAX)* (currentState->num_children));
				selectedChildValue = currentState->children[selectedChildIndex]->data->Q_value;
			}
		}
		//an action with no visits was selected, thus it still holds the intial value
		else{
			selectedChildValue = this->par_td_initVal;
		}

		selectedActionID = currentState->childrenActions[selectedChildIndex];
	}
	else{
		//if there is no record of current state, then select random action (assume equal value of all successor states)
		selectedActionID = localGame->Select_Move_Random();
		selectedChildValue = this->par_td_initVal;
		bestChildValue = this->par_td_initVal;
	}

	return std::make_tuple(selectedActionID, selectedChildIndex, bestChildIndex, selectedChildValue, bestChildValue);
}

void Player_AI_RL::Output_ExternalMove_Level()
{
	int depth = 1;
	if (this->config_output_depth >= depth){
		Output_Batch(depth);
		gmp->Print("\n\n");
		gmp->Print("////// ++++++++++++++++++++++++ //////\n");
		gmp->Print("////// ++++++++++++++++++++++++ ////// END OF EPISODE BATCH FOR EXTERNAL MOVE %d\n", this->internalGame->current_plys);
		gmp->Print("////// ++++++++++++++++++++++++ //////\n");
		gmp->Print("\n");
		if (this->config_output_pause >= depth)
			cin.get();
	}
}

void Player_AI_RL::Output_Episode_Level()
{
	int depth = 2;
	if (this->config_output_depth >= depth){
		if (this->config_output_simGameState >= depth)
			this->simulatedGame->Output_Board_State("SIMG    ");
		Output_Batch(depth);
		gmp->Print("\n\n");
		gmp->Print("//// ************************ //// END OF EPISODE %d (extMove %d)\n", this->numEpisodes_lastMove, this->internalGame->current_plys);
		gmp->Print("//// ************************ ////\n");
		gmp->Print("\n");
		if (this->config_output_pause >= depth)
			cin.get();
	}
}

void Player_AI_RL::Output_SimulatedMove_Level()
{
	int depth = 3;
	if (this->config_output_depth >= depth){
		if (this->config_output_simGameState >= depth)
			this->simulatedGame->Output_Board_State("SIMG    ");
		Output_Batch(depth);
		gmp->Print("\n\n");
		gmp->Print("// ------------- // END OF SIMULATED GAME PLY %d (episode %d, extMove %d)\n", this->simulatedGame->current_plys, this->numEpisodes_lastMove, this->internalGame->current_plys);
		gmp->Print("\n");
		if (this->config_output_pause >= depth)
			cin.get();
	}
}

void Player_AI_RL::Output_Batch(int depth)
{
	if (this->config_output_trajectory >= depth)
		Output_Trajectory();
	if (this->config_output_memory >= depth)
		Output_Memory();
	if (this->config_output_summary >= depth)
		Output_Summary();
	if (this->config_output_currentInfo >= depth)
		Output_Current_Info();
}

void Player_AI_RL::Output_Current_Info(char* printLinePrefix)
{
	//remember how many times this procedure was invoked since object was initialized
	this->outInfoCounter++;

	if (printLinePrefix == NULL)
		printLinePrefix = "CINF";

	gmp->Print("\n");
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("BEGIN Output_Current_Info() -- #%d --", this->outInfoCounter);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("                  MemoryNumNodes    %d", this->memory->numAllocNodes);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("                     Memory Size    %.0f MB (max %.0f MB)", (this->memory->allocMemorySize / 1024.0 / 1024.0), (this->memory->treeMaxMemorySize / 1024.0 / 1024.0));
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("     Index current external move    %d", this->internalGame->current_plys);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("           Index current episode    %d", this->numEpisodes_lastMove);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("    Index current simulated move    %d", this->simulatedGame->current_plys);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("    Last external move root node    ");	memory->Output_SingleNode_LineStats(this->internalGameActiveNode);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter);
	gmp->Print("\n%s -%d-    ", printLinePrefix, this->outInfoCounter); gmp->Print("END   Output_Current_Info()");
	gmp->Print("\n");
}

void Player_AI_RL::Output_Summary(char* printLinePrefix)
{
	if (printLinePrefix == NULL)
		printLinePrefix = "SUMM    ";

	gmp->Print("\n");
	gmp->Print("\n%s", printLinePrefix); gmp->Print("BEGIN Output_Summary()");
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("                            lastEpis  lastMove     total");
	gmp->Print("\n%s", printLinePrefix); gmp->Print("    num simulated episodes  %8d  %8d  %8d", 1, this->numEpisodes_lastMove, this->numEpisodes_total);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("     num simulated actions  %8d  %8d  %8d", this->numSimulatedActions_lastEpisode, this->numSimulatedActions_lastMove, this->numSimulatedActions_total);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("gathered simulated rewards  % 8.2f  % 8.2f  % 8.2f", this->sumSimulatedRewards_lastEpisode, this->sumSimulatedRewards_lastMove, this->sumSimulatedRewards_total);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("     num new state records  %8d", this->numNewStates_lastEpisode);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("  num visited known states  %8d", this->numVisitedKnownStates_lastEpisode);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("END   Output_Summary()");
	gmp->Print("\n");

}

void Player_AI_RL::Output_Memory(char* printLinePrefix)
{
	if (printLinePrefix == NULL)
		printLinePrefix = "MEMS    ";

	gmp->Print("\n");
	gmp->Print("\n%s", printLinePrefix); gmp->Print("BEGIN Output_Memory_State()");
	gmp->Print("\n%s", printLinePrefix);

	if (this->config_transpositions != Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_DISABLED){
		this->memory->Output_HashTable(printLinePrefix);
	}
	else{
		this->memory->Output_Tree(printLinePrefix, this->numEpisodes_total - 1, this->config_output_memory_treeDepth);
	}

	gmp->Print("\n%s", printLinePrefix); gmp->Print("END   Output_Memory_State()");
	gmp->Print("\n");
}

void Player_AI_RL::Output_Trajectory(char* printLinePrefix)
{
	if (printLinePrefix == NULL)
		printLinePrefix = "TRAJ    ";

	gmp->Print("\n");
	gmp->Print("\n%s", printLinePrefix); gmp->Print("BEGIN Output_Trajectory()");
	gmp->Print("\n%s", printLinePrefix);

	//output headers
	gmp->Print("\n%s", printLinePrefix); gmp->Print("ExtMove %d  Episode %d  (totalEpisodes %d)", this->internalGame->current_plys, this->numEpisodes_lastMove, this->numEpisodes_total);
	gmp->Print("\n%s", printLinePrefix); gmp->Print("Trajectory length %d (max %d)", this->trajectory_length + 1, this->trajectory_maxLength);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("\n%s", printLinePrefix);
	gmp->Print("   index");
	gmp->Print("  simPly");
	for (int h = 0; h < 7; h++){
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordLabels[h]);
	}
	gmp->Print("  "); gmp->Print(HashTree::TreeNodeAtrLabels[7]);
	gmp->Print("  "); gmp->Print(HashTree::StateActionAtrLabels[16]);
	gmp->Print("  "); gmp->Print(HashTree::StateActionAtrLabels[8]);

	gmp->Print("\n%s", printLinePrefix);

	//output records
	for (int t = 0; t <= this->trajectory_length; t++){
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[0], t);
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[0], simulatedGame->current_plys - this->trajectory_length + t);
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[0], this->trajectory[t].action);
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[1], this->trajectory[t].reward);
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[2], this->trajectory[t].stateVisitsTotal);
		gmp->Print("  ");
		if (this->trajectory[t].goal == REWARD_GOALS::REWARD_MAXIMIZE)
			gmp->Print("   MAX");
		else if (this->trajectory[t].goal == REWARD_GOALS::REWARD_MINIMIZE)
			gmp->Print("   MIN");
		else
			gmp->Print(" UNKNW");
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[4], this->trajectory[t].bestActionValue);
		gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[5], this->trajectory[t].exploratoryAction);
		if (this->trajectory[t].state == NULL){
			gmp->Print("  ");
			gmp->Print("    NULL");
		}
		else{
			gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[6], this->trajectory[t].state);
			gmp->Print("  "); gmp->Print(HashTree::TreeNodeAtrFormat[7], this->trajectory[t].state->hashKey);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[16], this->trajectory[t].state->data->num_visited_episodes);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[8], this->trajectory[t].state->data->created_episode);
			if (this->trajectory[t].state->data->created_episode == this->numEpisodes_total - 1)
				gmp->Print("  <- NEW");
		}
		gmp->Print("\n%s", printLinePrefix);
	}

	gmp->Print("\n%s", printLinePrefix); gmp->Print("END   Output_Trajectory()");
	gmp->Print("\n");
}

void Player_AI_RL::Output_TDbackup1(int trajectory_index, double TDerror, double nextStateVal, double stateVal, int exploratory_move_trace_reset, char* printLinePrefix)
{
	if ((this->config_output_depth >= 2) && (this->config_output_TDbackup >= 1)){

		if (printLinePrefix == NULL)
			printLinePrefix = "TDLB    ";

		gmp->Print("\n%s", printLinePrefix); gmp->Print("trajInd=%d", trajectory_index);
		if (trajectory_index < this->trajectory_length)
			gmp->Print("  nextAction=% d", this->trajectory[trajectory_index+1].action);
		else
			gmp->Print("  nextAction=% d", -1);	//terminal state
		gmp->Print("  traceCut=%d", this->exploratory_move_trace_cutOff);
		gmp->Print("  TDerror=% .5f", TDerror);
		gmp->Print("  reward=% .5f", this->trajectory[trajectory_index].reward);
		gmp->Print("  nextVal=% .5f", nextStateVal);
		gmp->Print("  currVal=% .5f", stateVal);
		gmp->Print("  explRes=%d", (int)exploratory_move_trace_reset);

	}
}
void Player_AI_RL::Output_TDbackup21(int b, int trajectory_index, double trace, HashTree::TreeNode* backupNode, char* printLinePrefix)
{
	if ((this->config_output_depth >= 2) && (this->config_output_TDbackup >= 2)){

		if (printLinePrefix == NULL)
			printLinePrefix = "TDLB    ";

		//headers
		if (b == trajectory_index){
			gmp->Print("\n%s", printLinePrefix);
			gmp->Print("\n%sBCKP    ", printLinePrefix);
			gmp->Print("  "); gmp->Print("   depth");
			gmp->Print("  "); gmp->Print("  Ztrace");
			gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordLabels[6]);
			gmp->Print("  "); gmp->Print(" updated");
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrLabels[4]);
			gmp->Print("  "); gmp->Print(" oldQval");
			gmp->Print("  "); gmp->Print(" newQval");
			gmp->Print("  "); gmp->Print(" newOffQ");	//new Q-value with added offline deltaQ update (what the value will be after the offline non-inplace update has finished)
			gmp->Print("  "); gmp->Print("parAlpha");
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrLabels[16]);
			gmp->Print("  "); gmp->Print(HashTree::TreeNodeAtrLabels[7]);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrLabels[1]);
		}

		//records
		gmp->Print("\n%sBCKP    ", printLinePrefix);
		gmp->Print("  "); gmp->Print("%8d", b);
		gmp->Print("  "); gmp->Print("% 8.5f", trace);
		if (backupNode != NULL){
			gmp->Print("  "); gmp->Print(trajectoryRecord::trajectoryRecordFormat[6], backupNode);
			gmp->Print("  ");
			if ((this->config_trace_type == Q_TRACE_ACCUMULATING) || (backupNode->data->Z_traceTag < trajectory_index))
				gmp->Print("     yes");
			else
				gmp->Print("      no");
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[4], backupNode->data->Z_traceTag);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[3], backupNode->data->Q_value);
		}
		else{
			gmp->Print("  "); gmp->Print("    NULL");
		}

	}
}
void Player_AI_RL::Output_TDbackup22(int b, HashTree::TreeNode* backupNode, double alpha, char* printLinePrefix)
{
	if ((this->config_output_depth >= 2) && (this->config_output_TDbackup >= 2)){

		if (printLinePrefix == NULL)
			printLinePrefix = "TDLB    ";

		if (backupNode != NULL){
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[3], backupNode->data->Q_value);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[3], backupNode->data->Q_value + backupNode->data->offline_delta_Q);
			gmp->Print("  "); gmp->Print("% 8.5f", alpha);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[16], backupNode->data->num_visited_episodes);
			gmp->Print("  "); gmp->Print(HashTree::TreeNodeAtrFormat[7], backupNode->hashKey);
			gmp->Print("  "); gmp->Print(HashTree::StateActionAtrFormat[1], backupNode->data->actionID);
		}
		if (b == this->exploratory_move_trace_cutOff)
			gmp->Print("\n%s", printLinePrefix);

	}
}

void Player_AI_RL::Output_Settings()
{
	gmp->Print("\n");
	gmp->Print("Player_AI_RL()::Output_Settings()\n");
	gmp->Print(settingsLabels[1]); gmp->Print("    "); gmp->Print(settingsFormat[1], this->config_preset_algorithm); gmp->Print("\n");
	gmp->Print(settingsLabels[2]); gmp->Print("    "); gmp->Print(settingsFormat[2], this->config_control_policy); gmp->Print("\n");
	gmp->Print(settingsLabels[3]); gmp->Print("    "); gmp->Print(settingsFormat[3], this->config_policy_evaluation); gmp->Print("\n");
	gmp->Print(settingsLabels[4]); gmp->Print("    "); gmp->Print(settingsFormat[4], this->config_TDupdateType); gmp->Print("\n");
	gmp->Print(settingsLabels[5]); gmp->Print("    "); gmp->Print(settingsFormat[5], this->config_trace_type); gmp->Print("\n");
	gmp->Print(settingsLabels[6]); gmp->Print("    "); gmp->Print(settingsFormat[6], this->config_trace_exploratory_reset); gmp->Print("\n");
	gmp->Print(settingsLabels[7]); gmp->Print("    "); gmp->Print(settingsFormat[7], this->config_transpositions); gmp->Print("\n");
	gmp->Print(settingsLabels[8]); gmp->Print("    "); gmp->Print(settingsFormat[8], this->config_offpolicy_backup_recheck_best); gmp->Print("\n");
	gmp->Print(settingsLabels[9]); gmp->Print("    "); gmp->Print(settingsFormat[9], this->config_nonEpisodicTasks_updateInterval); gmp->Print("\n");
	gmp->Print(settingsLabels[10]); gmp->Print("    "); gmp->Print(settingsFormat[10], this->config_num_new_nodes_per_episode); gmp->Print("\n");
	gmp->Print(settingsLabels[11]); gmp->Print("    "); gmp->Print(settingsFormat[11], this->config_rollout_assumption); gmp->Print("\n");
	gmp->Print(settingsLabels[12]); gmp->Print("    "); gmp->Print(settingsFormat[12], this->config_alpha_type); gmp->Print("\n");
	gmp->Print(settingsLabels[13]); gmp->Print("    "); gmp->Print(settingsFormat[13], this->config_ucb_visit_type); gmp->Print("\n");
	gmp->Print(settingsLabels[14]); gmp->Print("    "); gmp->Print(settingsFormat[14], this->config_ucb_norm_type); gmp->Print("\n");
	gmp->Print(settingsLabels[15]); gmp->Print("    "); gmp->Print(settingsFormat[15], this->config_ucb_norm_global); gmp->Print("\n");
	gmp->Print(settingsLabels[16]); gmp->Print("    "); gmp->Print(settingsFormat[16], this->config_ucb_norm_local); gmp->Print("\n");
	gmp->Print(settingsLabels[17]); gmp->Print("    "); gmp->Print(settingsFormat[17], this->config_opponent_alignment); gmp->Print("\n");
	gmp->Print(settingsLabels[18]); gmp->Print("    "); gmp->Print(settingsFormat[18], this->config_opponent_policy); gmp->Print("\n");
	gmp->Print(settingsLabels[19]); gmp->Print("    "); gmp->Print(settingsFormat[19], this->par_egreedy_e); gmp->Print("\n");
	gmp->Print(settingsLabels[20]); gmp->Print("    "); gmp->Print(settingsFormat[20], this->par_ucb_c); gmp->Print("\n");
	gmp->Print(settingsLabels[21]); gmp->Print("    "); gmp->Print(settingsFormat[21], this->par_task_gamma); gmp->Print("\n");
	gmp->Print(settingsLabels[22]); gmp->Print("    "); gmp->Print(settingsFormat[22], this->par_td_alpha); gmp->Print("\n");
	gmp->Print(settingsLabels[23]); gmp->Print("    "); gmp->Print(settingsFormat[23], this->par_td_lambda); gmp->Print("\n");
	gmp->Print(settingsLabels[24]); gmp->Print("    "); gmp->Print(settingsFormat[24], this->par_td_initVal); gmp->Print("\n");
	gmp->Print(settingsLabels[25]); gmp->Print("    "); gmp->Print(settingsFormat[25], this->par_num_episodes); gmp->Print("\n");
	gmp->Print(settingsLabels[26]); gmp->Print("    "); gmp->Print(settingsFormat[26], this->par_num_simulatedActions_perMove); gmp->Print("\n");
	gmp->Print(settingsLabels[27]); gmp->Print("    "); gmp->Print(settingsFormat[27], this->par_simulated_horizon_lenght); gmp->Print("\n");
	gmp->Print(settingsLabels[28]); gmp->Print("    "); gmp->Print(settingsFormat[28], this->config_memory_limitMB); gmp->Print("\n");
	gmp->Print("\n");
}

//static structures
const char * const Player_AI_RL::settingsLabels[] = {
	"INVALID",
	"config_preset_algorithm",
	"config_control_policy",
	"config_policy_evaluation",
	"config_TDupdateType",
	"config_trace_type",
	"config_trace_exploratory_reset",
	"config_transpositions",
	"config_offpolicy_backup_recheck_best",
	"config_nonEpisodicTasks_updateInterval",
	"config_num_new_nodes_per_episode",
	"config_rollout_assumption",
	"config_alpha_type",
	"config_ucb_visit_type",
	"config_ucb_norm_type",
	"config_ucb_norm_global",
	"config_ucb_norm_local",
	"config_opponent_alignment",
	"config_opponent_policy",
	"par_egreedy_e",
	"par_ucb_c",
	"par_task_gamma",
	"par_td_alpha",
	"par_td_lambda",
	"par_td_initVal",
	"par_num_episodes",
	"par_num_simulatedActions_perMove",
	"par_simulated_horizon_lenght",
	"config_memory_limitMB",
};
const char * const Player_AI_RL::settingsFormat[] = {
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%d",
	"%f",
	"%f",
	"%f",
	"%f",
	"%f",
	"%f",
	"%d",
	"%d",
	"%d",
	"%f",
};
const char * const Player_AI_RL::trajectoryRecord::trajectoryRecordLabels[] = {
	"action",	//0
	"reward",	//1
	"visTot",	//2 number of total visits to current state so far
	"  goal",	//3
	"bstAcV",	//4 value of best action
	"isExpl",	//5 was move exploratory
	"statePtr",	//6 pointer to memorized structure
};
const char * const Player_AI_RL::trajectoryRecord::trajectoryRecordFormat[] = {
	"% 6d",
	"% 6.2f",
	"%6.1f",
	"%6d",
	"% 6.2f",
	"%6d",
	"%8p",
};




////used for debug
//if (this->numEpisodes_lastMove > 68)
//if (internalGame->current_plys > 918)
//if (simulatedGame->current_plys > 1017)
//printf("debugStop\n");
//
///**
//Select next child from given tree node and with given UCT exploration weight C.
//*/
//Player_AI_RL::UCTnode* Player_AI_RL::UCT_Tree_Policy_Best_Child(UCTnode* parent, double exploration_weight){
//
//	double bestValue;
//	int multiple_best, randAction;
//	int selectedChild_id;
//
//	bestValue = -DBL_MAX;
//	selectedChild_id = -1;
//
//	//OPPONENT RANDOM MOVES
//	if (((simulatedGame->current_plys - internalGame->current_plys) % 2 == 1) && ((rand() / (float)(RAND_MAX + 1)) < RANDOM_TREE_OPPONENT_THRESHOLD)){
//
//		multiple_best = parent->number_allowed_actions;
//
//	}
//	else{
//
//		//find best-valued children node
//		multiple_best = 1;
//		for (int i = 0; i < parent->number_allowed_actions; i++){
//
//			UCTnode* child = parent->children[i];
//
//			//check if children was already allocated (for safety)
//			if (child != NULL){
//
//				// ------------------------------------PARAMETER SETTING ---------------------------------- //
//
//				// ---- default parameters ---- //
//				double set_param_C = par_ucb_c;
//
//				// ---- tom-added parameters ---- //
//				double set_QVALUE_param_scoreWeight = 1.0;
//				double set_MC_weight = 1.0 - set_QVALUE_param_scoreWeight;
//
//				// ------------ NON-CONSTANT PARAMETER VALUES ------------ //
//				double netInputs[FUNC_APPROX_NUM_INPUTS];
//				double sumNetOut[FUNC_APPROX_NUM_OUTPUTS];
//				double functionNetOut[FUNC_APPROX_HIDD_LAYER];
//				double sumNetHid[FUNC_APPROX_HIDD_LAYER];
//				double functionHidOut[FUNC_APPROX_HIDD_LAYER];
//
//#if(PARAM_FUNC_APP_TYPE == 1)
//				// ---- direct param search ---- //
//				//use this in combination with LRP_improved_v1() and LRP_test_wrapper()
//
//				//INPUTS are equal to weights (direct search)
//				for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++)
//					netInputs[inp] = Func_App_UCT_Params->parameter_weights[inp];
//
//#if(FUNC_APPROX_NUM_INPUTS > 0)
//				set_param_C = netInputs[0] + UCT_param_C;
//				set_QVALUE_param_scoreWeight = netInputs[1] + QVALUE_param_scoreWeight;
//				set_MC_weight = 1.0 - set_QVALUE_param_scoreWeight;		//was erroneously missing prior 17.3.2014
//#endif
//
//#elif(PARAM_FUNC_APP_TYPE == 2)
//				// ---- single NN: weighted output ---- //
//				//use this in combination with LRP_improved_v1() and LRP_test_wrapper()
//
//				//WARNING: THE NUMBER OF Func_App_UCT_Params must be set in Player_AI_RL.hpp with the constant FUNC_APPROX_NUM_PARAMS
//	
//				//define INPUTS here
//				//if(FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = child->visits;
//				//if(FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = 1.0/child->visits;
//				//if(FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = (1.0 / (child->sum_plys_sim_phase + 1.0)) * 2.0;		//test 8.1
//				//if(FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = ((double)this->numEpisodes_lastMove / UCT_param_IterNum);	//test 1.1
//
//				//single layer neural network
//				for (int out = 0; out < FUNC_APPROX_NUM_OUTPUTS; out++){
//					sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
//					for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++)
//						sumNetOut[out] += Func_App_UCT_Params->parameter_weights[(inp + 1) + out * (FUNC_APPROX_NUM_INPUTS + 1)] * netInputs[inp];
//					functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
//				}
//
//				//map net outputs to desired parameters, scale and bias parameters
//
//				set_param_C = functionNetOut[0] * 10.0 + UCT_param_C;
//				set_QVALUE_param_scoreWeight = functionNetOut[2] * 10.0 + QVALUE_param_scoreWeight;
//				set_MC_weight = 1.0 - set_QVALUE_param_scoreWeight;		//was erroneously missing prior 17.3.2014
//
//				//bound parameters to zero or above
//				//if(set_param_C < 0) set_param_C = 0.0;	//this was commented out on 2014_02_20, previous to this date all experiments with single NN used this bound
//
//				// END ---- single NN: weighted output ---- //
//
//#elif(PARAM_FUNC_APP_TYPE == 3)
//				// ---- feed forward perceptron (dual layer NN) ---- //		
//				//use this in combination with LRP_improved_v1() and LRP_test_wrapper()
//
//				//define INPUTS here
//				//if(FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = 1.0/child->visits;
//				//if(FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = ((double)this->numEpisodes_lastMove / UCT_param_IterNum);
//				//if(FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = (child->visits_in_last_UCT / UCT_param_IterNum);		//this was bugged until 2014_01 Q-Values test, so that visits_in_last_UCT was equal to visits (this way this whole input rapresented the average number of visits per iteration -> the probability of visiting the node in a single iteration)
//				//if(FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (1 / (child->sum_plys_sim_phase + 1)) * 2.0;
//
//				//hidden layer
//				for (int hid = 0; hid < FUNC_APPROX_HIDD_LAYER; hid++){
//					sumNetHid[hid] = Func_App_UCT_Params->parameter_weights[0 + hid * (FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
//					for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++){
//						sumNetHid[hid] += netInputs[inp] * Func_App_UCT_Params->parameter_weights[(inp + 1) + hid * (FUNC_APPROX_NUM_INPUTS + 1)];	//net inputs
//					}
//					functionHidOut[hid] = Neural_Network_Threshold_Function(sumNetHid[hid]);
//				}
//
//				//output layer
//				for (int out = 0; out < FUNC_APPROX_NUM_OUTPUTS; out++){
//					sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (FUNC_APPROX_HIDD_LAYER + 1) + FUNC_APPROX_HIDD_LAYER*(FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
//					for (int hid = 0; hid < FUNC_APPROX_HIDD_LAYER; hid++){
//						sumNetOut[out] += (functionHidOut[hid] * Func_App_UCT_Params->parameter_weights[(hid + 1) + out * (FUNC_APPROX_HIDD_LAYER + 1) + FUNC_APPROX_HIDD_LAYER*(FUNC_APPROX_NUM_INPUTS + 1)]);	//hidden layer outputs
//					}
//					functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
//				}
//
//				//map net outputs to desired parameters, scale and bias parameters
//				//set_param_C =					functionNetOut[0] * 10.0 + UCT_param_C;
//				//set_QVALUE_param_scoreWeight =	functionNetOut[2] * 10.0 + QVALUE_param_scoreWeight;
//				//set_MC_weight =					1.0 - set_QVALUE_param_scoreWeight;		//was erroneously missing prior 17.3.2014
//
//				//bound parameters to zero or above
//				//if(set_param_C < 0) set_param_C = 0.0;
//
//				// END ---- feed forward perceptron (dual layer NN) ---- //
//				// END ------------ NON-CONSTANT PARAMETER VALUES ------------ //
//#endif
//				// ------------------------------------END - PARAMETER SETTING ---------------------------------- //
//
//				// ------------------------------------VALUE EQUATION COMPONENTS ---------------------------------- //
//
//				// ---- default equations ---- //
//				double MC_value = (child->rewards / child->visits);
//				double UCB_value = sqrt(2 * log(parent->visits) / child->visits);
//
//				// ---- consider whether is this an exploratory move or an output best move ---- //
//				set_param_C *= exploration_weight;	//neccessary for select best child (when C must be 0.0)
//				//set_QVALUE_param_scoreWeight *= exploration_weight;	//not used yet
//
//				// ---- Q-value RL values instead of normal average ---- //
//
//				MC_value = set_QVALUE_param_scoreWeight*(child->Q_value + 0.5) + set_MC_weight*(MC_value);	//TDfourth: translated back to interval [0,1]
//
//
//				// ------------------------------------END - VALUE EQUATION COMPONENTS ---------------------------------- //
//
//				// ------------------------------------VALUE CALCULATION ---------------------------------- //
//
//				// ---- plain UCB equation ---- //
//				child->value = MC_value + 2.0 * set_param_C * UCB_value;
//
//				// ------------------------------------END - VALUE CALCULATION ---------------------------------- //
//
//				// ---- DEBUG PRINT ----//
//
//				//printf("%3.3f\t%3.3f\n", (double)this->numEpisodes_lastMove / UCT_param_IterNum, (child->sum_plys_sim_phase / child->visits / simulatedGame->maximum_plys));
//				//if(child->number_allowed_actions != 7)
//				//printf("%3.3f\t%d\t%d\n",child->visits_in_last_UCT / UCT_param_IterNum, child->number_allowed_actions,  game->maximum_allowed_moves);
//				//printf("%3.3f\t%3.3f\n", (double)game->current_plys / game->maximum_plys, (double)simulatedGame->current_plys / simulatedGame->maximum_plys);
//				////TEST 7
//				//printf("%6.3f \t %10.0f \t %6.3f \t %6.3f \t %3d \t %10.0f \t %6.3f\n",
//				//	(child->sum_plys_sim_phase / child->visits / (parent->sum_plys_to_end + simulatedGame->current_plys)),
//				//	child->sum_plys_sim_phase,
//				//	child->visits,
//				//	parent->sum_plys_to_end,
//				//	simulatedGame->current_plys,
//				//	parent->visits,
//				//	(child->sum_plys_sim_phase / child->visits / ((parent->sum_plys_to_end)/parent->visits + simulatedGame->current_plys))
//				//	);
//
//				//printf("DEBUG CHILD VAL: %d %3.1f\n", i, child->value);
//
//				// ---- END - DEBUG PRINT ----//
//
//				//remember best children and count number of equal best children
//				if (child->value == bestValue){
//#if((!DEBUG_DISABLE_RANDOM)&&(!DEBUG_DISABLE_RANDOM_MULTIPLE_BEST))
//					multiple_best++;
//#endif
//				}
//				else if (child->value > bestValue){
//					selectedChild_id = i;
//					bestValue = child->value;
//					multiple_best = 1;
//				}
//
//				//OUTPUT ALL VALUES - level 5
//#if(TOM_GLOBAL_ENABLE_MCTS_OUTPUT_LEVEL)
//				gmp->PrintI(5, output_log_level5_format,
//
//					game->experiment_repeat_index,
//					game->batch_repeat_index,
//					game->game_repeat_index,
//					game->current_plys,
//					this->numEpisodes_lastMove,
//					simulatedGame->current_plys,
//					i,
//
//					child->action_index,
//					child->number_allowed_actions,
//					child->number_explored_children,
//
//					child->visits,
//					child->rewards,
//
//					child->value,
//					MC_value,
//					UCB_value,
//					child->Q_value,
//
//					set_param_C,
//
//					child->sum_simulations,
//					child->sum_plys_sim_phase,
//					child->sum_plys_to_end,
//					child->last_update_iteration,
//					child->visits_in_last_UCT,
//
//					child->last_selected_child_id,
//					child->best_value_child_id,
//					child->num_best_childs,
//					child->num_changes_best_child
//
//					);
//#if(PARAM_FUNC_APP_TYPE > 1)
//				for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++){
//					gmp->PrintI(5, "%7.3f \t", netInputs[inp]);
//				}
//#endif
//				gmp->PrintI(5, "\n");
//#endif
//
//			} // END - check if children was already allocated (for safety)
//
//		}
//
//	}
//
//	//if multiple best actions/children, break ties uniformly random
//	if (multiple_best > 1){
//		randAction = (int)floorf((rand() / (float)(RAND_MAX + 1)) * multiple_best);
//		for (int i = 0; i < parent->number_allowed_actions; i++){
//			if (parent->children[i] != NULL){
//				if (parent->children[i]->value >= bestValue){
//					if (randAction <= 0){
//						selectedChild_id = i;
//						i = parent->number_allowed_actions;	//break loop
//					}
//					else{
//						randAction--;
//					}
//				}
//			}
//		}
//	}
//
//	//memorize values/calculations
//	if (selectedChild_id != parent->best_value_child_id){
//		parent->best_value_child_id = selectedChild_id;
//		parent->num_changes_best_child++;
//	}
//	parent->num_best_childs = multiple_best;
//	parent->last_selected_child_id = selectedChild_id;
//
//	//debug check
//	//dbgTmpInt2 = selectedChild_id;
//	if ((selectedChild_id < 0) || (selectedChild_id >= internalGame->maximum_allowed_moves)){
//		//gmp->Print("WARNING: PLAYER AI UCT_TOMTEST: UCT_Tree_Policy_Best_Child: selectedChild_id %d (parent_moves %d game_max_moves %d) (multiple %d)\n",selectedChild_id,parent->number_allowed_actions,internalGame->maximum_allowed_moves,multiple_best);
//		//gmp->Print("---\n");
//		//gmp->Print("plyE %3d  mctsI %3d  plyI %3d   bestValue %3.3f\n", game->current_plys,this->numEpisodes_lastMove,simulatedGame->current_plys,bestValue);
//		//for(int i = 0; i < parent->number_allowed_actions; i++){
//		//	gmp->Print("c%2d  %3.3f\n",i,parent->children[i]->value);
//		//}
//		//gmp->Print("---\n");
//		//gmp->Flush();
//
//		//select random move
//		selectedChild_id = (int)floorf((rand() / (float)(RAND_MAX + 1)) * (float)parent->number_allowed_actions);
//	}
//	//-- end - debug check
//
//	//return selected untried action
//	return (parent->children[selectedChild_id]);
//}
//
//
///**
//Run simulations from the UCT-tree leaf by using the Default Policy
//
//Updates MCTS_num_all_simulations counter, however not online but in BATCH at the end of all requested simulations
//*/
//void Player_AI_RL::UCT_Simulate(int num_simulations, const bool calc_variance){
//
//	int plys_at_tree_leaf;
//
//	//-- store values before playout phase begins --//
//	plys_at_tree_leaf = simulatedGame->current_plys;	//remember number of moves at beginning of playout
//	if (num_simulations > 1){
//		simulatedGame_startingState->Copy_Game_State_From(simulatedGame, false);		//save game state at beginning of playout phase
//	}
//
//	//-- compute first simulation and calculate score --//
//	UCT_Default_Policy();		//score is stored in simulatedGame->score
//
//	//-- save feedback/results from first simulation --//
//
//	//feedback: scores for each player
//	for (int i = 0; i < simulatedGame->number_players; i++){
//
//		sim_feedback_scores_avg[i] = simulatedGame->score[i];
//		if (calc_variance)
//			sim_feedback_scores[0][i] = sim_feedback_scores_avg[i];
//	}
//
//	//feedback: duration (number of plys) of the playout phase
//	sim_feedback_plys_avg = (simulatedGame->current_plys) - plys_at_tree_leaf;
//	if (calc_variance)
//		sim_feedback_plys[0] = sim_feedback_plys_avg;
//
//	//-- compute the rest of the simulations --//
//	if (num_simulations == 1){
//
//		for (MCTS_current_simuNum = 1; MCTS_current_simuNum < num_simulations; MCTS_current_simuNum++){
//
//			//reset simulated game state to match state at beginning of playout phase
//			simulatedGame->Copy_Game_State_From(simulatedGame_startingState, false);
//
//			//compute simulation
//			UCT_Default_Policy();
//
//			//save feedback/results
//			for (int i = 0; i < simulatedGame->number_players; i++){
//				sim_feedback_scores_avg[i] += simulatedGame->score[i];
//				if (calc_variance)
//					sim_feedback_scores[MCTS_current_simuNum][i] = simulatedGame->score[i];
//			}
//			sim_feedback_plys_avg += ((simulatedGame->current_plys) - plys_at_tree_leaf);
//			sim_feedback_plys[MCTS_current_simuNum] = (simulatedGame->current_plys) - (simulatedGame_startingState->current_plys);
//
//		}
//
//		//average results
//		for (int i = 0; i < simulatedGame->number_players; i++){
//			sim_feedback_scores_avg[i] /= num_simulations;
//		}
//		sim_feedback_plys_avg /= num_simulations;
//
//	}
//
//	//store number of computed simulations
//	sim_feedback_num_sims = num_simulations;
//
//	//BATCH update global simulation counter
//	MCTS_num_all_simulations += num_simulations;
//}
//
///**
//Play default policy from current game position until game end
//*/
//void Player_AI_RL::UCT_Default_Policy(){
//
//	int gameStatus, lastMove;
//	int num_simulated_plys;
//
//	//simulate game until game-end
//	num_simulated_plys = 0;
//	gameStatus = simulatedGame->game_ended;
//	while (gameStatus == 0){
//
//		//DEBUG
//		//if(simulatedGame->number_of_plays == 38) 
//		//	printf("DEBUG: plys == %d", simulatedGame->number_of_plays);	
//
//		//random policy
//#if(!DEBUG_DISABLE_RANDOM)
//		lastMove = simulatedGame->Select_Move_Random();
//#else
//		lastMove = simulatedGame->Select_Move(0);
//		//lastMove = simulatedGame->Select_Move(simulatedGame->current_number_moves[simulatedGame->current_player] - 1);
//		//lastMove = simulatedGame->Select_Move_Random();
//#endif
//
//		//play move in internal simulated game
//#if(TOM_DEBUG)
//		gameStatus = simulatedGame->Play_Move(lastMove);
//#else
//		gameStatus = simulatedGame->Play_Move_Unsafe(lastMove);
//#endif
//
//		//DEBUG
//#if((VISUALIZE_LEVEL_UCT)&&VISUALIZE_UCT_ACTIONS_TREE)
//		//sprintf(visualizeActionsTree, "  > %2d", currentNode->action_index);
//		visualizeActionsPlayout << "  > " << lastMove;
//		//printf("  > %2d", currentNode->action_index);
//#endif
//#if(DEBUG_SIMULATED_GAMES_OUT)
//		printf("-playout-\n");
//		simulatedGame->Output_Board_State();
//		//simulatedGame->output_state_to_STD();
//		//simulatedGame->output_chains_to_STD();
//		//printf("Moves: %d %d\n",simulatedGame->num_moves[0], simulatedGame->num_moves[1]);
//#endif
//
//	}
//
//	//calculate score at game end
//	simulatedGame->Calculate_Score();
//}
//
///**
//Single- or two-player backup reward through the tree
//*/
//void Player_AI_RL::UCT_Backup(UCTnode* leaf){
//
//	UCTnode* currentNode = leaf;
//	int belonging_player;
//	double tree_up_path_length;
//
//	//improve this below when needed, NOW TEMPORARY SOLUTION FOR SINGLEPLAYER and TWOPLAYER games
//	if (game->number_players > 1)
//		//select correct players' reward: bitwise replacement for upper if-sentences (instead of modulo 2)
//		belonging_player = (UCTtree_treePolicy_lastDepth & 1) == (internalGame->current_plys & 1);
//	else
//		belonging_player = 0;
//
//	// -- Q-values reinforcement learning algorithm -- //
//
//	double set_QVALUE_param_alpha = par_td_alpha;
//	double set_QVALUE_param_gamma = par_task_gamma;
//	double set_QVALUE_param_lambda = par_td_lambda;
//
//	double netInputs[FUNC_APPROX_NUM_INPUTS];
//	double sumNetOut[FUNC_APPROX_NUM_OUTPUTS];
//	double functionNetOut[FUNC_APPROX_HIDD_LAYER];
//	double sumNetHid[FUNC_APPROX_HIDD_LAYER];
//	double functionHidOut[FUNC_APPROX_HIDD_LAYER];
//
//#if(PARAM_FUNC_APP_TYPE == 1)
//	// -- Q-value parameter search and approximation -- //
//
//	//INPUTS arr equal to weights (direct search)
//	for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++)
//		netInputs[inp] = Func_App_UCT_Params->parameter_weights[inp];
//
//	set_QVALUE_param_alpha = Func_App_UCT_Params->parameter_weights[2] + QVALUE_param_alpha;
//	set_QVALUE_param_gamma = Func_App_UCT_Params->parameter_weights[3] + QVALUE_param_gamma;
//	set_QVALUE_param_lambda = Func_App_UCT_Params->parameter_weights[4] + QVALUE_param_lambda;
//
//#elif(PARAM_FUNC_APP_TYPE == 2)
//	// ---- single NN: weighted output ---- //
//
//	//define INPUTS here
//	if (FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = sim_feedback_scores_avg[belonging_player];
//	if (FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = sim_feedback_plys_avg / simulatedGame->maximum_plys;
//	//if(FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (currentNode->parent->sum_plys_sim_phase + sim_feedback_plys_avg) / (currentNode->parent->sum_simulations + 1) ;	//these two indicators were not yet updated for parent node (will be in next iteration of backup loop below, so here we need to correct their value in advance)
//	if (FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (currentNode->parent->sum_plys_sim_phase + sim_feedback_plys_avg) / (currentNode->parent->sum_simulations + 1) / simulatedGame->maximum_plys;	//these two indicators were not yet updated for parent node (will be in next iteration of backup loop below, so here we need to correct their value in advance)
//
//	//single layer neural network
//	for (int out = 0; out < FUNC_APPROX_NUM_OUTPUTS; out++){
//		sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
//		for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++)
//			sumNetOut[out] += Func_App_UCT_Params->parameter_weights[(inp + 1) + out * (FUNC_APPROX_NUM_INPUTS + 1)] * netInputs[inp];
//		functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
//	}
//
//#elif(PARAM_FUNC_APP_TYPE == 3)
//	// ---- feed forward perceptron (dual layer NN) ---- //		
//
//	//define INPUTS here
//	if (FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = sim_feedback_scores_avg[belonging_player];
//	if (FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = sim_feedback_plys_avg / simulatedGame->maximum_plys;
//	if (FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (currentNode->parent->sum_plys_sim_phase + sim_feedback_plys_avg) / (currentNode->parent->sum_simulations + 1) / simulatedGame->maximum_plys;	//these two indicators were not yet updated for parent node (will be in next iteration of backup loop below, so here we need to correct their value in advance)
//
//
//	//hidden layer
//	for (int hid = 0; hid < FUNC_APPROX_HIDD_LAYER; hid++){
//		sumNetHid[hid] = Func_App_UCT_Params->parameter_weights[0 + hid * (FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
//		for (int inp = 0; inp < FUNC_APPROX_NUM_INPUTS; inp++){
//			sumNetHid[hid] += netInputs[inp] * Func_App_UCT_Params->parameter_weights[(inp + 1) + hid * (FUNC_APPROX_NUM_INPUTS + 1)];	//net inputs
//		}
//		functionHidOut[hid] = Neural_Network_Threshold_Function(sumNetHid[hid]);
//	}
//
//	//output layer
//	for (int out = 0; out < FUNC_APPROX_NUM_OUTPUTS; out++){
//		sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (FUNC_APPROX_HIDD_LAYER + 1) + FUNC_APPROX_HIDD_LAYER*(FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
//		for (int hid = 0; hid < FUNC_APPROX_HIDD_LAYER; hid++){
//			sumNetOut[out] += (functionHidOut[hid] * Func_App_UCT_Params->parameter_weights[(hid + 1) + out * (FUNC_APPROX_HIDD_LAYER + 1) + FUNC_APPROX_HIDD_LAYER*(FUNC_APPROX_NUM_INPUTS + 1)]);	//hidden layer outputs
//		}
//		functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
//	}
//
//	// END ---- feed forward perceptron (dual layer NN) ---- //
//
//#endif
//	// -- end - Q-value parameter search and approximation -- //
//
//	double TDerror[2];
//
//	// -- eligibility trace -- //
//
//	double Q_trace = 1.0;
//	for (int i = 0; i < sim_feedback_plys_avg; i++){
//		Q_trace *= set_QVALUE_param_gamma;
//	}
//
//
//	// -- value of the next node after the leaf node -- //
//
//	//double TD_next_state_value = Q_trace*(sim_feedback_scores_avg[belonging_player] - 0.5);	//assume that all simulation nodes have value equal to reward
//	//if (VARIANT == VARIANTS_MERGED_BOOTSTRAPPING)
//	//	TD_next_state_value = 0.0;
//
//	//// -- first TD error -- //
//
//	//double TD_leaf_state_value = currentNode->Q_value;	//the actual value of the leaf node
//	//if (VARIANT == VARIANTS_WEIGHTED_REWARDS)
//	//	TD_leaf_state_value = 0.0;						//assume neutral value of leaf node
//	////TD_leaf_state_value = QVALUE_param_initVal;		//assume initial value of leaf node (default = 0.0)
//
//	//TDerror[belonging_player] = ((TD_next_state_value - TD_leaf_state_value));
//	//TDerror[1 - belonging_player] = (-(TD_next_state_value - TD_leaf_state_value));
//
//	//if (VARIANT == VARIANTS_FULL_TD){
//	//	TDerror[belonging_player] = 0.0;
//	//	TDerror[1 - belonging_player] = 0.0;
//	//	TD_next_state_value /= set_QVALUE_param_gamma;
//	//}
//
//
//	// -- end - Q-values reinforcement learning algorithm -- //
//
//	//propagate reward up through the tree
//	tree_up_path_length = 0;
//	for (int i = 0; i < UCTtree_treePolicy_lastDepth + 1; i++){
//
//		// -- update current node -- //
//		//basic UCT values
//		currentNode->visits += 1.0;
//		currentNode->rewards += sim_feedback_scores_avg[belonging_player];
//
//		// -- new indicators -- //
//
//		currentNode->sum_simulations += sim_feedback_num_sims;
//		currentNode->sum_plys_sim_phase += sim_feedback_plys_avg;
//		currentNode->sum_plys_to_end += (sim_feedback_plys_avg + tree_up_path_length);
//
//		//count node visits since last UCT() call (since last external game ply and UCT tree change)
//		if (currentNode->last_update_iteration < this->num_all_episodes - this->numEpisodes_lastMove){
//			currentNode->visits_in_last_UCT = 1.0;
//			currentNode->last_update_iteration = this->num_all_episodes;
//		}
//		else{
//			currentNode->visits_in_last_UCT += 1.0;
//		}
//
//		// -- Q-values temporal difference update  -- //
//
//
//		
//		//set_QVALUE_param_alpha = 1.0 / currentNode->visits;
//		//double alpha = (1.0 + set_QVALUE_param_alpha) * 1.0 / currentNode->visits;
//		
//		//if (VARIANT == VARIANTS_SINGLE_BACKUP){
//		//	currentNode->Q_value = currentNode->Q_value + set_QVALUE_param_alpha * TDerror[belonging_player];
//		//	TDerror[belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
//		//	TDerror[1 - belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
//		//}
//		//else if (VARIANT == VARIANTS_WEIGHTED_REWARDS){
//		//	currentNode->Q_value = currentNode->Q_value + TDerror[belonging_player];
//		//	TDerror[belonging_player] *= (set_QVALUE_param_gamma);
//		//	TDerror[1 - belonging_player] *= (set_QVALUE_param_gamma);
//		//}
//		//else if (VARIANT == VARIANTS_MERGED_BOOTSTRAPPING)
//		//{
//		//	TDerror[belonging_player] = ((set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
//		//	TDerror[1 - belonging_player] = -(-(set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
//		//	TD_next_state_value = (- currentNode->Q_value);
//		//	currentNode->Q_value = currentNode->Q_value + set_QVALUE_param_alpha * Q_trace * (sim_feedback_scores_avg[belonging_player] - 0.5 + TDerror[belonging_player]);
//		//	Q_trace *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
//		//}
//		//else if (VARIANT == VARIANTS_FULL_TD){
//		//	TDerror[belonging_player] += ((set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
//		//	TDerror[1 - belonging_player] += (-(set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
//		//	TD_next_state_value = (-currentNode->Q_value);
//		//	currentNode->Q_value = currentNode->Q_value + set_QVALUE_param_alpha * TDerror[belonging_player];
//		//	TDerror[belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
//		//	TDerror[1 - belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
//		//}
//
//		//-- move to parent --/
//		currentNode = currentNode->parent;
//		tree_up_path_length += 1.0;
//
//		//-- change active player (to get correct reward) --//
//		belonging_player = internalGame->Get_Previous_Player(belonging_player);
//	}
//
//}



void Player_AI_RL::Output_Log_Level_Create_Headers()
{
#if(TOM_GLOBAL_ENABLE_MCTS_OUTPUT_LEVEL)
	if (output_level_headers_created)
		return;

	output_level_headers_created = true;

	// -- lvl0 -- //
#if(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 0)
	gmp->PrintI(0, "setting \t batch_repeat \t ");
	gmp->PrintI(0, "\n");
#endif

#if(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 1)
	// -- lvl1 -- //
	gmp->PrintI(1, "setting \t batch_repeat \t game_repeat \t ");
	gmp->PrintI(1, "\n");
#endif

#if(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 2)
	// -- lvl2 -- //
	gmp->PrintI(2, "setting \t batch_repeat \t game_repeat \t extern_ply_num \t ");
	gmp->PrintI(2, "MCTS_iter_per_ply \n");
#endif

#if(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 3)
	// -- lvl3 -- //
	gmp->PrintI(3, "setting \t batch_repeat \t game_repeat \t extern_ply_num \t MCTS_iteration \t ");
	gmp->PrintI(3, "\n");
#endif

	// -- lvl4 -- //
#if(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 4)
	gmp->PrintI(4, "setting \t batch_repeat \t game_repeat \t extern_ply_num \t MCTS_iteration \t simulated_ply_num \t ");
	gmp->PrintI(4, "\n");
#endif

#if(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 5)
	// -- lvl5 -- //
	gmp->PrintI(5, TOMPLAYER_AI_RL_output_log_level5_header);
	for (int i = 0; i < FUNC_APPROX_NUM_INPUTS; i++)
		gmp->PrintI(5, "L5/child->NN_input_%d \t", i);
	gmp->PrintI(5, "\n");
#endif
#endif
}
// -- END - Output_Log_Level_Create_Headers -- //

double Player_AI_RL::Neural_Network_Threshold_Function(double input_weight_sum, const int function_type)
{

	if (function_type == NN_FUNCTION_TYPES_SIGMOID_CENTER_ZERO){
		return (1.0 / (1.0 + exp(-input_weight_sum)) - 0.5);

	}
	else if (function_type == NN_FUNCTION_TYPES_SIGMOID){
		return (1.0 / (1.0 + exp(-input_weight_sum)));

	}
	else if (function_type == NN_FUNCTION_TYPES_STEP){
		return ((double)(input_weight_sum > 0.0));

	}
	else if (function_type == NN_FUNCTION_TYPES_LINEAR){
		return (input_weight_sum);

	}
	else{
		//wrong parameter call
		gmp->Print(stderr, "Player_AI_RL::Neural_Network_Threshold_Function: ERROR: incorrect function_type: %d\n", function_type);
		return -1;

	}

}