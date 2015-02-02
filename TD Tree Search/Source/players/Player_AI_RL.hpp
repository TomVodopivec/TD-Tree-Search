/**
The general reinforcement learning player
2015.01.25
Author: Tom Vodopivec
*/

#ifndef _TOM_PLAYER_AI_RL_
#define _TOM_PLAYER_AI_RL_

//includes
#include "..\core\Player_Engine.hpp"
#include "..\tools\Tool_HashTree.hpp"
#include "..\optimizers\Tom_Lrp.hpp"
#include "..\tools\Support_MultiPrint.hpp"

//external global variables
extern MultiPrinter * gmp;	//multiprinter object defined in main.hpp
extern int experiment_settings_id;

/**
The general reinforcement learning player
*/
class Player_AI_RL : public Player_Engine
{

public:

	// ---- defines ---- //

// WARNING: presets override some other configuration settings
#define DEFAULT_PRESET_ALGORITHM	NO_PRESET_ALGORITHM
	enum PRESET_ALGORITHMS{
		NO_PRESET_ALGORITHM,		// No preset used: all configuration options apply (none is overriden)
		ALGORITHM_MC_ONPOLICY,		// On-policy Monte Carlo control: equals to offline replacing-traces TD(1) with alpha = (1/visits)
		ALGORITHM_TD_ZERO_ONPOLICY,	// On-policy TD(0), SARSA(0)	
		ALGORITHM_TD_LAMBDA,		// General TD(lambda), SARSA(lambda)
		ALGORITHM_WATKINS_Q,		// Watkin's Q(lambda)
		ALGORITHM_NAIVE_Q,			// Naive Q(lambda), a Watkin's Q-learning variant that does not zero eligibility traces for exploratory actions
		//ALGORITHM_PENGS_Q,		// -- NOT IMPLEMENTED YET -- Peng's Q(lambda), a Q-learning variant that does not zero traces for all exploratory actions -> a merge between Watkin's Q(lambda) and SARSA(lambda)
		ALGORITHM_UCT				// Upper Confidence Bounds applied to Trees, the most popular Monte Carlo Tree Search algorithm
	};

#define DEFAULT_CONTROL_POLICY		CONTROL_EGREEDY
	enum CONTROL_POLICIES{
		CONTROL_EGREEDY,
		CONTROL_UCB
	};
#define DEFAULT_POLICY_EVALUATION		EVALUATION_TDLAMBDA_ONPOLICY
	enum POLICY_EVALUATION_TYPES{
		EVALUATION_TDLAMBDA_ONPOLICY,				// the general onpolicy TD(lambda) evaluation policy -> produces the SARSA(lambda) algorithm
		EVALUATION_TDLAMBDA_OFFPOLICY_Q_LEARNING,	// Watkin's or Naive Q(lambda) algorithm
		//EVALUATION_TDLAMBDA_OFFPOLICY_PENGS_Q,	// -- NOT IMPLEMENTED YET -- 
	};

#define DEFAULT_TD_UPDATE_TYPE	TD_UPDATE_OFFLINE
	enum TD_UPDATE_TYPES{
		TD_UPDATE_ONLINE,			// update after each action, default for RL methods, equals to offline updates if transpositions are not used (it is useless if state-actions are not revisited multiple times in the same episode)
		TD_UPDATE_OFFLINE,			// the original offline update (after the end of each episode), default for MC methods (also MCTS). Temporary stores changes to values while backuping and after all backups it updates the actual values.
		TD_UPDATE_OFFLINE_INPLACE,  // a variant of offline update that immediately updates the actual values - inplace (it does not temporary store the value changes)
		//TD_UPDATE_OFFLINE_ASYNC,	// asynchronous from-end-to-start offline update that is less computationally heavy (iterates only once through the trajectory, O(n) instead of O(n*n)) -- TODO: is this even possible when using transpositions and replacing traces? (because one must not update the same state more than once)
	};

#define DEFAULT_Q_TRACE_TYPE	Q_TRACE_REPLACING	
	enum Q_TRACE_TYPES{			// if transposistions are not used, then all options are equal
		Q_TRACE_REPLACING,		// usually performs better, used to produce first-visit MC
		Q_TRACE_ACCUMULATING	// used to produce every-visit MC -> not good, tends to diverge (nodes get infinite values)
		//Q_TRACE_ACTIONEXCLUSIVE	-> NOT YET IMPLEMENTED
	};

#define DEFAULT_TRACE_EXPLORATORY_RESET		Q_TRACE_EXPLORATORY_RESET_DISABLED
	enum Q_TRACE_RESET_TYPES{
		Q_TRACE_EXPLORATORY_RESET_DISABLED,
		Q_TRACE_EXPLORATORY_RESET_ENABLED
	};

#define DEFAULT_USE_TRANSPOSITIONS		(Game_Engine::TRANSPOSITION_TYPES::TRANSPOSITIONS_STATES)
	// TRANSPOSITIONS_DISABLED,			// if states cannot be distinguished or state-space is too large, then a search tree is grown (default for UCT)
	// TRANSPOSITIONS_STATES,			// evaluate states V(s) <- TD
	// TRANSPOSITIONS_STATEACTIONS		// evaluate state-actions Q(s,a) <- SARSA / Q-learning

#define DEFAULT_OFFPOLICY_BACKUP_RECHECK_BEST	(false)		// true or false: Recheck best child value when backuping (increases computational burden). Applies only to offpolicy learning and makes a difference only when using transpositions with offline inplace backups, or when using async backups.

#define DEFAULT_NUM_NEW_NODES_PER_EPISODE		-1
	// -1 - memorize all (default for RL methods)
	//  0 - no memorization (produces random algorithms)
	//  1 - UCT's default setting
	// >1 - arbitrary positive integer value allowed

#define DEFAULT_ROLLOUT_ASSUMPTION	ROLLOUT_NODE_ASSUME_INITIAL_VALUE
	enum ROLLOUT_ASSUMPTIONS{					// assume non-memorized nodes in MCTS simulation have ...
		ROLLOUT_NODE_ASSUME_INITIAL_VALUE,		// ... the default initial value
		//ROLLOUT_NODE_ASSUME_NEUTRAL_VALUE,	// ... a neutral value, this is 0.0
		//ROLLOUT_NODE_ASSUME_LAST_VALUE,		// ... the value of the last memorized node (leaf in the tree)
		//ROLLOUT_NODE_ASSUME_CONVERGED_REWARD	// ... already converged to their optimal value regarding the received reward or the first encountered memorized state afterwards (if transpositions are used)
	};
	
#define DEFAULT_UPDATESTEP_ALPHA_TYPE	ALPHA_MONTE_CARLO
	enum UPDATESTEP_ALPHA_TYPES{
		ALPHA_CONSTANT,		// constant update step (alpha value (set by parameters par_td_alpha)
		ALPHA_MONTE_CARLO,	// calculating the statistical mean: alpha is computed at each update for each node by (1/visit_counter)
	};

#define DEFAULT_UCB_VISITS_TYPE		UCB_VISITS_TOTAL	
	enum UCB_VISIT_TYPES{		// if transposistions are not used, then both options are equal
		UCB_VISITS_TOTAL,		// consider the total number of visits of a state (or state-action) - use the counter that updates after each actual visit
		UCB_VISITS_EPISODES		// consider the number of terminal updates the state received (the number of episodes that visited that state) - use the counter that updates once per episode
	};
#define DEFAULT_UCB_NORMALIZATION_TYPE	UCB_NORMALIZATION_GLOBAL
	enum UCB_NORMALIZATION_TYPES{
		UCB_NORMALIZATION_GLOBAL,			// use global Q-value normalization bounds, assume whole state-space has same bounds (it is not discount with gamma, so it might not be a good choice for discounting tasks)
		UCB_NORMALIZATION_LOCAL,			// use local (current state) normalization bounds, assume bounds may differ across the state-space
		UCB_NORMALIZATION_LOCAL_GLOBAL		// use global bounds if local are not yet valid (not yet known or not initialized)
	};
#define DEFAULT_UCB_NORMALIZATION_GLOBAL_TYPE	UCB_NORMALIZATION_GLOBAL_KNOWN
	enum UCB_NORMALIZATION_GLOBAL_TYPES{
		UCB_NORMALIZATION_GLOBAL_KNOWN,		// use the known min/max return (sum of rewards) per episode
		UCB_NORMALIZATION_GLOBAL_OBSERVED,	// use the observed min/max return (sum of rewards) per episode
	};
#define DEFAULT_UCB_NORMALIZATION_LOCAL_TYPE	UCB_NORMALIZATION_LOCAL_QVAL
	enum UCB_NORMALIZATION_LOCAL_TYPES{
		UCB_NORMALIZATION_LOCAL_OBSERVED,	// use current state's known min/max return
		UCB_NORMALIZATION_LOCAL_QVAL,		// use current branch's min/max Q-value
		UCB_NORMALIZATION_LOCAL_CHILDREN	// use current state's min/max Q-value
	};

#define DEFAULT_NONEPISODICTASKS_UPDATEINTERVAL	100
	// the number of steps between updates for non-episodic tasks (if updates are not online)

#define DEFAULT_PAR_EPSILON		1.0
#define DEFAULT_PAR_UCB_C		(sqrt(2.0))

#define DEFAULT_PAR_TASK_GAMMA	1.0
#define DEFAULT_PAR_TD_ALPHA	0.1
#define DEFAULT_PAR_TD_LAMBDA	1.0
#define DEFAULT_PAR_TD_INITVAL	0.0

#define DEFAULT_NUM_EPISODES_PER_MOVE		100		//computational resource limit: number of episodes per external move, set on -1 for no limit
#define DEFAULT_SIMULATEDACTIONS_PER_MOVE	-1		//computational resource limit: number of simulated actions per external move, set on -1 for no limit
#define DEFAULT_SIMULATED_HORIZON_LENGTH	-1		//horizon length for simulated episodes (number of actions per episode), set -1 for no limit

#define DEFAULT_OPPONENT_ALIGNMENT	OPPONENT_ADVERSARY
	enum OPPONENT_ALIGNMENTS{
		OPPONENT_ADVERSARY,		// produces MinMax search
		OPPONENT_COOPERATIVE
		//OPPONENT_INDEPENDENT	// implementation not ready yet: should have it's own data tree structures for rewards (a vector of rewards by players for each node)
	};

#define DEFAULT_OPPONENT_POLICY		OPPONENT_SELFPLAY
	enum OPPONENT_POLICIES{
		OPPONENT_RANDOM,
		OPPONENT_GREEDY,
		OPPONENT_SELFPLAY,		// selfplay: uses same policy as agent
		//OPPONENT_HANDSET		// not done yet: must be implemented for each game individually
	};

