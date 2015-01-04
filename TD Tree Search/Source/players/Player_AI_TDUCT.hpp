/**
Testing of new AI Player by Tom Vodopivec
Using UCT, AMAF, RAVE

ISSUES: PRESERVING TREE CURRENTLY NOT IMPLEMENTED COMPLETLY
*/


#ifndef _TOM_PLAYER_AI_TDUCT_
#define _TOM_PLAYER_AI_TDUCT_

//includes
#include "..\core\Player_Engine.hpp"
#include "..\optimizers\Tom_Lrp.hpp"
#include "..\tools\Support_MultiPrint.hpp"
//#include "..\tools\Support_FastApproximatePow.hpp"

// ---- defines ---- //

//MCTS value equation learning parameters
#define TOMPLAYER_AI_TDUCT_PARAM_C					(1.0 / (2*sqrt(2)))

//MCTS policy parameters
#define TOMPLAYER_AI_TDUCT_PARAM_NUMBER_ITERATIONS	1000
#define TOMPLAYER_AI_TDUCT_PARAM_SIMULATIONS_PER_ITER	1
#define TOMPLAYER_AI_TDUCT_PARAM_DEFAULT_MAX_PLAYS	(game->maximum_plys)
#define TOMPLAYER_AI_TDUCT_BEST_CHILD_EXPLORATION_ENABLED		true

//MCTS tree and optimization parameters
#define TOMPLAYER_AI_TDUCT_PARAM_PRESERVE_TREE		false
#define TOMPLAYER_AI_TDUCT_TREE_SIZE_LIMIT_GB			1.0
#define TOMPLAYER_AI_TDUCT_OPTIMIZATION_INTERNAL_FORCE_COPY	false
#define TOMPLAYER_AI_TDUCT_SIMULATIONS_CALC_VARIANCE	false	//store individual results for multiple simulations per iteration and calculate variance

#define TOMPLAYER_AI_TDUCT_PARAM_QVALUE_SCORE_WEIGHT	1.0		//weight of Q-value when combining with MC value (when TOMPLAYER_AI_TDUCT_QVALUE_EQUATION_TYPE == 2)
#define	TOMPLAYER_AI_TDUCT_PARAM_QVALUE_ALPHA			0.2	//Q-value RL algorithm: delta Q step rate alpha 
#define	TOMPLAYER_AI_TDUCT_PARAM_QVALUE_GAMMA			0.9	//Q-value RL algorithm: children max reward weight gamma
#define TOMPLAYER_AI_TDUCT_PARAM_QVALUE_LAMBDA			0.9	//Q-value RL algorithm: eligibility traces decay rate
#define TOMPLAYER_AI_TDUCT_PARAM_QVALUE_INIT_VAL		0.0		//Q-value RL algorithm: initial Q-value

#define TOMPLAYER_AI_TDUCT_VARIANT						TOMPLAYER_AI_TDUCT_VARIANTS_SINGLE_BACKUP

enum TOMPLAYER_AI_TDUCT_VARIANTS {
	TOMPLAYER_AI_TDUCT_VARIANTS_SINGLE_BACKUP,
	TOMPLAYER_AI_TDUCT_VARIANTS_WEIGHTED_REWARDS,
	TOMPLAYER_AI_TDUCT_VARIANTS_MERGED_BOOTSTRAPPING,
	TOMPLAYER_AI_TDUCT_VARIANTS_FULL_TD					//NOT FULLY TESTED!
};



#define TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE		0	//LRP parameter search (MUST set on 0 when evaluating fixed setting)
//0 - disabled, constant parameter values
//1 - direct search
//2 - single neuron (sigmoid function) search
//3 - dual-layer feed forward net

#define	TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS		2	//set number of weights for the function approximator or (if dual-layer perceptron) number of inputs in the net
#define	TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS	3	//set number of outputs from the single- or dual-layer neural network
#define	TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER		3	//dual-layer perceptron: number of hidden layer neurons
#define TOMPLAYER_AI_TDUCT_FUNC_APPROX_NEURAL_FUNC	TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_SIGMOID_CENTER_ZERO	//neuron threshold function: see below at "enum" for a list of possible functions

