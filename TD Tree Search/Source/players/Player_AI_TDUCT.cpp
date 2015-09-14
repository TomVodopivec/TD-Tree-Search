//include header
#include "Player_AI_TDUCT.hpp"

/**
Constructor for AI UCT player module calling general game player constructor

@param game Pointer to a Game_Engine object (or derivated class)
*/
Player_AI_TDUCT::Player_AI_TDUCT(Game_Engine* game, int player_number) : Player_Engine(game, player_number)
{
	//player definition
	player_name = "TDUCT";

	//temporary moved from Init_Settings()
	Func_App_UCT_num_params = TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_PARAMS;

	//call initialization procedures
	if (game != NULL){

		Initialize();

	}
	else{

		is_initialized = false;

	}
}

//destructor
Player_AI_TDUCT::~Player_AI_TDUCT(void)
{
	if (is_initialized){
		Clear_Memory();
		is_initialized = false;
	}
}

//allocate memory and initialize variables
void Player_AI_TDUCT::Initialize()
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

void Player_AI_TDUCT::Init_Settings()
{
	//init internal variables
	all_actions_num = game->maximum_allowed_moves;
	UCTtree_maxMemorySize = (int)(TOMPLAYER_AI_TDUCT_TREE_SIZE_LIMIT_GB * (1 << 30));
	UCTtree_num_nodes = 0;
	UCTtree_memorySize = 0;

	MCTS_current_iterNum = 0;
	MCTS_current_simuNum = 0;

	//init optimization settings
	internal_game_force_copy = TOMPLAYER_AI_TDUCT_OPTIMIZATION_INTERNAL_FORCE_COPY;

	//init learning parameters
	UCT_param_C = TOMPLAYER_AI_TDUCT_PARAM_C;
	UCT_param_IterNum = TOMPLAYER_AI_TDUCT_PARAM_NUMBER_ITERATIONS;
	UCT_param_SimPerIter = TOMPLAYER_AI_TDUCT_PARAM_SIMULATIONS_PER_ITER;
	UCT_param_defaultPolicy_maxPlys = TOMPLAYER_AI_TDUCT_PARAM_DEFAULT_MAX_PLAYS;
	UCTtree_preserve = TOMPLAYER_AI_TDUCT_PARAM_PRESERVE_TREE;

	//Q-value RL
	QVALUE_param_scoreWeight = TOMPLAYER_AI_TDUCT_PARAM_QVALUE_SCORE_WEIGHT;

	QVALUE_param_alpha = TOMPLAYER_AI_TDUCT_PARAM_QVALUE_ALPHA;
	QVALUE_param_gamma = TOMPLAYER_AI_TDUCT_PARAM_QVALUE_GAMMA;
	QVALUE_param_lambda = TOMPLAYER_AI_TDUCT_PARAM_QVALUE_LAMBDA;
	QVALUE_param_initVal = TOMPLAYER_AI_TDUCT_PARAM_QVALUE_INIT_VAL;

	//visualization
	output_level_headers_created = false;

	//debug variables
	debug_dbl_cnt1 = 0;
	debug_dbl_cnt2 = 0;
}

void Player_AI_TDUCT::Allocate_Memory()
{
	//allocate resources
	internalGame = game->Create_Duplicate_Game();
	simulatedGame = game->Create_Duplicate_Game();
	simulatedGame_startingState = game->Create_Duplicate_Game();
	UCTroot = UCT_Tree_Node_Init(-1, NULL, false);
	UCTroot_memory = UCTroot;

	//simulations feedback structures
	sim_feedback_scores_avg = new double[game->number_players];
	sim_feedback_scores_var = new double[game->number_players];
	sim_feedback_scores = new double*[UCT_param_SimPerIter];
	for (int i = 0; i < UCT_param_SimPerIter; i++)
		sim_feedback_scores[i] = new double[game->number_players];
	sim_feedback_plys = new double[UCT_param_SimPerIter];

}

void Player_AI_TDUCT::Clear_Memory()
{
	//clean up memory
	if (is_initialized){
		if (UCTtree_preserve)
			UCT_Tree_Delete(UCTroot_memory);
		else
			UCT_Tree_Delete(UCTroot);

		delete(internalGame);
		delete(simulatedGame);

		//simulations feedback structures
		delete(simulatedGame_startingState);
		delete[] sim_feedback_scores_avg;
		delete[] sim_feedback_scores_var;
		for (int i = 0; i < UCT_param_SimPerIter; i++)
			delete[] sim_feedback_scores[i];
		delete[] sim_feedback_scores;
		delete[] sim_feedback_plys;

	}
}

//public procedure: signal player that new game has been started
void Player_AI_TDUCT::New_Game()
{

	//reset root (and reset tree, optionally)
	if (UCTtree_preserve){
		UCTroot = UCTroot_memory;
		New_Game2();
	}
	else{
		Reset();		//calls reset1(), newGame(), newGame1()
	}

}

//public procedure: reset player (reset all learning values)
void Player_AI_TDUCT::Reset()
{

	//delete/free entire tree except root
	UCT_Tree_Reset();

	//reset root
	UCTroot->parent = NULL;
	UCT_Tree_Node_Reset(UCTroot);

	return New_Game2();
}

void Player_AI_TDUCT::New_Game2()
{

	//RESET internal game copy
	internalGame->Copy_Game_State_From(game);

	//zero the counters
	UCT_num_plys = 0;
	MCTS_num_all_iterations = 0;
	MCTS_num_all_simulations = 0;

	//null history-storing variables
	lastAction_node = NULL;
}

//public procedure: returns players next selected move
int Player_AI_TDUCT::Get_Move()
{

	int moveNumber;
	int number_internal_moves;

#if(TOMPLAYER_AI_TDUCT_DEBUG_TRACE_SELECTED_NODE)
	gmp->Print("TRACE_NODE_SEL:  ply iter action     value      N      R     Qval\n");
#endif

	//debug: display tree state
	//STDprint_UCTtree_state();
	//STDprintTreeVal(root);

	//How many moves were made in external game since last Get_Move() call
	number_internal_moves = (game->current_plys - internalGame->current_plys);

	//Update internal game to match external game (replay moves in internal game)
	UCT_Update_Internal_Game(number_internal_moves);

	//Correct tree state: set new root and delete part of tree that is unrelevant
	UCT_Tree_Change_Root(number_internal_moves);

	//Execute UCT algortihm and select best action
	moveNumber = UCT();

	//DEBUG
#if(TOMPLAYER_AI_TDUCT_DEBUG_ROOT_CHILDREN_VALUES)
	Output_UCT_Tree_Node_Children(UCTroot);		//show values of roots actions (children)
#endif
#if(TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_GETC_AFTER_MOVE)
	cin.get();
#endif

	//return selected move
	return moveNumber;
}

//Updates internal game to match external game (replay moves in internal game)
void Player_AI_TDUCT::UCT_Update_Internal_Game(int number_actions)
{

	//check if external game should be copied to or replayed in internal game
	if ((game->is_deterministic) && (internal_game_force_copy == false)){

		//play all players moves in internal copy of game (including own last move)
		for (int i = number_actions; i > 0; i--)
			internalGame->Play_Move(game->history_moves[game->current_plys - i + 1]);

		//copy external game to internal game
	}
	else{
		internalGame->Copy_Game_State_From(game, true, internalGame->current_plys - 1);
	}

	//DEBUG: check if move history of external and internal game is equal
#if(TOMPLAYER_AI_TDUCT_DEBUG_HISTORY_COPY_CHECK)
	for (int i = 0; i <= game->current_plys; i++){
		if (game->history_moves[i] != internalGame->history_moves[i]){
			printf("PLAYER AI UCT: UCT_Update_Internal_Game(): game copy error - external and internal game history does not match at index %d: ext %d int %d ... RESETTING UCT PLAYER\n", i, game->history_moves[i], internalGame->history_moves[i]);
			i = game->current_plys + 1;
			Reset();
		}
	}
#endif

}