	enum REWARD_GOALS{
		REWARD_MAXIMIZE,
		REWARD_MINIMIZE,
		GOAL_UNKNOWN		// to mark other player's actions whose purpose was unknown (used for opponent's move on external game)
	};

#define EPSILON_TIEBRAKER		((double)(0.000000001))
#define SMALLEST_TDERROR		EPSILON_TIEBRAKER
#define EPSILON_TRACE_CUTOFF	EPSILON_TIEBRAKER


	//MCTS tree and optimization parameters
#define DEFAULT_MEMORY_LIMIT_MB			1024
#define OPTIMIZATION_INTERNAL_FORCE_COPY	false

	//VISUALIZATION
// the general switch to set the depth of output printing(0 - disabled, 1 - after each external move, 2 - after each episode, 3 - after each simulated move)
#define	DEFAULT_OUTPUT_DEPTH	1

//individual switches (printing depths for each individual visualization component, 0 - disabled)
#define DEFAULT_OUTPUT_TRAJECTORY_DEPTH		0	// last followed trajectory (suggested max 2)
#define DEFAULT_OUTPUT_MEMORY_DEPTH			2	// memorized structures (tree or hash table) (suggested max 2)
#define DEFAULT_OUTPUT_SUMMARY_DEPTH		2	// stats summary (suggested max 2)
#define DEFAULT_OUTPUT_CURRENTINFO_DEPTH	3	// current info (counters, root node value) (max 3)
#define DEFAULT_OUTPUT_SIMGAMESTATE_DEPTH	0	// current state/position of the simulated game (max 3)

#define DEFAULT_OUTPUT_TDBACKUP_DEPTH		0	// TD backups, output_depth must be at least 2! (0 - disabled, 1 - print TD errors, 2 - output whole backups)

#define DEFAULT_OUTPUT_PAUSE_DEPTH			0	// pauses depth (waits for user to press key, 0 - disabled)

//additional visualization settings
#define DEFAULT_OUTPUT_MEMORY_TREEDEPTH		-1	// print depth of the memorzied tree (-1 - entire tree, 0 - root, 1 - root's children, ... )

////---- OLD DEFINES


#define PARAM_FUNC_APP_TYPE		0	//LRP parameter search (MUST set on 0 when evaluating fixed setting)
	//0 - disabled, constant parameter values
	//1 - direct search
	//2 - single neuron (sigmoid function) search
	//3 - dual-layer feed forward net

#define	FUNC_APPROX_NUM_INPUTS		2	//set number of weights for the function approximator or (if dual-layer perceptron) number of inputs in the net
#define	FUNC_APPROX_NUM_OUTPUTS		3	//set number of outputs from the single- or dual-layer neural network
#define	FUNC_APPROX_HIDD_LAYER		3	//dual-layer perceptron: number of hidden layer neurons
#define FUNC_APPROX_NEURAL_FUNC	NN_FUNCTION_TYPES_SIGMOID_CENTER_ZERO	//neuron threshold function: see below at "enum" for a list of possible functions