enum TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES {
	TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_SIGMOID_CENTER_ZERO,
	TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_SIGMOID,
	TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_STEP,
	TOMPLAYER_AI_TDUCT_NN_FUNCTION_TYPES_LINEAR
};

//TESTING OPPONENT MODEL
#define TOMPLAYER_AI_TDUCT_RANDOM_TREE_OPPONENT_THRESHOLD		0.0		//0.0 = disabled

// -- debug defines --

//defines - DEBUG checking
#define TOMPLAYER_AI_TDUCT_DEBUG_MEMORY_SIZE_COUNT	(1 && TOM_DEBUG)
#define TOMPLAYER_AI_TDUCT_DEBUG_HISTORY_COPY_CHECK	(1 && TOM_DEBUG)

//defines - DEBUG behaviour
#define TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM		((1 && TOM_DEBUG) || TOM_DISABLE_RANDOM)

//defines - DEBUG VISUALIZATION
#define TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL			2		//set visualization depth
#define TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL_UCT		((1 >= TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL) && TOM_DEBUG)

#define TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_GETC_AFTER_MOVE	(0 && TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL_UCT)
#define TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_ACTIONS_TREE		(0 && TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL_UCT)
#define TOMPLAYER_AI_TDUCT_VISUALIZE_UCT_ACTIONS_PLAYOUT	(0 && TOMPLAYER_AI_TDUCT_VISUALIZE_LEVEL_UCT)

#define TOMPLAYER_AI_TDUCT_DEBUG_ROOT_CHILDREN_VALUES	(0 && TOM_DEBUG)
#define TOMPLAYER_AI_TDUCT_DEBUG_TRACE_SELECTED_NODE	0 //(0 && TOM_DEBUG)
#define TOMPLAYER_AI_TDUCT_DEBUG_TREE_EXPANSION		(0 && TOM_DEBUG)
#define TOMPLAYER_AI_TDUCT_DEBUG_TREE_EXPANSION_SIM	0 //(0 && TOM_DEBUG)
#define TOMPLAYER_AI_TDUCT_DEBUG_SIMULATED_GAMES_OUT	(0 && TOM_DEBUG)

#define TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM_MULTIPLE_BEST	0
#define TOMPLAYER_AI_TDUCT_DEBUG_DISABLE_RANDOM_EXPAND		0

// -- END of user defines section -- //

// -- auto-defines -- //
#if(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE < 2)
#define TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_PARAMS		TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS
#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 2)
#define TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_PARAMS		(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS+1)*TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS
#elif(TOMPLAYER_AI_TDUCT_PARAM_FUNC_APP_TYPE == 3)
#define TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_PARAMS		(TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_INPUTS+1) + TOMPLAYER_AI_TDUCT_FUNC_APPROX_NUM_OUTPUTS*(TOMPLAYER_AI_TDUCT_FUNC_APPROX_HIDD_LAYER+1))
#endif

//external global variables
extern MultiPrinter * gmp;	//multiprinter object defined in main.hpp
extern int experiment_settings_id;
/**
Basic AI UCT player class
*/
class Player_AI_TDUCT : public Player_Engine
{

public:

	//public structures
	typedef struct UCTnode {

		//node-action link
		int action_index;

		//tree structure variables
		int number_allowed_actions;
		int number_explored_children;
		UCTnode* parent;
		UCTnode** children;

		//learning values
		double visits;
		double rewards;

		//memorized calculations
		double value;

		//tom testing new indicators
		int	sum_simulations;			//total number of simulations executed from selected node and its subtree (if num_simulations per iteration is 1 (default) then this value equals to visits)
		double sum_plys_sim_phase;
		double sum_plys_to_end;

		double computation_time;	//not implemented
		double knowledge_gain;		//not implemented

		int last_update_iteration;
		double visits_in_last_UCT;		//number of visits in the last call of UCT() (since root was lastly changed and tree prunned)

		int last_selected_child_id;
		int	best_value_child_id;
		int num_best_childs;
		int num_changes_best_child;

		//Q-value RL
		double Q_value;

		//analysis: history and statistical variables
#if(TOM_GLOBAL_ENABLE_MCTS_OUTPUT_LEVEL)
		//double previous_value;
		//double previous_value_MC;
		//double previous_value_UCB;
		//double previous_value_AMAF;

		//int previous_best_child_id;
		//int previous_num_best_child;
#endif
	} UCTnode;