int Player_AI_TDUCT::UCT()
{
	//execute MCTS iterations with given computational budget
	for (MCTS_current_iterNum = 0; MCTS_current_iterNum < UCT_param_IterNum; MCTS_current_iterNum++){

		//RESET simulated game position to initial state
		simulatedGame->Copy_Game_State_From(internalGame, false);

		//DEBUG
		//internalGame->output_chains_to_STD();
		//simulatedGame->output_chains_to_STD();
		//simulatedGame->output_state_to_STD();
		//printf("sim player %d\n",simulatedGame->current_player);

		//UCT algorithm phases
		UCT_selected_leaf = UCT_Tree_Policy(UCTroot);
		UCT_Simulate(UCT_param_SimPerIter);		//simulates game until end using UCT_Default_Policy() and sets global "sim_feedback..." values
		UCT_Backup(UCT_selected_leaf);			//reads global "sim_feedback..." values

		//check if memory limit was exceeded - TODO: this is a basic version that work well if only 1 node is added per iteration, otherwise the procedure must be implemented inside UCTtreePolicy, where new nodes are allocated
		if (UCTtree_memorySize >= UCTtree_maxMemorySize){
			MCTS_current_iterNum = UCT_param_IterNum;	//end the simulations loop
		}

		//increase global iteration counter
		MCTS_num_all_iterations++;

		//DEBUG
#if(TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL_UCT)
		printf("\nSim num %2d     score", MCTS_current_iterNum);
		//for(int t = 0; t < game->number_players; t++)
		//	printf("  %3.5f",final_rewards[t]);
#if(!TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_ACTIONS_TREE)
		printf("     root  %2d", UCTroot->action_index);
#else
		printf("     tree  %2d", UCTroot->action_index);
		printf("%s", visualizeActionsTree.str().c_str());
		visualizeActionsTree.str("");		//set stringstream to empty
		visualizeActionsTree.clear();		//clear flags
#endif
#if(TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_ACTIONS_PLAYOUT)
		printf("    \t playout:");
		printf("%s", visualizeActionsPlayout.str().c_str());
		visualizeActionsPlayout.str("");	//set stringstream to empty
		visualizeActionsPlayout.clear();	//clear flags
#endif
#endif

#if(TOMPLAYER_AI_TDUCT_DEBUG_TREE_EXPANSION_SIM)
		//Output_UCT_Tree();
		Output_UCT_Tree_Node_Children(UCTroot);
#endif

	}

	//DEBUG
#if(TOMPLAYER_AI_TDUCT_DEBUG_TREE_EXPANSION)
	Output_UCT_Tree();
#endif

	//increase global counter of invoked UCT plys
	UCT_num_plys++;

	// ---- select the best evaluated move ---- //

	//return best action from root (without exploring factors) and remember node
	if (UCTroot->number_explored_children > 0){
		lastAction_node = UCT_Tree_Policy_Best_Child(UCTroot, 0.0);
		return (lastAction_node->action_index);

		//no simulations run - return random action
	}
	else if (UCT_param_IterNum == 0){
		lastAction_node = NULL;
		return game->Select_Move_Random();

		//no valid action (no children explored), return error
	}
	else{
		printf("PLAYER AI UCT: UCT(): action selection error - no valid action available\n");
		lastAction_node = NULL;
		return -1;
	}

	// --- DO NOT WRITE CODE BELOW THIS LINE ---- it will not be executed because of the return's above

}

Player_AI_TDUCT::UCTnode* Player_AI_TDUCT::UCT_Tree_Policy(UCTnode* root)
{

	UCTnode* currentNode = root;
	int terminalNode = (int)(simulatedGame->game_ended);

	//move through the tree and game
	while (terminalNode == 0){

		//check expanding condition and descend tree according to tree policy
		if (currentNode->number_explored_children >= simulatedGame->current_number_moves[simulatedGame->current_player]){

			//select best child node/action
			currentNode = UCT_Tree_Policy_Best_Child(currentNode, 1.0);

			//try
			//{
			//play simulated game (if game not ended yet playMove() returns value 0)
			terminalNode = simulatedGame->Play_Move(currentNode->action_index);
			//}
			//catch (exception& e)
			//{
			//	cout << "!!!Standard exception: " << e.what() << endl;
			//}

			//DEBUG
#if(TOMPLAYER_AI_TDUCT_DEBUG_TRACE_SELECTED_NODE)
			gmp->Print("TRACE_NODE_SEL:  %3d  %3d    %3d  % 8.3f  %5.1f  %5.1f   % 6.3f\n",
				game->current_plys,
				MCTS_current_iterNum,
				currentNode->action_index,
				currentNode->value,
				currentNode->visits,
				currentNode->rewards,
				currentNode->Q_value
				);
#endif

			//expand if not fully expanded
		}
		else{

			//select a nontried action
			currentNode = UCT_Expand(currentNode);

			//play simulated game
			simulatedGame->Play_Move(currentNode->action_index);

			//save information about number of allowed moves (possible children) from the newly created move
			currentNode->number_allowed_actions = simulatedGame->current_number_moves[simulatedGame->current_player];

			//is last node in tree
			terminalNode = 1;

#if(TOMPLAYER_AI_TDUCT_DEBUG_TRACE_SELECTED_NODE)
			gmp->Print("TRACE_NODE_SEL:  %3d  %3d    %3d\n",
				game->current_plys,
				MCTS_current_iterNum,
				currentNode->action_index
				);
#endif
		}

#if(TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_ACTIONS_TREE)
		//sprintf(visualizeActionsTree, "  > %2d", currentNode->action_index);
		if (currentNode->action_index >= 10)
			visualizeActionsTree << "  > " << currentNode->action_index;
		else
			visualizeActionsTree << "  >  " << currentNode->action_index;
		//printf("  > %2d", currentNode->action_index);
#endif

		//DEBUG
		//simulatedGame->output_state_to_STD();
		//simulatedGame->output_chains_to_STD();

	}

	//save number of actions from root to selected leaf (search depth)
	UCTtree_treePolicy_lastDepth = simulatedGame->current_plys - internalGame->current_plys;

	//return selected leaf
	return currentNode;

};

/**
Select next child from given tree node and with given UCT exploration weight C.
*/
Player_AI_TDUCT::UCTnode* Player_AI_TDUCT::UCT_Tree_Policy_Best_Child(UCTnode* parent, double exploration_weight){

	double bestValue;
	int multiple_best, randAction;
	int selectedChild_id;

	bestValue = -DBL_MAX;
	selectedChild_id = -1;

	//OPPONENT RANDOM MOVES
	if (((simulatedGame->current_plys - internalGame->current_plys) % 2 == 1) && ((rand() / (float)(RAND_MAX + 1)) < TOMPLAYER_AI_TDUCT_RANDOM_TREE_OPPONENT_THRESHOLD)){

		multiple_best = parent->number_allowed_actions;

	}
	else{

		//find best-valued children node
		multiple_best = 1;
		for (int i = 0; i < parent->number_allowed_actions; i++){

			UCTnode* child = parent->children[i];

			//check if children was already allocated (for safety)
			if (child != NULL){

				// ------------------------------------PARAMETER SETTING ---------------------------------- //

				// ---- default parameters ---- //
				double set_param_C = UCT_param_C;

				// ---- tom-added parameters ---- //
				double set_QVALUE_param_scoreWeight = QVALUE_param_scoreWeight;
				double set_MC_weight = 1.0 - set_QVALUE_param_scoreWeight;

				// ------------ NON-CONSTANT PARAMETER VALUES ------------ //
				double netInputs[TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS];
				double sumNetOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS];
				double functionNetOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];
				double sumNetHid[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];
				double functionHidOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];

#if(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 1)
				// ---- direct param search ---- //
				//use this in combination with LRP_improved_v1() and LRP_test_wrapper()

				//INPUTS are equal to weights (direct search)
				for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++)
					netInputs[inp] = Func_App_UCT_Params->parameter_weights[inp];