	enum NN_FUNCTION_TYPES {
		NN_FUNCTION_TYPES_SIGMOID_CENTER_ZERO,
		NN_FUNCTION_TYPES_SIGMOID,
		NN_FUNCTION_TYPES_STEP,
		NN_FUNCTION_TYPES_LINEAR
	};

	//TESTING OPPONENT MODEL
#define RANDOM_TREE_OPPONENT_THRESHOLD		0.0		//0.0 = disabled


	// -- code from old TomTest implementation

#define TOMPLAYER_AI_UCT_TOMTEST_PARAM_SIMULATIONS_PER_ITER	1

	// -- debug defines --

	//defines - DEBUG checking
#define DEBUG_HISTORY_COPY_CHECK	(1 && TOM_DEBUG)

	//defines - DEBUG behaviour
#define DEBUG_DISABLE_RANDOM		((1 && TOM_DEBUG) || TOM_DISABLE_RANDOM)

	//defines - DEBUG VISUALIZATION
#define VISUALIZE_LEVEL			2		//set visualization depth
#define VISUALIZE_LEVEL_UCT		((1 >= VISUALIZE_LEVEL) && TOM_DEBUG)

#define VISUALIZE_UCT_GETC_AFTER_MOVE	(0 && VISUALIZE_LEVEL_UCT)
#define VISUALIZE_UCT_ACTIONS_TREE		(0 && VISUALIZE_LEVEL_UCT)
#define VISUALIZE_UCT_ACTIONS_PLAYOUT	(0 && VISUALIZE_LEVEL_UCT)

#define DEBUG_ROOT_CHILDREN_VALUES	(0 && TOM_DEBUG)
#define DEBUG_TRACE_SELECTED_NODE	0 //(0 && TOM_DEBUG)
#define DEBUG_TREE_EXPANSION		(0 && TOM_DEBUG)
#define DEBUG_TREE_EXPANSION_SIM	0 //(0 && TOM_DEBUG)
#define DEBUG_SIMULATED_GAMES_OUT	(0 && TOM_DEBUG)

#define DEBUG_DISABLE_RANDOM_MULTIPLE_BEST	0
#define DEBUG_DISABLE_RANDOM_EXPAND		0