	//public procedures
	Player_AI_TDUCT(Game_Engine* game = NULL, int player_number = TOMPLAYER_PLAYER_NUMBER);
	virtual ~Player_AI_TDUCT();
	virtual void Initialize();
	virtual void Reset();
	virtual void New_Game();
	virtual int  Get_Move();
	//void Before_Move(int move);
	//void End_Game();

	//public procedures - debug and visualization	
	virtual void Output_UCT_Tree();
	virtual void Output_UCT_Tree_Branch(UCTnode*);
	virtual void Output_UCT_Tree_Node_Children(UCTnode*);
	virtual void Debug_UCT_Tree_MemoryState();
	virtual int  Debug_UCT_Tree_Size(UCTnode*);
	virtual void Output_Log_Level_Create_Headers();

	//void Output();
	//void STDprint_UCTtree_state();	//debug procedure for printing current tree info
	//int  STDprintNumChildren(UCTnode* branchRoot);	//prints number of children of each node to standard output
	//int  STDprintTreeVal(UCTnode* branchRoot);	//prints number of children of each node to standard output

	//public procedures - UCT algorithm
	//void UCTperserveTree_enable();
	//void UCTperserveTree_disable();

	//public variables - player settings

	//public variables - optimization settings
	bool	internal_game_force_copy;

	//public variables - UCT learning parameters
	int		UCT_param_IterNum;					//number of iterations per move
	int		UCT_param_SimPerIter;				//number of simulations per iteration
	double	UCT_param_C;						//exploration factor
	int		UCT_param_defaultPolicy_maxPlys;	//maxium number of moves per simulated game
	int		UCTtree_maxMemorySize;				//maximum size of tree in memory

	//Q-value RL algorithm
	double QVALUE_param_scoreWeight;	//weight of Q-value when combining with MC value [0,1]

	double QVALUE_param_alpha;
	double QVALUE_param_gamma;
	double QVALUE_param_lambda;
	double QVALUE_param_initVal;

	//public variables - UCT
	UCTnode* UCTroot;
	UCTnode* UCTroot_memory;

	//public variables - function approximation parameters
	Tom_Function_Approximator* Func_App_UCT_Params;
	int Func_App_UCT_num_params;

	//public variables - current state
	int UCT_num_plys;
	int MCTS_current_iterNum;
	int MCTS_current_simuNum;
	int MCTS_num_all_iterations;
	int MCTS_num_all_simulations;

	//public vairables - debug and visualization settings
	int  output_type;
	double	debug_dbl_cnt1, debug_dbl_cnt2;
	int	 output_level_headers_created;

protected:

	//private protected procedures
	virtual void Init_Settings();
	virtual void Allocate_Memory();
	virtual void Clear_Memory();
	virtual void New_Game2();

	//private protected procedures - UCT
	virtual int			UCT();
	virtual UCTnode*	UCT_Tree_Policy(UCTnode* root);
	virtual UCTnode*	UCT_Tree_Policy_Best_Child(UCTnode* parent, double exploration_weight);
	virtual void		UCT_Simulate(int num_simulations, const bool calc_variance = TOMPLAYER_AI_TDUCT_SIMULATIONS_CALC_VARIANCE);
	virtual void		UCT_Default_Policy();
	virtual UCTnode*	UCT_Expand(UCTnode* parent);
	virtual void		UCT_Backup(UCTnode* leaf);

	virtual void		UCT_Update_Internal_Game(int number_actions);
	virtual void		UCT_Tree_Change_Root(int number_actions);
	virtual void		UCT_Tree_Trim(UCTnode* branchRoot, int remaining_depth);
	virtual void		UCT_Tree_Delete(UCTnode* branchRoot);
	virtual void		UCT_Tree_Reset();
	virtual void		UCT_Tree_Preserve();