#if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)
				set_param_C = netInputs[0] + UCT_param_C;
				set_QVALUE_param_scoreWeight = netInputs[1] + QVALUE_param_scoreWeight;
				set_MC_weight = 1.0 - set_QVALUE_param_scoreWeight;		//was erroneously missing prior 17.3.2014
#endif

#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 2)
				// ---- single NN: weighted output ---- //
				//use this in combination with LRP_improved_v1() and LRP_test_wrapper()

				//WARNING: THE NUMBER OF Func_App_UCT_Params must be set in Player_AI_TDUCT.hpp with the constant TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_PARAMS
	
				//define INPUTS here
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = child->visits;
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = 1.0/child->visits;
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = (1.0 / (child->sum_plys_sim_phase + 1.0)) * 2.0;		//test 8.1
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = ((double)MCTS_current_iterNum / UCT_param_IterNum);	//test 1.1

				//single layer neural network
				for (int out = 0; out < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS; out++){
					sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
					for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++)
						sumNetOut[out] += Func_App_UCT_Params->parameter_weights[(inp + 1) + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)] * netInputs[inp];
					functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
				}

				//map net outputs to desired parameters, scale and bias parameters

				set_param_C = functionNetOut[0] * 10.0 + UCT_param_C;
				set_QVALUE_param_scoreWeight = functionNetOut[2] * 10.0 + QVALUE_param_scoreWeight;
				set_MC_weight = 1.0 - set_QVALUE_param_scoreWeight;		//was erroneously missing prior 17.3.2014

				//bound parameters to zero or above
				//if(set_param_C < 0) set_param_C = 0.0;	//this was commented out on 2014_02_20, previous to this date all experiments with single NN used this bound

				// END ---- single NN: weighted output ---- //

#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 3)
				// ---- feed forward perceptron (dual layer NN) ---- //		
				//use this in combination with LRP_improved_v1() and LRP_test_wrapper()

				//define INPUTS here
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = 1.0/child->visits;
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = ((double)MCTS_current_iterNum / UCT_param_IterNum);
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = (child->visits_in_last_UCT / UCT_param_IterNum);		//this was bugged until 2014_01 Q-Values test, so that visits_in_last_UCT was equal to visits (this way this whole input rapresented the average number of visits per iteration -> the probability of visiting the node in a single iteration)
				//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (1 / (child->sum_plys_sim_phase + 1)) * 2.0;

				//hidden layer
				for (int hid = 0; hid < TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER; hid++){
					sumNetHid[hid] = Func_App_UCT_Params->parameter_weights[0 + hid * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
					for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++){
						sumNetHid[hid] += netInputs[inp] * Func_App_UCT_Params->parameter_weights[(inp + 1) + hid * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//net inputs
					}
					functionHidOut[hid] = Neural_Network_Threshold_Function(sumNetHid[hid]);
				}

				//output layer
				for (int out = 0; out < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS; out++){
					sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER + 1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
					for (int hid = 0; hid < TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER; hid++){
						sumNetOut[out] += (functionHidOut[hid] * Func_App_UCT_Params->parameter_weights[(hid + 1) + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER + 1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)]);	//hidden layer outputs
					}
					functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
				}

				//map net outputs to desired parameters, scale and bias parameters
				//set_param_C =					functionNetOut[0] * 10.0 + UCT_param_C;
				//set_QVALUE_param_scoreWeight =	functionNetOut[2] * 10.0 + QVALUE_param_scoreWeight;
				//set_MC_weight =					1.0 - set_QVALUE_param_scoreWeight;		//was erroneously missing prior 17.3.2014

				//bound parameters to zero or above
				//if(set_param_C < 0) set_param_C = 0.0;

				// END ---- feed forward perceptron (dual layer NN) ---- //
				// END ------------ NON-CONSTANT PARAMETER VALUES ------------ //
#endif
				// ------------------------------------END - PARAMETER SETTING ---------------------------------- //

				// ------------------------------------VALUE EQUATION COMPONENTS ---------------------------------- //

				// ---- default equations ---- //
				double MC_value = (child->rewards / child->visits);
				double UCB_value = sqrt(2 * log(parent->visits) / child->visits);

				// ---- consider whether is this an exploratory move or an output best move ---- //
				set_param_C *= exploration_weight;	//neccessary for select best child (when C must be 0.0)
				//set_QVALUE_param_scoreWeight *= exploration_weight;	//not used yet

				// ---- Q-value RL values instead of normal average ---- //

				MC_value = set_QVALUE_param_scoreWeight*(child->Q_value + 0.5) + set_MC_weight*(MC_value);	//TDfourth: translated back to interval [0,1]


				// ------------------------------------END - VALUE EQUATION COMPONENTS ---------------------------------- //

				// ------------------------------------VALUE CALCULATION ---------------------------------- //

				// ---- plain UCB equation ---- //
				child->value = MC_value + 2.0 * set_param_C * UCB_value;

				// ------------------------------------END - VALUE CALCULATION ---------------------------------- //

				// ---- DEBUG PRINT ----//

				//printf("%3.3f\t%3.3f\n", (double)MCTS_current_iterNum / UCT_param_IterNum, (child->sum_plys_sim_phase / child->visits / simulatedGame->maximum_plys));
				//if(child->number_allowed_actions != 7)
				//printf("%3.3f\t%d\t%d\n",child->visits_in_last_UCT / UCT_param_IterNum, child->number_allowed_actions,  game->maximum_allowed_moves);
				//printf("%3.3f\t%3.3f\n", (double)game->current_plys / game->maximum_plys, (double)simulatedGame->current_plys / simulatedGame->maximum_plys);
				////TEST 7
				//printf("%6.3f \t %10.0f \t %6.3f \t %6.3f \t %3d \t %10.0f \t %6.3f\n",
				//	(child->sum_plys_sim_phase / child->visits / (parent->sum_plys_to_end + simulatedGame->current_plys)),
				//	child->sum_plys_sim_phase,
				//	child->visits,
				//	parent->sum_plys_to_end,
				//	simulatedGame->current_plys,
				//	parent->visits,
				//	(child->sum_plys_sim_phase / child->visits / ((parent->sum_plys_to_end)/parent->visits + simulatedGame->current_plys))
				//	);

				//printf("DEBUG CHILD VAL: %d %3.1f\n", i, child->value);

				// ---- END - DEBUG PRINT ----//

				//remember best children and count number of equal best children
				if (child->value == bestValue){
#if((!TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM)&&(!TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM_MULTIPLE_BEST))
					multiple_best++;
#endif
				}
				else if (child->value > bestValue){
					selectedChild_id = i;
					bestValue = child->value;
					multiple_best = 1;
				}

				//OUTPUT ALL VALUES - level 5