	// -- END of user defines section -- //

	// -- auto-defines -- //
#if(PARAM_FUNC_APP_TYPE < 2)
#define FUNC_APPROX_NUM_PARAMS		FUNC_APPROX_NUM_INPUTS
#elif(PARAM_FUNC_APP_TYPE == 2)
#define FUNC_APPROX_NUM_PARAMS		(FUNC_APPROX_NUM_INPUTS+1)*FUNC_APPROX_NUM_OUTPUTS
#elif(PARAM_FUNC_APP_TYPE == 3)
#define FUNC_APPROX_NUM_PARAMS		(FUNC_APPROX_HIDD_LAYER*(FUNC_APPROX_NUM_INPUTS+1) + FUNC_APPROX_NUM_OUTPUTS*(FUNC_APPROX_HIDD_LAYER+1))
#endif

	//history of rewards in visited states in the last episode
	typedef struct trajectoryRecord {
		int action;					// chosen action (bound to game)
		HashTree::TreeNode* state;	// chosen state
		double reward;				// reward received when transiting to new state
		REWARD_GOALS goal;			// what was the goal of that move (to maximize or minimize the reward)
		double bestActionValue;		// needed for off-policy control: value of best action
		int exploratoryAction;		// needed for off-policy control: flag whether the move was exploratory (set by the Control Policy)
		double stateVisitsTotal;	// number of total visits of this state so far

		//statics
		static const char * const trajectoryRecordLabels[];
		static const char * const trajectoryRecordFormat[];
	};