	virtual UCTnode*	UCT_Tree_Node_Init(int action, UCTnode* parent, const bool parentIncreaseChildCount);	//node: initialize
	virtual void		UCT_Tree_Node_AllocateList(UCTnode* node);	//node: allocate children list
	virtual void		UCT_Tree_Node_Reset(UCTnode* node);		//node: reset values to initial

	virtual double		Neural_Network_Threshold_Function(double input_weight_sum, const int function_type = TOMPLAYER_AI_TDUCT_FUNC_APPROX_NEURAL_FUNC);
	//private protected procedures - debug and visualization	

	//private protected variables
	//double* actionsWeight;
	//int* actionsNumWin;
	//int* actionsNumSel;
	//bool* actionsPlayed;
	int all_actions_num;

	//private protected variables - UCT
	int UCTtree_treePolicy_lastDepth;
	int UCTtree_num_nodes;
	int UCTtree_memorySize;
	Game_Engine* internalGame;
	Game_Engine* simulatedGame;
	UCTnode* lastAction_node;		//last played move
	UCTnode* UCTtree_newRoot;		//next UCT root

	int* AMAF_flagList;

	//feedback information from simulations
	UCTnode*	UCT_selected_leaf;
	Game_Engine* simulatedGame_startingState;
	int			sim_feedback_num_sims;		//should this be long long ?
	double*		sim_feedback_scores_avg;
	double*		sim_feedback_scores_var;
	double**	sim_feedback_scores;
	double		sim_feedback_plys_avg;
	double		sim_feedback_plys_var;
	double*		sim_feedback_plys;

	//private protected variables - UCT parameters
	bool UCTtree_preserve;

	//private protected variables - debug and visualization
	stringstream visualizeActionsTree;
	stringstream visualizeActionsPlayout;

	int		dbgTmpInt1;
	double	dbgTmpInt2;
};

//logging by levels output format
#define TOMPLAYER_AI_TDUCT_output_log_level5_header \
	"L-/game->experiment_repeat_index \t" \
	"L0/game->batch_repeat_index \t" \
	"L1/game->game_repeat_index \t" \
	"L2/game->current_plys \t" \
	"L3/player->MCTS_current_iterNum \t" \
	"L4/simulatedGame->current_plys \t" \
	"L5/currentNode->children_index \t" \
	\
	"L5/child->action_index \t" \
	"L5/child->number_allowed_actions \t" \
	"L5/child->number_explored_children \t" \
	\
	"L5/child->visits \t" \
	"L5/child->rewards \t" \
	\
	"L5/child->value \t" \
	"L5/child->MC_value \t" \
	"L5/child->UCB_value \t" \
	"L5/child->Q_value \t" \
	\
	"L5/child->set_param_C \t" \
	"L5/child->sum_simulations \t" \
	"L5/child->sum_plys_sim_phase \t" \
	"L5/child->sum_plys_to_end \t" \
	"L5/child->last_update_iteration \t" \
	"L5/child->visits_in_last_UCT \t" \
	\
	"L5/child->last_selected_child_id \t" \
	"L5/child->best_value_child_id \t" \
	"L5/child->num_best_childs \t" \
	"L5/child->num_changes_best_child \t" \

#define TOMPLAYER_AI_TDUCT_output_log_level5_format \
	"%2d \t" \
	"%2d \t" \
	"%4d \t" \
	"%3d \t" \
	"%4d \t" \
	"%3d \t" \
	"%3d \t" \
	\
	"%3d \t" \
	"%3d \t" \
	"%3d \t" \
	\
	"%7.1f \t" \
	"%7.2f \t" \
	\
	"%7.3f \t" \
	"%7.3f \t" \
	"%7.3f \t" \
	"%7.3f \t" \
	\
	"%6.3f \t" \
	\
	"%5d \t" \
	"%7.3f \t" \
	"%7.3f \t" \
	"%5d \t" \
	"%7.3f \t" \
	\
	"%3d \t" \
	"%3d \t" \
	"%3d \t" \
	"%4d \t" \

#endif