#if(TOM_GLOBAL_ENABLE_MCTS_OUTPUT_LEVEL)
				gmp->PrintI(5, TOMPLAYER_AI_TDUCT_output_log_level5_format,

					game->experiment_repeat_index,
					game->batch_repeat_index,
					game->game_repeat_index,
					game->current_plys,
					MCTS_current_iterNum,
					simulatedGame->current_plys,
					i,

					child->action_index,
					child->number_allowed_actions,
					child->number_explored_children,

					child->visits,
					child->rewards,

					child->value,
					MC_value,
					UCB_value,
					child->Q_value,

					set_param_C,

					child->sum_simulations,
					child->sum_plys_sim_phase,
					child->sum_plys_to_end,
					child->last_update_iteration,
					child->visits_in_last_UCT,

					child->last_selected_child_id,
					child->best_value_child_id,
					child->num_best_childs,
					child->num_changes_best_child

					);
#if(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE > 1)
				for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++){
					gmp->PrintI(5, "%7.3f \t", netInputs[inp]);
				}
#endif
				gmp->PrintI(5, "\n");
#endif

			} // END - check if children was already allocated (for safety)

		}

	}

	//if multiple best actions/children, break ties uniformly random
	if (multiple_best > 1){
		randAction = (int)floorf((rand() / (float)(RAND_MAX + 1)) * multiple_best);
		for (int i = 0; i < parent->number_allowed_actions; i++){
			if (parent->children[i] != NULL){
				if (parent->children[i]->value >= bestValue){
					if (randAction <= 0){
						selectedChild_id = i;
						i = parent->number_allowed_actions;	//break loop
					}
					else{
						randAction--;
					}
				}
			}
		}
	}

	//memorize values/calculations
	if (selectedChild_id != parent->best_value_child_id){
		parent->best_value_child_id = selectedChild_id;
		parent->num_changes_best_child++;
	}
	parent->num_best_childs = multiple_best;
	parent->last_selected_child_id = selectedChild_id;

	//debug check
	//dbgTmpInt2 = selectedChild_id;
	if ((selectedChild_id < 0) || (selectedChild_id >= internalGame->maximum_allowed_moves)){
		//gmp->Print("WARNING: PLAYER AI UCT_TOMTEST: UCT_Tree_Policy_Best_Child: selectedChild_id %d (parent_moves %d game_max_moves %d) (multiple %d)\n",selectedChild_id,parent->number_allowed_actions,internalGame->maximum_allowed_moves,multiple_best);
		//gmp->Print("---\n");
		//gmp->Print("plyE %3d  mctsI %3d  plyI %3d   bestValue %3.3f\n", game->current_plys,MCTS_current_iterNum,simulatedGame->current_plys,bestValue);
		//for(int i = 0; i < parent->number_allowed_actions; i++){
		//	gmp->Print("c%2d  %3.3f\n",i,parent->children[i]->value);
		//}
		//gmp->Print("---\n");
		//gmp->Flush();

		//select random move
		selectedChild_id = (int)floorf((rand() / (float)(RAND_MAX + 1)) * (float)parent->number_allowed_actions);
	}
	//-- end - debug check

	//return selected untried action
	return (parent->children[selectedChild_id]);
}

/**
Expand the tree
*/
Player_AI_TDUCT::UCTnode* Player_AI_TDUCT::UCT_Expand(UCTnode* parent){

	int randAction, cntAvailable;
	UCTnode* selectedChild;

#if(TOM_DEBUG)
	if ((parent->children == NULL) && (parent->number_explored_children > 0)){
		printf("WARNING: PLAYER AI UCT: UCT_Expand(): node children list NOT allocated but number of explored children is %d\n", parent->number_explored_children);
	}
	else if ((parent->children != NULL) && (parent->number_explored_children <= 0)){
		printf("WARNING: PLAYER AI UCT: UCT_Expand(): node children list allocated but number of explored children is %d ... ALLOCATING LIST (causing memory leak)\n", parent->number_explored_children);
		UCT_Tree_Node_AllocateList(parent);
	}
#endif

	//allocate memory resources when exploring first action from node
	//if(parent->children == NULL){
	if (parent->number_explored_children == 0){
		UCT_Tree_Node_AllocateList(parent);
	}
	//printf("DEBUG: parent p %d %d\n", parent, parent->allowedActionNum);
	//for(int i = 0; i < parent->allowedActionNum; i++)
	//	printf("DEBUG: child p %d %d\n", parent->children[i], i);

	//choose random untried action
#if((!TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM)&&(!TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM_EXPAND))
	randAction = (int)((rand() / (float)(RAND_MAX + 1))*(parent->number_allowed_actions - parent->number_explored_children));
#else
	randAction = 0;
#endif

	//find nontried action, cycle through all actions
	cntAvailable = 0;
	selectedChild = NULL;
	for (int i = 0; i < all_actions_num; i++){

		//check available actions
		if (simulatedGame->current_moves[simulatedGame->current_player][i]){

			//check if action was already tried / already exists in the tree
			if ((parent->children[cntAvailable]) == NULL){
				if (randAction <= 0){

					//allocate and init new children
					parent->children[cntAvailable] = UCT_Tree_Node_Init(i, parent, true);

					//mark as selected child/action
					selectedChild = parent->children[cntAvailable];
					parent->last_selected_child_id = cntAvailable;

					//increase number of explored children actions/nodes
					//parent->number_explored_children++; WAS MOVED in UCT_Tree_Node_Init()

					//break the loop
					i = all_actions_num;
				}
				else{
					randAction--;
				}
			}
			//END - check if action was already tried
			cntAvailable++;

		}
		//END - check available actions
	}

	//return selected untried action
	return selectedChild;
}

/**
Run simulations from the UCT-tree leaf by using the Default Policy

Updates MCTS_num_all_simulations counter, however not online but in BATCH at the end of all requested simulations
*/
void Player_AI_TDUCT::UCT_Simulate(int num_simulations, const bool calc_variance){

	int plys_at_tree_leaf;

	//-- store values before playout phase begins --//
	plys_at_tree_leaf = simulatedGame->current_plys;	//remember number of moves at beginning of playout
	if (num_simulations > 1){
		simulatedGame_startingState->Copy_Game_State_From(simulatedGame, false);		//save game state at beginning of playout phase
	}

	//-- compute first simulation and calculate score --//
	UCT_Default_Policy();		//score is stored in simulatedGame->score

	//-- save feedback/results from first simulation --//

	//feedback: scores for each player
	for (int i = 0; i < simulatedGame->number_players; i++){

		sim_feedback_scores_avg[i] = simulatedGame->score[i];
		if (calc_variance)
			sim_feedback_scores[0][i] = sim_feedback_scores_avg[i];
	}

	//feedback: duration (number of plys) of the playout phase
	sim_feedback_plys_avg = (simulatedGame->current_plys) - plys_at_tree_leaf;
	if (calc_variance)
		sim_feedback_plys[0] = sim_feedback_plys_avg;

	//-- compute the rest of the simulations --//
	if (num_simulations == 1){

		for (MCTS_current_simuNum = 1; MCTS_current_simuNum < num_simulations; MCTS_current_simuNum++){

			//reset simulated game state to match state at beginning of playout phase
			simulatedGame->Copy_Game_State_From(simulatedGame_startingState, false);

			//compute simulation
			UCT_Default_Policy();

			//save feedback/results
			for (int i = 0; i < simulatedGame->number_players; i++){
				sim_feedback_scores_avg[i] += simulatedGame->score[i];
				if (calc_variance)
					sim_feedback_scores[MCTS_current_simuNum][i] = simulatedGame->score[i];
			}
			sim_feedback_plys_avg += ((simulatedGame->current_plys) - plys_at_tree_leaf);
			sim_feedback_plys[MCTS_current_simuNum] = (simulatedGame->current_plys) - (simulatedGame_startingState->current_plys);

		}

		//average results
		for (int i = 0; i < simulatedGame->number_players; i++){
			sim_feedback_scores_avg[i] /= num_simulations;
		}
		sim_feedback_plys_avg /= num_simulations;

		//calculate variance
		//TODO
	}

	//store number of computed simulations
	sim_feedback_num_sims = num_simulations;

	//BATCH update global simulation counter
	MCTS_num_all_simulations += num_simulations;
}