	//public procedures
	Player_AI_RL(Game_Engine* game = NULL, int player_number = TOMPLAYER_PLAYER_NUMBER);
	virtual ~Player_AI_RL();
	virtual void Initialize();
	virtual void Reset();
	virtual void New_Game();
	virtual int  Get_Move();
	//void Before_Move(int move);
	//void End_Game();

	//public procedures - debug and visualization	
	virtual void Output_Log_Level_Create_Headers();

	//configuration variables
	PRESET_ALGORITHMS					config_preset_algorithm;
	CONTROL_POLICIES					config_control_policy;
	POLICY_EVALUATION_TYPES				config_policy_evaluation;
	TD_UPDATE_TYPES						config_TDupdateType;
	Q_TRACE_TYPES						config_trace_type;
	Q_TRACE_RESET_TYPES					config_trace_exploratory_reset;
	Game_Engine::TRANSPOSITION_TYPES	config_transpositions;

	bool				config_offpolicy_backup_recheck_best;
	
	int					config_nonEpisodicTasks_updateInterval;
	int					config_num_new_nodes_per_episode;

	ROLLOUT_ASSUMPTIONS	config_rollout_assumption;

	UPDATESTEP_ALPHA_TYPES			config_alpha_type;

	UCB_VISIT_TYPES					config_ucb_visit_type;
	UCB_NORMALIZATION_TYPES			config_ucb_norm_type;
	UCB_NORMALIZATION_GLOBAL_TYPES	config_ucb_norm_global;
	UCB_NORMALIZATION_LOCAL_TYPES	config_ucb_norm_local;

	OPPONENT_ALIGNMENTS config_opponent_alignment;
	OPPONENT_POLICIES	config_opponent_policy;

	double par_egreedy_e;
	double par_ucb_c;

	double par_task_gamma;
	double par_td_alpha;
	double par_td_lambda;
	double par_td_initVal;

	int par_num_episodes;					//number of simulated episodes per Get_Move() call (computational budget)
	int par_num_simulatedActions_perMove;	//the number of allowed actions per getMove() call (summed across all episodes), if no limit is needed then set value on -1
	int par_simulated_horizon_lenght;		//the horizon length - this is the number of allowed actions per simulated episode, if no limit is needed then set value on -1
	
	double config_memory_limitMB;	//ammount of available memory (memory budget) in MB


	//public variables - tabular value function
	HashTree* memory;
	trajectoryRecord* trajectory;
	int trajectory_length;		//length of the current trajectory
	int trajectory_maxLength;	//maximum length of a trajectory (usually defined by the maximum length of an episodic task/game)
	int exploratory_move_trace_cutOff;	//needed for backups when using offpolicy learning with eligibility traces