/**
Play default policy from current game position until game end
*/
void Player_AI_TDUCT::UCT_Default_Policy(){

	int gameStatus, lastMove;
	int num_simulated_plys;

	//simulate game until game-end
	num_simulated_plys = 0;
	gameStatus = (int)(simulatedGame->game_ended);
	while ((gameStatus == 0) && ((simulatedGame->current_plys - internalGame->current_plys) < UCT_param_defaultPolicy_maxPlys)){

		//DEBUG
		//if(simulatedGame->number_of_plays == 38) 
		//	printf("DEBUG: plys == %d", simulatedGame->number_of_plays);	

		//random policy
#if(!TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM)
		lastMove = simulatedGame->Select_Move_Random();
#else
		lastMove = simulatedGame->Select_Move(0);
		//lastMove = simulatedGame->Select_Move(simulatedGame->current_number_moves[simulatedGame->current_player] - 1);
		//lastMove = simulatedGame->Select_Move_Random();
#endif

		//play move in internal simulated game
#if(TOM_DEBUG)
		gameStatus = simulatedGame->Play_Move(lastMove);
#else
		gameStatus = simulatedGame->Play_Move_Unsafe(lastMove);
#endif

		//DEBUG
#if((TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL_UCT)&&TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_ACTIONS_TREE)
		//sprintf(visualizeActionsTree, "  > %2d", currentNode->action_index);
		visualizeActionsPlayout << "  > " << lastMove;
		//printf("  > %2d", currentNode->action_index);
#endif
#if(TOMPLAYER_AI_TDUCT_DEBUG_SIMULATED_GAMES_OUT)
		printf("-playout-\n");
		simulatedGame->Output_Board_State();
		//simulatedGame->output_state_to_STD();
		//simulatedGame->output_chains_to_STD();
		//printf("Moves: %d %d\n",simulatedGame->num_moves[0], simulatedGame->num_moves[1]);
#endif

	}

	//calculate score at game end
	simulatedGame->Calculate_Score();
}

/**
Single- or two-player backup reward through the tree
*/
void Player_AI_TDUCT::UCT_Backup(UCTnode* leaf){

	UCTnode* currentNode = leaf;
	int belonging_player;
	double tree_up_path_length;

	//TODO IMPROVE: NOW TEMPORARY SOLUTION FOR SINGLEPLAYER and TWOPLAYER games
	if (game->number_players > 1)
		//select correct players' reward: bitwise replacement for upper if-sentences (instead of modulo 2)
		belonging_player = (UCTtree_treePolicy_lastDepth & 1) == (internalGame->current_plys & 1);
	else
		belonging_player = 0;

	// -- Q-values reinforcement learning algorithm -- //

	double set_QVALUE_param_alpha = QVALUE_param_alpha;
	double set_QVALUE_param_gamma = QVALUE_param_gamma;
	double set_QVALUE_param_lambda = QVALUE_param_lambda;

	double netInputs[TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS];
	double sumNetOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS];
	double functionNetOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];
	double sumNetHid[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];
	double functionHidOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];

#if(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 1)
	// -- Q-value parameter search and approximation -- //

	//INPUTS arr equal to weights (direct search)
	for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++)
		netInputs[inp] = Func_App_UCT_Params->parameter_weights[inp];

	set_QVALUE_param_alpha = Func_App_UCT_Params->parameter_weights[2] + QVALUE_param_alpha;
	set_QVALUE_param_gamma = Func_App_UCT_Params->parameter_weights[3] + QVALUE_param_gamma;
	set_QVALUE_param_lambda = Func_App_UCT_Params->parameter_weights[4] + QVALUE_param_lambda;

#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 2)
	// ---- single NN: weighted output ---- //

	//define INPUTS here
	if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = sim_feedback_scores_avg[belonging_player];
	if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = sim_feedback_plys_avg / simulatedGame->maximum_plys;
	//if(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (currentNode->parent->sum_plys_sim_phase + sim_feedback_plys_avg) / (currentNode->parent->sum_simulations + 1) ;	//these two indicators were not yet updated for parent node (will be in next iteration of backup loop below, so here we need to correct their value in advance)
	if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (currentNode->parent->sum_plys_sim_phase + sim_feedback_plys_avg) / (currentNode->parent->sum_simulations + 1) / simulatedGame->maximum_plys;	//these two indicators were not yet updated for parent node (will be in next iteration of backup loop below, so here we need to correct their value in advance)

	//single layer neural network
	for (int out = 0; out < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS; out++){
		sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
		for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++)
			sumNetOut[out] += Func_App_UCT_Params->parameter_weights[(inp + 1) + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)] * netInputs[inp];
		functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
	}

#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 3)
	// ---- feed forward perceptron (dual layer NN) ---- //		

	//define INPUTS here
	if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = sim_feedback_scores_avg[belonging_player];
	if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = sim_feedback_plys_avg / simulatedGame->maximum_plys;
	if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (currentNode->parent->sum_plys_sim_phase + sim_feedback_plys_avg) / (currentNode->parent->sum_simulations + 1) / simulatedGame->maximum_plys;	//these two indicators were not yet updated for parent node (will be in next iteration of backup loop below, so here we need to correct their value in advance)


	//hidden layer
	for (int hid = 0; hid < TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER; hid++){
		sumNetHid[hid] = Func_App_UCT_Params->parameter_weights[0 + hid * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
		for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++){
			sumNetHid[hid] += netInputs[inp] * Func_App_UCT_Params->parameter_weights[(inp + 1) + hid * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//net inputs
		}
		functionHidOut[hid] = Neural_Network_Threshold_Function(sumNetHid[hid]);
	}

	//output layer
	for (int out = 0; out < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS; out++){
		sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER + 1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
		for (int hid = 0; hid < TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER; hid++){
			sumNetOut[out] += (functionHidOut[hid] * Func_App_UCT_Params->parameter_weights[(hid + 1) + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER + 1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)]);	//hidden layer outputs
		}
		functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
	}

	// END ---- feed forward perceptron (dual layer NN) ---- //

#endif
	// -- end - Q-value parameter search and approximation -- //

	double TDerror[2];

	// -- eligibility trace -- //

	double Q_trace = 1.0;
	for (int i = 0; i < sim_feedback_plys_avg; i++){
		Q_trace *= set_QVALUE_param_gamma;
	}


	// -- value of the next node after the leaf node -- //

	double TD_next_state_value = Q_trace*(sim_feedback_scores_avg[belonging_player] - 0.5);	//assume that all simulation nodes have value equal to reward
	if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_MERGED_BOOTSTRAPPING)
		TD_next_state_value = 0.0;

	// -- first TD error -- //

	double TD_leaf_state_value = currentNode->Q_value;	//the actual value of the leaf node
	if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_WEIGHTED_REWARDS)
		TD_leaf_state_value = 0.0;						//assume neutral value of leaf node
	//TD_leaf_state_value = QVALUE_param_initVal;		//assume initial value of leaf node (default = 0.0)

	TDerror[belonging_player] = ((TD_next_state_value - TD_leaf_state_value));
	TDerror[1 - belonging_player] = (-(TD_next_state_value - TD_leaf_state_value));

	if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_FULL_TD){
		TDerror[belonging_player] = 0.0;
		TDerror[1 - belonging_player] = 0.0;
		TD_next_state_value /= set_QVALUE_param_gamma;
	}


	// -- end - Q-values reinforcement learning algorithm -- //

	//propagate reward up through the tree
	tree_up_path_length = 0;
	for (int i = 0; i < UCTtree_treePolicy_lastDepth + 1; i++){

		// -- update current node -- //
		//basic UCT values
		currentNode->visits += 1.0;
		currentNode->rewards += sim_feedback_scores_avg[belonging_player];

		// -- new indicators -- //

		currentNode->sum_simulations += sim_feedback_num_sims;
		currentNode->sum_plys_sim_phase += sim_feedback_plys_avg;
		currentNode->sum_plys_to_end += (sim_feedback_plys_avg + tree_up_path_length);

		//count node visits since last UCT() call (since last external game ply and UCT tree change)
		if (currentNode->last_update_iteration < MCTS_num_all_iterations - MCTS_current_iterNum){
			currentNode->visits_in_last_UCT = 1.0;
			currentNode->last_update_iteration = MCTS_num_all_iterations;
		}
		else{
			currentNode->visits_in_last_UCT += 1.0;
		}

		// -- Q-values temporal difference update  -- //


		
		//set_QVALUE_param_alpha = 1.0 / currentNode->visits;
		//double alpha = (1.0 + set_QVALUE_param_alpha) * 1.0 / currentNode->visits;
		
		if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_SINGLE_BACKUP){
			currentNode->Q_value = currentNode->Q_value + set_QVALUE_param_alpha * TDerror[belonging_player];
			TDerror[belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
			TDerror[1 - belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
		}
		else if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_WEIGHTED_REWARDS){
			currentNode->Q_value = currentNode->Q_value + TDerror[belonging_player];
			TDerror[belonging_player] *= (set_QVALUE_param_gamma);
			TDerror[1 - belonging_player] *= (set_QVALUE_param_gamma);
		}
		else if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_MERGED_BOOTSTRAPPING)
		{
			TDerror[belonging_player] = ((set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
			TDerror[1 - belonging_player] = -(-(set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
			TD_next_state_value = (- currentNode->Q_value);
			currentNode->Q_value = currentNode->Q_value + set_QVALUE_param_alpha * Q_trace * (sim_feedback_scores_avg[belonging_player] - 0.5 + TDerror[belonging_player]);
			Q_trace *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
		}
		else if (TOMPLAYER_AI_TDUCT_VARIANT == TOMPLAYER_AI_TDUCT_VARIANTS_FULL_TD){
			TDerror[belonging_player] += ((set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
			TDerror[1 - belonging_player] += (-(set_QVALUE_param_gamma*TD_next_state_value - currentNode->Q_value));
			TD_next_state_value = (-currentNode->Q_value);
			currentNode->Q_value = currentNode->Q_value + set_QVALUE_param_alpha * TDerror[belonging_player];
			TDerror[belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
			TDerror[1 - belonging_player] *= (set_QVALUE_param_lambda*set_QVALUE_param_gamma);
		}

		//-- move to parent --/
		currentNode = currentNode->parent;
		tree_up_path_length += 1.0;

		//-- change active player (to get correct reward) --//
		belonging_player = internalGame->Get_Previous_Player(belonging_player);
	}

}

/**
UCT Tree Node - initialization
*/
Player_AI_TDUCT::UCTnode* Player_AI_TDUCT::UCT_Tree_Node_Init(int action, UCTnode* parent, const bool parentIncreaseChildCount)
{
	UCTnode* node;

	//allocate and init
	node = new UCTnode;
	node->action_index = action;
	node->parent = parent;
	node->children = NULL;

	//reset
	UCT_Tree_Node_Reset(node);

	//increase counter of nodes and memory consumption (needed for allocation)
	UCTtree_num_nodes++;					//this is for debug only
	UCTtree_memorySize += sizeof(UCTnode);

	//increase parents number of allocated children
	if (parentIncreaseChildCount)
		parent->number_explored_children++;

	return node;
}

/**
UCT Tree Node - reset values
*/
void Player_AI_TDUCT::UCT_Tree_Node_Reset(UCTnode* node)
{

	//node->number_allowed_actions = -1;	//not really needed for execution, only for visualization/debug

	node->visits = 0.0;
	node->rewards = 0.0;
	node->number_explored_children = 0;

	node->last_update_iteration = -1;
	node->sum_simulations = 0;
	node->sum_plys_sim_phase = 0.0;
	node->sum_plys_to_end = 0.0;

	node->computation_time = 0.0;
	node->knowledge_gain = 0.0;

	node->visits_in_last_UCT = 0.0;

	node->last_selected_child_id = -1;
	node->best_value_child_id = -1;
	node->num_best_childs = 0;
	node->num_changes_best_child = 0;

	//Q-value RL
	node->Q_value = QVALUE_param_initVal;

#if(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE > 0)
	double netInputs[TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS];
	double sumNetOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS];
	double functionNetOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];
	double sumNetHid[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];
	double functionHidOut[TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER];

#if(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 1)

	//TODO: correct: nodes of opponent player must be set on (1-node->Q_value)
	//node->Q_value = Func_App_UCT_Params->parameter_weights[11] + QVALUE_param_initVal;

#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 2)
	// ---- single NN: weighted output ---- //

	//define INPUTS here
	if (node->parent != NULL){
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = (double)simulatedGame->current_plys / simulatedGame->maximum_plys;
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = node->parent->Q_value;
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (double)node->parent->visits / UCT_param_IterNum;
	}
	else{
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = (double)simulatedGame->current_plys / simulatedGame->maximum_plys;
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = QVALUE_param_initVal;	//supposed root initial Q value
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = 0.0;
	}

	//single layer neural network
	for (int out = 0; out < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS; out++){
		sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
		for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++)
			sumNetOut[out] += Func_App_UCT_Params->parameter_weights[(inp + 1) + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)] * netInputs[inp];
		functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
	}

	//node->Q_value = functionNetOut[0]	* 4.0 + QVALUE_param_initVal;	//translate QVALUE_param_initVal by +-2

	//if(node->Q_value != QVALUE_param_initVal)
	//	printf("test  %6.3f  %6.3f  %6.3f  -  %6.3f\n", netInputs[0], netInputs[1], netInputs[2], node->Q_value);

#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 3)
	// ---- feed forward perceptron (dual layer NN) ---- //		

	//define INPUTS here
	if (node->parent != NULL){
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = (double)simulatedGame->current_plys / simulatedGame->maximum_plys;
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = node->parent->Q_value;
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = (double)node->parent->visits / UCT_param_IterNum;
	}
	else{
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 0)	netInputs[0] = (double)simulatedGame->current_plys / simulatedGame->maximum_plys;
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 1)	netInputs[1] = QVALUE_param_initVal;	//supposed root initial Q value
		if (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS > 2)	netInputs[2] = 0.0;
	}

	//hidden layer
	for (int hid = 0; hid < TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER; hid++){
		sumNetHid[hid] = Func_App_UCT_Params->parameter_weights[0 + hid * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
		for (int inp = 0; inp < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; inp++){
			sumNetHid[hid] += netInputs[inp] * Func_App_UCT_Params->parameter_weights[(inp + 1) + hid * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//net inputs
		}
		functionHidOut[hid] = Neural_Network_Threshold_Function(sumNetHid[hid]);
	}

	//output layer
	for (int out = 0; out < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS; out++){
		sumNetOut[out] = Func_App_UCT_Params->parameter_weights[0 + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER + 1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)];	//BIAS
		for (int hid = 0; hid < TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER; hid++){
			sumNetOut[out] += (functionHidOut[hid] * Func_App_UCT_Params->parameter_weights[(hid + 1) + out * (TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER + 1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS + 1)]);	//hidden layer outputs
		}
		functionNetOut[out] = Neural_Network_Threshold_Function(sumNetOut[out]);
	}

	//node->Q_value = functionNetOut[0]	* 4.0 + QVALUE_param_initVal;

	// END ---- feed forward perceptron (dual layer NN) ---- //

#endif
#endif
}