	//current state variables
	HashTree::TreeNode* internalGameActiveNode;	//the active starting state (node) for each simulation - the root node for each episode
	int		numEpisodes_lastMove;				//number of computed episodes in last external move (last batch)
	int		numEpisodes_total;					//number of all computed episodes (also over all external game steps) (since reset())
	int		numSimulatedActions_lastEpisode;	//number of simulated actions in last episode
	int		numSimulatedActions_lastMove;		//number of simulated actions in last getMove() call
	int		numSimulatedActions_total;			//number of all simulated actions, number of calls to simulatedGame->Play_Move()
	int		numNewStates_lastEpisode;			//number of memorized new states in last episode (needed to replicate MCTS behaviour)
	int		numVisitedKnownStates_lastEpisode;	//number of visited nodes in the last episode that were already known from previous episodes
	double	sumSimulatedRewards_lastEpisode;	//cumulative sum of rewards in last episode
	double	sumSimulatedRewards_lastMove;		//cumulative sum of rewards in last external move
	double	sumSimulatedRewards_total;			//cumulative sum of rewards in total (since reset())

	double	maximumKnownReturn;		//highest known return (may be equal to observed, or extracted from game description), is not discounted with par_gamma
	double	minimumKnownReturn;		// lowest known return (may be equal to observed, or extracted from game description), is not discounted with par_gamma
	double	maximumObservedReturn;	//highest recorded (encountered) return so far, is not discounted with par_gamma
	double	minimumObservedReturn;	// lowest recorded (encountered) return so far, is not discounted with par_gamma

	//public variables - runtime and optimization settings
	bool	internal_game_force_copy;

	////public variables - UCT learning parameters
	//int		UCT_param_SimPerIter;				//number of simulations per iteration

	//public variables - function approximation parameters
	Tom_Function_Approximator* Func_App_UCT_Params;
	int Func_App_UCT_num_params;

	////public variables - current state
	//int UCT_num_plys;
	//int MCTS_current_simuNum;
	//int MCTS_num_all_simulations;

	//public vairables - debug and visualization settings

	int config_output_depth;

	int	config_output_simGameState;
	int	config_output_trajectory;
	int	config_output_memory;
	int	config_output_summary;
	int	config_output_currentInfo;
	int	config_output_TDbackup;

	int config_output_pause;

	int config_output_memory_treeDepth;
	//int  output_type;
	//double	debug_dbl_cnt1, debug_dbl_cnt2;
	//int	 output_level_headers_created;

	//statics
	static const char * const settingsLabels[];
	static const char * const settingsFormat[];

protected:

	//private protected procedures
	virtual void Init_Settings();
	virtual void Allocate_Memory();
	virtual void Clear_Memory();
	virtual void New_Game2();

	virtual void Apply_Preset_Config(PRESET_ALGORITHMS preset);	//set parameters by the selected preset - overrides certain settings, depending on which preset was selected

	//RL procedures
	virtual int			RL_Algorithm();
	virtual bool		RL_Single_Episode();

	virtual std::tuple<int, int, int, double, double, REWARD_GOALS>	RL_Control_Policy(Game_Engine* localGame, HashTree::TreeNode* currentState, CONTROL_POLICIES policy, REWARD_GOALS rewardGoal);
	virtual std::tuple<int, int, int, double, double, REWARD_GOALS>	RL_Opponent_Model(Game_Engine* localGame, HashTree::TreeNode* currentState);
	virtual std::tuple<double, int, int>							RL_Perform_Action(Game_Engine* localGame, int actionID);

	virtual void				Update_Memory_After_External_Change(int number_actions);
	virtual HashTree::TreeNode*	MemorizeNextState(Game_Engine* localGame, HashTree::TreeNode* previousState, int hashKey, int selected_child_index);
	virtual void				MarkStateVisit(HashTree::TreeNode* visitedNode);
	virtual void				AddTrajectoryEntry(int action, HashTree::TreeNode* state, double reward, REWARD_GOALS rewardGoal, double onPolicyChildValue, double bestActionValue);
	
	virtual void				HandleEpisodeStep();
	virtual void				HandleEpisodeEnd();

	virtual void				UpdateTrajectoryOfflineValues();
	virtual void				UpdateTrajectoryBounds();
	virtual void				UpdateKnownReturnBounds(double lastReturn);

	virtual HashTree::TreeNode* AddNode(Game_Engine* localGame, int hashKey, HashTree::TreeNode* parent, int child_seq_index);
	virtual void				ResetNode(HashTree::TreeNode* newNode);

	virtual std::tuple<int, int, int, double, double>	RL_Control_Egreedy(Game_Engine* localGame, HashTree::TreeNode* currentState, double par_epsilon, REWARD_GOALS goal);
	virtual std::tuple<int, int, int, double, double>	RL_Control_UCB(Game_Engine* localGame, HashTree::TreeNode* currentState, double par_C, REWARD_GOALS goal);
	virtual void		RL_TDofflineBackup();
	virtual void		RL_TDsingleBackup(int trajectory_index, double gamma, double alpha, double lambda, char* printLinePrefix = NULL);
	virtual double		RL_GetAssumedStateValue(HashTree::TreeNode* node);
	virtual double		RL_GetBestActionValue(HashTree::TreeNode* node, REWARD_GOALS goal);


	//support procedures
	virtual double		Neural_Network_Threshold_Function(double input_weight_sum, const int function_type = FUNC_APPROX_NEURAL_FUNC);

	//private protected procedures - visualization and debug
	virtual void		Output_Settings();
	
	virtual void		Output_ExternalMove_Level();
	virtual void		Output_Episode_Level();
	virtual void		Output_SimulatedMove_Level();

	virtual void		Output_Batch(int depth);
	virtual void		Output_Current_Info(char* printLinePrefix = NULL);
	virtual void		Output_Summary(char* printLinePrefix = NULL);
	virtual void		Output_Memory(char* printLinePrefix = NULL);
	virtual void		Output_Trajectory(char* printLinePrefix = NULL);

	virtual void		Output_TDbackup1(int trajectory_index, double TDerror, double reward, double nextStateVal, double stateVal, int exploratory_move_trace_reset, char* printLinePrefix);
	virtual void		Output_TDbackup21(int b, int trajectory_index, double trace, HashTree::TreeNode* backupNode, char* printLinePrefix);
	virtual void		Output_TDbackup22(int b, HashTree::TreeNode* backupNode, double alpha, char* printLinePrefix);

	////private protected variables
	////double* actionsWeight;
	////int* actionsNumWin;
	////int* actionsNumSel;
	////bool* actionsPlayed;
	//int all_actions_num;

	//private protected variables
	Game_Engine* internalGame;
	Game_Engine* simulatedGame;

	////feedback information from simulations
	//UCTnode*	UCT_selected_leaf;
	//Game_Engine* simulatedGame_startingState;
	//int			sim_feedback_num_sims;		//should this be long long ?
	//double*		sim_feedback_scores_avg;
	//double*		sim_feedback_scores_var;
	//double**	sim_feedback_scores;
	//double		sim_feedback_plys_avg;
	//double		sim_feedback_plys_var;REWARD_GOALS
	//double*		sim_feedback_plys;

	//private protected variables - debug and visualization
	int outInfoCounter;
	
		
		//stringstream visualizeActionsTree;
	//stringstream visualizeActionsPlayout;

	int		dbgTmpInt1;
	double	dbgTmpInt2;

public:
	//logging by levels output format
#define TOMPLAYER_AI_RL_output_log_level5_header \
	"L-/game->experiment_repeat_index \t" \
	"L0/game->batch_repeat_index \t" \
	"L1/game->game_repeat_index \t" \
	"L2/game->current_plys \t" \
	"L3/player->current_episode \t" \
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

#define TOMPLAYER_AI_RL_output_log_level5_format \
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

};

#endif