/**
UCT Tree Node - allocate children (actions) list
*/
void Player_AI_TDUCT::UCT_Tree_Node_AllocateList(UCTnode* node)
{
	//allocate and init list
	node->children = new UCTnode*[node->number_allowed_actions];
	for (int i = 0; i < node->number_allowed_actions; i++)
		node->children[i] = NULL;

	//increase memory consumption counter
	UCTtree_memorySize += (node->number_allowed_actions)*sizeof(UCTnode*);
}

void Player_AI_TDUCT::UCT_Tree_Change_Root(int number_actions)
{
	//is root change needed?
	if (number_actions > 0){

		//trim tree, delete unrelevant part of tree
		if (!UCTtree_preserve){

			UCTtree_newRoot = NULL;
			UCT_Tree_Trim(UCTroot, number_actions);

			//new root has been found
			if (UCTtree_newRoot != NULL){

				//delete old root and set new root
				if (UCTroot != UCTtree_newRoot){		//redundant check, but may be needed in some special cases
					delete(UCTroot);
					UCTroot = UCTtree_newRoot;
					UCTroot->parent = NULL;
				}

				//these two mutualy exclude:
				//decrease tree memory size counter for old UCTroot as recursive call did not decrease it
				//UCTtree_num_nodes--;
				//UCTtree_memorySize -= sizeof(UCTnode);
				//increase tree memory size counter (because in recursion we assumed that no root was found)				
				//UCTtree_num_nodes++;
				//UCTtree_memorySize += sizeof(UCTnode);

				//new root not found, selected actions were not present in tree
			}
			else{

				//decrease tree memory size counter for old UCTroot as recursive call did not decrease it
				//UCTtree_num_nodes--;
				//UCTtree_memorySize -= sizeof(UCTnode);

				//reset root node
				UCTroot->action_index = internalGame->history_moves[internalGame->current_plys];
				UCTroot->children = NULL;
				UCT_Tree_Node_Reset(UCTroot);
				UCTroot->number_allowed_actions = internalGame->current_number_moves[internalGame->current_player];

				//DEBUG
#if(TOMPLAYER_AI_TDUCT_DEBUG_MEMORY_SIZE_COUNT)
				if ((UCTtree_num_nodes != 1) || (UCTtree_memorySize != sizeof(UCTnode)))
					printf("PLAYER AI UCT: Tree_Change_Root(): tree error - tree incorrectly deleted, remaining nodes %d\n", UCTtree_num_nodes);
#endif

			}

			//preserve complete tree structure in memory, only move root pointer to different node
		}
		else{

			UCT_Tree_Preserve();

		}

		//root change is nood needed: this code executed only once per game, before the first move in played (so this code will be executed only if the player is first on move)
	}
	else{

		//this is needed because number_allowed_actions is set at expansion (and at root-change), but is not set for first created root node, because it is not created by the "expand" procedure
		UCTroot->number_allowed_actions = internalGame->current_number_moves[internalGame->current_player];

	}

}


/**
Select new tree root for current game state and trim tree if UCTtree_preserve is not set: delete all nodes (and free memory) except active branch
WARNING: does not delete first call branchRoot node
*/
void Player_AI_TDUCT::UCT_Tree_Trim(UCTnode* branchRoot, int remaining_depth)
{

	//new root has not yet been found
	if (remaining_depth > 0){

		//search deeper in the tree if branchRoot is not a leaf - if has children
		if (branchRoot->children != NULL){

			//decrease tree memory size counter (must be done before loop, because number_explored_children is decreased to 0)
			UCTtree_num_nodes -= (branchRoot->number_explored_children);
			UCTtree_memorySize -= ((branchRoot->number_allowed_actions*sizeof(UCTnode*)+branchRoot->number_explored_children*sizeof(UCTnode)));

			//loop through all children
			for (int i = 0; i < branchRoot->number_allowed_actions, branchRoot->number_explored_children > 0; i++){

				//children is valid
				if (branchRoot->children[i] != NULL){

					//selected action found in tree
					if (branchRoot->children[i]->action_index == internalGame->history_moves[internalGame->current_plys - remaining_depth + 1]){

						UCT_Tree_Trim(branchRoot->children[i], remaining_depth - 1);

						//delete child if it is not the new found root
						if (remaining_depth - 1 > 0)
							delete(branchRoot->children[i]);

						//delete non-selected tree branch
					}
					else{

						UCT_Tree_Delete(branchRoot->children[i]);

					}

					//decrease counter of children
					branchRoot->number_explored_children--;

					//delete child
					//delete(branchRoot->children[i]);
				}
			}

			//delete root node list of children
			delete[] branchRoot->children;

		}

		//new root has been found
	}
	else{

		UCTtree_newRoot = branchRoot;

	}

}


/**
Recursively delete tree from selected node, including root node
WARNING: does not delete first call branchRoot node
*/
void Player_AI_TDUCT::UCT_Tree_Delete(UCTnode* branchRoot)
{

	//search deeper in the tree if branchRoot is not a leaf - if has children
	if (branchRoot->children != NULL){

		//decrease tree memory size counter (must be done before loop, because number_explored_children is decreased to 0)
		UCTtree_num_nodes -= (branchRoot->number_explored_children);
		UCTtree_memorySize -= ((branchRoot->number_allowed_actions*sizeof(UCTnode*)+(branchRoot->number_explored_children)*sizeof(UCTnode)));	//size decreased by number of children nodes and by size of children list of root node

		//loop through all children
		for (int i = 0; i < branchRoot->number_allowed_actions, branchRoot->number_explored_children > 0; i++){
			if (branchRoot->children[i] != NULL){
				UCT_Tree_Delete(branchRoot->children[i]);
				branchRoot->number_explored_children--;
			}
		}

		//delete root node list of children
		delete[] branchRoot->children;
	}

	//delete self
	delete(branchRoot);

}

/**
Recursively delete selected tree branch, without root node
*/
void Player_AI_TDUCT::UCT_Tree_Reset()
{

	UCTnode* branchRoot;

	//from which node to reset the tree
	if (!UCTtree_preserve)
		branchRoot = UCTroot;
	else
		branchRoot = UCTroot_memory;

	//node has children
	if (branchRoot->children != NULL){

		//find and delete children nodes
		for (int i = 0; i < branchRoot->number_allowed_actions, branchRoot->number_explored_children > 0; i++){
			if (branchRoot->children[i] != NULL){
				UCT_Tree_Delete(branchRoot->children[i]);
				branchRoot->number_explored_children--;
			}
		}

		//delete root node list of children
		delete[] branchRoot->children;
		branchRoot->children = NULL;
	}

	//reset tree memory size counter
	UCTtree_num_nodes = 1;
	UCTtree_memorySize = sizeof(UCTnode);

	branchRoot->action_index = game->history_moves[game->current_plys];
	UCT_Tree_Node_Reset(branchRoot);
}

//TODO
void Player_AI_TDUCT::UCT_Tree_Preserve()
{
}
//OLD CODE
////enable tree preservation
//void PlayerGoAI_UCT::UCTperserveTree_enable(){
//	memoryUCTroot = root;
//	UCTtree_preserve = true;
//}
//
////disable tree preservation - INCOMPLETE, TODO
//void PlayerGoAI_UCT::UCTperserveTree_disable(){
//	//delete tree except active root (for current game)
//	UCTtree_preserve = false;
//	trimUCTtree(memoryUCTroot,root->actionNum);
//}
//

/**
Output entire tree with all information (see implementation code for details about output format)
*/
void Player_AI_TDUCT::Output_UCT_Tree()
{
	gmp->Print("\n========== BEGIN OUTPUT_UCT_TREE ==========\n\nTREE SIZE: %d nodes, memory: %d B (%.3f MB)\n\n", UCTtree_num_nodes, UCTtree_memorySize, UCTtree_memorySize / 1024.0 / 1024.0);
	gmp->Print("Leafs < Root\n");
	Output_UCT_Tree_Branch(UCTroot);
	gmp->Print("\n========== END OUTPUT_UCT_TREE ==========\n\n");
}

void Player_AI_TDUCT::Output_UCT_Tree_Node_Children(UCTnode* parent)
{
	printf("\n========== BEGIN OUTPUT_UCT_TREE_NODE_CHILDREN ==========\naction: visits rewards  \tvalue: \tQval\n");
	for (int i = 0; i < UCTroot->number_allowed_actions; i++){
		if (UCTroot->children[i] != NULL){
			printf("   %3d:  %5.0f  %6.1f  \t%3.3f \t %3.3f\n",
				UCTroot->children[i]->action_index,
				UCTroot->children[i]->visits,
				UCTroot->children[i]->rewards,
				UCTroot->children[i]->value,
				UCTroot->children[i]->Q_value + 0.5
				);
		}
		else{
			printf("Untried action: parent->children[%d]\n", i);
		}
	}
	gmp->Print("\n========== END OUTPUT_UCT_TREE_NODE_CHILDREN ==========\n\n");
}

/**
Output part of tree starting from branchRoot
*/
void Player_AI_TDUCT::Output_UCT_Tree_Branch(UCTnode* branchRoot)
{
	UCTnode* tmpNode;

	//print current node and its parents
	gmp->Print("%d", branchRoot->action_index);
	tmpNode = branchRoot->parent;
	while (tmpNode != NULL){
		gmp->Print(" < %d", tmpNode->action_index);
		tmpNode = tmpNode->parent;
	}

	//print current nodes' values
	gmp->Print("\t :\t %2.1f %2.1f", branchRoot->visits, branchRoot->rewards);

	//search deeper in the tree if branchRoot is not a leaf - if has children
	if (branchRoot->children != NULL){

		//print children info
		gmp->Print("\t %d/%d :", branchRoot->number_explored_children, branchRoot->number_allowed_actions);

		//print current nodes' children list
		for (int i = 0, c = 0; i < branchRoot->number_allowed_actions, c < branchRoot->number_explored_children; i++){
			if (branchRoot->children[i] != NULL){
				gmp->Print(" %d", branchRoot->children[i]->action_index);
				c++;
			}
		}

		gmp->Print("\n");

		//recursively call children nodes' output
		for (int i = 0, c = 0; i < branchRoot->number_allowed_actions, c < branchRoot->number_explored_children; i++){
			if (branchRoot->children[i] != NULL){
				Output_UCT_Tree_Branch(branchRoot->children[i]);
				c++;
			}
		}

	}
	else{
		gmp->Print("\n");
	}

}

void Player_AI_TDUCT::Debug_UCT_Tree_MemoryState()
{

	int size1, size2;

	printf("\nTREE MEMORY STATE\n");
	printf("Current tree: ");
	size1 = Debug_UCT_Tree_Size(UCTroot);
	printf("\n");
	printf("Memory tree:  ");
	if (this->UCTtree_preserve)
		size2 = Debug_UCT_Tree_Size(UCTroot_memory);
	else
		size2 = -1;
	printf("\n");
	printf("Tree info: num nodes: %d size %d\n", UCTtree_num_nodes, UCTtree_memorySize);
	printf("Size: current: %d memory: %d\n\n", size1, size2);
}

//TODO

int Player_AI_TDUCT::Debug_UCT_Tree_Size(UCTnode*)
{
	return 0;
}



void Player_AI_TDUCT::Output_Log_Level_Create_Headers()
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
	gmp->PrintI(5, TOMPLAYER_AI_TDUCT_output_log_level5_header);
	for (int i = 0; i < TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS; i++)
		gmp->PrintI(5, "L5/child->NN_input_%d \t", i);
	gmp->PrintI(5, "\n");
#endif
#endif
}
// -- END - Output_Log_Level_Create_Headers -- //

double Player_AI_TDUCT::Neural_Network_Threshold_Function(double input_weight_sum, const int function_type)
{

	if (function_type == TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_SIGMOID_CENTER_ZERO){
		return (1.0 / (1.0 + exp(-input_weight_sum)) - 0.5);

	}
	else if (function_type == TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_SIGMOID){
		return (1.0 / (1.0 + exp(-input_weight_sum)));

	}
	else if (function_type == TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_STEP){
		return ((double)(input_weight_sum > 0.0));

	}
	else if (function_type == TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_LINEAR){
		return (input_weight_sum);

	}
	else{
		//wrong parameter call
		gmp->Print(stderr, "Player_AI_TDUCT::Neural_Network_Threshold_Function: ERROR: incorrect function_type: %d\n", function_type);
		return -1;

	}

}

//
///**
//return number of nodes in tree from branchRoot
//*/
//int PlayerGoAI_UCT::STDprintNumChildren(UCTnode* branchRoot){
//
//	int numNodes = 1;
//
//	if(branchRoot->explored_children > 0){
//
//		printf("%d[",branchRoot->explored_children);
//
//		for(int i = 0; i < branchRoot->allowedActionNum; i++){
//			if(branchRoot->children[i] != NULL){
//				numNodes += STDprintNumChildren(branchRoot->children[i]);
//			}
//		}
//
//		printf("]");
//
//	}else{
//
//		printf(".");
//
//	}
//
//	return numNodes;
//
//}
//
///**
//return number of nodes in tree from branchRoot
//*/
//int PlayerGoAI_UCT::STDprintTreeVal(UCTnode* branchRoot){
//
//	printf("%3.0f[",(branchRoot->rewards/branchRoot->visits)*100);
//
//	if(branchRoot->explored_children > 0){
//
//		for(int i = 0; i < branchRoot->allowedActionNum; i++){
//			if(branchRoot->children[i] != NULL){
//				STDprintTreeVal(branchRoot->children[i]);
//			}
//		}
//	}
//
//	printf("]");
//
//	return 0;
//
//}