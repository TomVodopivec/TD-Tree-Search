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
#include "..\tools\Tool_Sample_Storage.hpp"

//external global variables
extern MultiPrinter * gmp;	//multiprinter object defined in main.hpp
extern int experiment_settings_id;

/**
The general reinforcement learning player
*/
class Player_AI_RL : public Player_Engine
{

public:

  // -- MAST added 2017-02-28
  // by default disabled (config_MASTenable == 0)
  // works only with the UCB policy! (not implemented for others yet)
  // works only for returns in range [0,1]!
  // also, the implementation is poor so the time-complexity is very high (slows down the algorithm 10 fold)
  // config_MASTenable=3 works only with on-policy control, without transpositions, with offline batch backups, and with ROLLOUT_VALUE_ASSUMPTIONS set to one of EQUAL_... options

  int config_MASTenable;
    // 0 - disabled
    // 1 - use in control policy (both tree and playout)
    // 2 - use only for Vplayout value estimation
    // 3 - use both in control and for Vplayout
  double config_MAST_paramT;  // uniform random default (does not use MAST in playout)

  double* MAST_rewards;
  double* MAST_visits;
  double* MAST_prob;
  int* MAST_list;

  int all_actions_num;

  // -- MAST end



  // ---- class global constants ---- //
// WARNING: DO NOT CHANGE THE ORDERING OF ELEMENTES IN INDIVIDUAL ENUMS (the labels will get messed up)

// WARNING: presets override some other configuration settings
  struct PRESET_ALGORITHMS{
    enum TYPE {
      NONE,							// No preset used: all configuration options apply (none is overriden)
      FIRSTVISIT_MC_ONPOLICY,			// First-visit on-policy Monte Carlo control: equals to offline replacing-traces TD(1) with alpha = (1/visits), and equals to MCTS
      EVERYVISIT_MC_ONPOLICY,			// Every-visit on-policy Monte Carlo control
      FIRSTVISIT_EPISODIC_ALPHA_MC,	// Batch (by episodes) first-visit arbitrary-step-rate-alpha Monte Carlo
      ONLINE_TD_ZERO_ONPOLICY,		// Online on-policy TD(0), SARSA(0)	
      EPISODIC_TD_ZERO_ONPOLICY,		// Batch (by episodes) on-policy TD(0), SARSA(0)	
      TD_LAMBDA,						// General TD(lambda), SARSA(lambda)
      ONLINE_WATKINS_Q,				// Watkin's Q(lambda), with online updates
      ONLINE_NAIVE_Q,					// Naive Q(lambda), a Watkin's Q-learning variant that does not zero eligibility traces for exploratory actions, with online updates
      PENGS_Q,						// -- NOT IMPLEMENTED YET -- Peng's Q(lambda), a Q-learning variant that does not zero traces for all exploratory actions -> a merge between Watkin's Q(lambda) and SARSA(lambda)
      MCTS_UCT,						// Upper Confidence Bounds applied to Trees, the most popular Monte Carlo Tree Search algorithm
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const PRESET_ALGORITHMS::TYPE DEFAULT_PRESET_ALGORITHM = PRESET_ALGORITHMS::NONE;

  struct CONTROL_POLICIES{
    enum TYPE {
      EGREEDY,
      UCB1,
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
    static const char * stringLabels2char[ENUM_COUNT_ELEMENTS];
  };
  static const CONTROL_POLICIES::TYPE DEFAULT_CONTROL_POLICY = CONTROL_POLICIES::EGREEDY;

  struct POLICY_EVALUATIONS{
    enum TYPE {
      EPISODIC_MC,					// the constant-alpha Monte Carlo update rule
      TDLAMBDA_ONPOLICY,				// the general onpolicy TD(lambda) evaluation policy -> produces the SARSA(lambda) algorithm
      TDLAMBDA_OFFPOLICY_Q_LEARNING,	// Watkin's or Naive Q(lambda) algorithm
      //TDLAMBDA_OFFPOLICY_PENGS_Q,	// -- NOT IMPLEMENTED YET -- 
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const POLICY_EVALUATIONS::TYPE DEFAULT_POLICY_EVALUATION = POLICY_EVALUATIONS::TDLAMBDA_ONPOLICY;

  struct TD_UPDATES{
    enum TYPE {
      ONLINE,					// update after each step, default for TD methods, equals to batch updates if transpositions are not used (it is useless if state-actions are not revisited multiple times in the same episode)
      BATCH_EPISODIC,			// update after end of each episode (batch update), default for MC methods (also MCTS). Temporary stores changes to values while backuping and after all backups it updates the actual values.
      BATCH_EPISODIC_INPLACE,	// a variant of episodic update that updates the actual values inplace (it does not temporary store the value changes)
      //BATCH_EPISODIC_ASYNC,	// asynchronous from-end-to-start episodic update that is less computationally heavy (iterates only once through the trajectory, O(n) instead of O(n*n)) -- TODO: is this even possible when using transpositions and replacing traces? (because one must not update the same state more than once)
      //BATCH_STEPS,			// todo, same as episodic, just that now the update is carried on after a certain ammount of steps (needed for non-episodic tasks)
      //BATCH_STEPS_INPLACE,	// todo
      //BATCH_STEPS_ASYNC,	//todo
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const TD_UPDATES::TYPE DEFAULT_TD_UPDATE = TD_UPDATES::BATCH_EPISODIC;

  struct ELIGIBILITY_TRACES{	// if transposistions are not used, then all options are equal
    enum TYPE {
      REPLACING,			// usually performs better, used to produce first-visit MC
      ACCUMULATING,		// used to produce every-visit MC -> not good, tends to diverge (nodes get infinite values)
      //ACTIONEXCLUSIVE	-> NOT YET IMPLEMENTED
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const ELIGIBILITY_TRACES::TYPE DEFAULT_ELIGIBILITY_TRACES = ELIGIBILITY_TRACES::REPLACING;

  struct ELIGIBILITY_EXPLORATORY_RESET{
    enum TYPE {
      DISABLED,
      ENABLED,
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const ELIGIBILITY_EXPLORATORY_RESET::TYPE DEFAULT_ELIGIBILITY_EXPLORATORY_RESET = ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

  static const Game_Engine::TRANSPOSITIONS::TYPE DEFAULT_TRANSPOSITIONS = (Game_Engine::TRANSPOSITIONS::DISABLED);
  // DISABLED,		// if states cannot be distinguished or state-space is too large, then a search tree is grown (default for UCT)
  // STATES,			// evaluate states V(s) <- TD
  // STATEACTIONS		// evaluate state-actions Q(s,a) <- SARSA / Q-learning

  static const int DEFAULT_OFFPOLICY_BACKUP_RECHECK_BEST = 0;		// 1 or 0: Recheck best child value when backuping (increases computational burden). Applies only to offpolicy learning and makes a difference only when using transpositions with offline inplace backups, or when using async backups.

  static const int DEFAULT_NUM_NEW_NODES_PER_EPISODE = 1;
  // -1 - memorize all (default for RL methods)
  //  0 - no memorization (produces random algorithms)
  //  1 - UCT's default setting
  // >1 - arbitrary positive integer value allowed

  struct ROLLOUT_VALUE_ASSUMPTIONS{	// what is the assumed value of non-memorized nodes (as MCTS is using in the rollout phase)
    enum TYPE {
      EQUAL_INITIAL,					// the default initial value (par_td_initVal)
      EQUAL_ZERO,						// a value of 0.0 (no TDerrors due to bootstrapping in the playout phase)
      EQUAL_LAST_MEMORIZED,			// the value of the last memorized node (leaf in the tree)
      CONVERGED_TO_NEXT_MEMORIZED,	// values optimally converged to first next encountered memorized value or to the terminal state (episode end), also considering the received reward (no TDerrors due to bootstrapping in the playout phase)
      CONVERGED_TO_LAST_MEMORIZED,	// values optimally converged to last memorized value (no TDerrors due to bootstrapping in the playout phase)
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
    static const char * stringLabels2char[ENUM_COUNT_ELEMENTS];
  };
  static const ROLLOUT_VALUE_ASSUMPTIONS::TYPE DEFAULT_ROLLOUT_VALUE_ASSUMPTION = ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
  
  struct UPDATESTEP_ALPHA{
    enum TYPE {
      CONSTANT,		// constant update step (alpha value (set by parameters par_td_alpha)
      MONTE_CARLO,	// calculating the statistical mean: alpha is computed at each update for each node by (1/visit_counter) -> exponential by visited episodes
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const UPDATESTEP_ALPHA::TYPE DEFAULT_UPDATESTEP_ALPHA = UPDATESTEP_ALPHA::MONTE_CARLO;

  struct UCB_VISITS{		// if transposistions are not used, then both options are equal
    enum TYPE {
      TOTAL,		// consider the total number of visits of a state (or state-action) - use the counter that updates after each actual visit
      EPISODES,	// consider the number of terminal updates the state received (the number of episodes that visited that state) - use the counter that updates once per episode
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const UCB_VISITS::TYPE DEFAULT_UCB_VISITS = UCB_VISITS::TOTAL;
  struct UCB_NORMALIZATION_LOCALITY{
    enum TYPE {
      GLOBAL,				// use global Q-value normalization bounds, assume whole state-space has same bounds (it is not discount with gamma, so it might not be a good choice for discounting tasks)
      LOCAL,				// use local (current state) normalization bounds, assume bounds may differ across the state-space
      LOCAL_THEN_GLOBAL,	// use global bounds if local are not yet valid (not yet known or not initialized)
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  const UCB_NORMALIZATION_LOCALITY::TYPE DEFAULT_UCB_NORMALIZATION_LOCALITY = UCB_NORMALIZATION_LOCALITY::GLOBAL;
  struct UCB_GLOBAL_NORMALIZATIONS{
    enum TYPE {
      KNOWN_RETURN,		// use the known min/max return (sum of rewards) per episode (the bounds get initialized apriori if the problem/game definition reveals this information)
      OBSERVED_RETURN,	// use the observed min/max return (sum of rewards) per episode
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const UCB_GLOBAL_NORMALIZATIONS::TYPE DEFAULT_UCB_GLOBAL_NORMALIZATION = UCB_GLOBAL_NORMALIZATIONS::KNOWN_RETURN;
  struct UCB_LOCAL_NORMALIZATIONS{
    enum TYPE {
      OBSERVED_RETURN,		// use current state's known min/max return
      BRANCH_CURRENT_QVAL,	// use current branch's min/max Q-value
      CHILDREN_CURRENT_QVAL,	// use current state's min/max Q-value
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const UCB_LOCAL_NORMALIZATIONS::TYPE DEFAULT_UCB_LOCAL_NORMALIZATION = UCB_LOCAL_NORMALIZATIONS::BRANCH_CURRENT_QVAL;

  // the number of steps between updates for non-episodic tasks (if updates are not online)
  static const int DEFAULT_NONEPISODICTASKS_UPDATEINTERVAL = 100;

  // number of steps for the exploratory-weight linear decrease to zero (by different levels)
  static const int DEFAULT_EXPLORATION_LINEARZERO_EXTERNALMOVES = 0;
  static const int DEFAULT_EXPLORATION_LINEARZERO_EPISODES = 0;
  static const int DEFAULT_EXPLORATION_LINEARZERO_SIMULATEDMOVES = 0;

  static const double DEFAULT_PAR_EPSILON;
  static const double DEFAULT_PAR_UCB_C;

  // reinforcement learning parameters
  static const double DEFAULT_PAR_TASK_GAMMA;
  static const double DEFAULT_PAR_TD_ALPHA;
  static const double DEFAULT_PAR_TD_LAMBDA;
  static const double DEFAULT_PAR_TD_INITVAL;

  // MCTS (planning) parameters
  static const int DEFAULT_NUM_EPISODES_PER_MOVE = 10000;		//computational resource limit: number of episodes per external move, set on -1 for no limit
  static const int DEFAULT_SIMULATEDACTIONS_PER_MOVE = -1;		//computational resource limit: number of simulated actions per external move, set on -1 for no limit
  static const int DEFAULT_SIMULATED_HORIZON_LENGTH = -1;		//horizon length for simulated episodes (number of actions per episode), set -1 for no limit

  struct OPPONENT_ALIGNMENTS{
    enum TYPE {
      ADVERSARY,		// produces MinMax search
      COOPERATIVE,
      //INDEPENDENT	// implementation not ready yet: should have it's own data tree structures for rewards (a vector of rewards by players for each node)
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const OPPONENT_ALIGNMENTS::TYPE DEFAULT_OPPONENT_ALIGNMENT = OPPONENT_ALIGNMENTS::ADVERSARY;

  struct OPPONENT_POLICIES{
    enum TYPE {
      RANDOM,
      GREEDY,
      SELFPLAY,		// selfplay: uses same policy as the learning agent
      //HANDSET		// not done yet: must be implemented for each game individually
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const OPPONENT_POLICIES::TYPE DEFAULT_OPPONENT_POLICY = OPPONENT_POLICIES::SELFPLAY;

  struct REWARD_GOALS{
    enum TYPE {
      MAXIMIZE,
      MINIMIZE,
      UNKNOWN,	// to mark other player's actions whose purpose was unknown (used for opponent's move on external game)
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };

  struct NUMERCIAL_CORRECTIONS{
    enum TYPE {
      DISABLED,
      ENABLED,
      ENABLED_WITH_WARNINGS,
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const NUMERCIAL_CORRECTIONS::TYPE DEFAULT_NUMERICAL_CORRECTION = NUMERCIAL_CORRECTIONS::DISABLED;

  static const double EPSILON_TIEBRAKER;
  static const double SMALLEST_TDERROR;
  static const double EPSILON_TRACE_CUTOFF;

  // MCTS tree and optimization parameters
  static const int DEFAULT_MEMORY_LIMIT_MB = 2048;	//in MegaBytes
  static const bool OPTIMIZATION_INTERNAL_FORCE_COPY = false;

  // VISUALIZATION

  static const int DEFAULT_OUTPUT_DEPTH = 2;	// the general switch to set the depth of output printing
  // 0 - disabled
  // 1 - after each external move
  // 2 - after each episode
  // 3 - after each simulated move

  //individual switches (printing depths for each individual visualization component, 0 - disabled)
  static const int DEFAULT_OUTPUT_TRAJECTORY_DEPTH = 2;		// last followed trajectory (suggested max 2)
  static const int DEFAULT_OUTPUT_MEMORY_DEPTH = 2;			// memorized structures (tree or hash table) (suggested max 2)
  static const int DEFAULT_OUTPUT_SUMMARY_DEPTH = 2;			// stats summary (suggested max 2)
  static const int DEFAULT_OUTPUT_CURRENTINFO_DEPTH = 0;		// current info (counters, root node value) (max 3)
  static const int DEFAULT_OUTPUT_SIMGAMESTATE_DEPTH = 0;	// current state/position of the simulated game (max 3)
                              
  static const int DEFAULT_OUTPUT_TDBACKUP_DEPTH = 2;		// TD backups, output_depth must be at least 2! (0 - disabled, 1 - print TD errors, 2 - output whole backups)

  static const int DEFAULT_OUTPUT_PAUSE_DEPTH = 0;			// pauses depth (waits for user to press key, 0 - disabled)

  //additional visualization settings
  static const int DEFAULT_OUTPUT_MEMORY_TREEDEPTH = 3;	// print depth of the memorzied tree (-1 - entire tree, 0 - root, 1 - root's children, ... )

  // EXPERIMENTAL SETTINGS
  struct EXPERIMENTAL_SETTINGS{	// IF YOU ADD NEW ENTRIES, BE SURE TO ADD NEW ENTRIES ALSO FOR experimentNumMetrics[] AND FOR experimentLabels[] AND FOR EXPERIMENTAL_SETTINGS::stringLabels[]
    // do not change the order
    enum TYPE {
      NONE,
      RW_RIGHTWIN_METRICS_PER_EPISODES,
      RW_RIGHTWIN_METRICS_PER_TIMESTEPS,
      TTT_METRICS_PER_TIMESTEPS,
      ENUM_COUNT_ELEMENTS	// must be last element in enum, do not remove: used to return the number of elements in enumerator
    };
    static const char * stringLabels[ENUM_COUNT_ELEMENTS];
  };
  static const EXPERIMENTAL_SETTINGS::TYPE DEFAULT_EXPERIMENTAL_SETTING = EXPERIMENTAL_SETTINGS::NONE;

  static const int DEFAULT_OUTPUT_WARNING_QBOUNDS = 1;	// output

  // ---- END OF class global constants ---- //

  //history of rewards in visited states in the last episode
  typedef struct trajectoryRecord {
    int action;					// chosen action (bound to game)
    HashTree::TreeNode* state;	// chosen state
    double reward;				// reward received when transiting to new state
    REWARD_GOALS::TYPE goal;	// what was the goal of that move (to maximize or minimize the reward)
    double bestActionValue;		// needed for off-policy control: value of best action
    int exploratoryAction;		// needed for off-policy control: flag whether the move was exploratory (set by the Control Policy)
    double stateVisitsTotal;	// number of total visits of this state so far

    //statics
    static const int structNumElements = 7;
    static const char * trajectoryRecordLabels[structNumElements];
    static const char * trajectoryRecordFormat[structNumElements];
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
  virtual void Output_Settings();

  //configuration variables
  PRESET_ALGORITHMS::TYPE				config_preset_algorithm;
  CONTROL_POLICIES::TYPE				config_control_policy;
  POLICY_EVALUATIONS::TYPE			config_policy_evaluation;
  TD_UPDATES::TYPE					config_TDupdateType;
  ELIGIBILITY_TRACES::TYPE			config_trace_type;
  ELIGIBILITY_EXPLORATORY_RESET::TYPE	config_trace_exploratory_reset;
  Game_Engine::TRANSPOSITIONS::TYPE	config_transpositions;

  int							config_offpolicy_backup_recheck_best;
  
  int							config_nonEpisodicTasks_updateInterval;
  int							config_num_new_nodes_per_episode;

  ROLLOUT_VALUE_ASSUMPTIONS::TYPE		config_rollout_assumption;

  UPDATESTEP_ALPHA::TYPE				config_alpha_type;

  UCB_VISITS::TYPE					config_ucb_visit_type;
  UCB_NORMALIZATION_LOCALITY::TYPE	config_ucb_norm_type;
  UCB_GLOBAL_NORMALIZATIONS::TYPE		config_ucb_norm_global;
  UCB_LOCAL_NORMALIZATIONS::TYPE		config_ucb_norm_local;

  OPPONENT_ALIGNMENTS::TYPE	config_opponent_alignment;
  OPPONENT_POLICIES::TYPE		config_opponent_policy;

  int		config_ExplorationLinear_maxExtMoves;
  int		config_ExplorationLinear_maxEpisodes;
  int		config_ExplorationLinear_maxActions;

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

  NUMERCIAL_CORRECTIONS::TYPE	config_numerical_correction;

  //public variables - tabular value function
  HashTree* memory;

  trajectoryRecord* trajectory;
  int trajectory_length;		//length of the current trajectory
  int trajectory_maxLength;	//maximum length of a trajectory (usually defined by the maximum length of an episodic task/game)
  
  int exploratory_move_trace_cutOff, exploratory_move_trace_cutOff_new;		//needed for backups when using offpolicy learning with eligibility traces
  int lastMetMemorizedState_trajIndex;	//needed for ROLLOUT_VALUE_ASSUMPTIONS::LAST_MEMORIZED
  int nextPendingBackup_trajIndex;		//needed for ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_REWA
  double lastAssumedValue;				//needed for ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LEAF

  //HashTree::TreeNode* lastMetMemorizedState;	

  //current state variables
  HashTree::TreeNode* internalGameActiveNode;	//the active starting state (node) for each simulation - the root node for each episode
  int		numExternalMoves_all;				//number of all external moves (including all agent's moves)
  int		numExternalMoves_own;				//number of own external moves (how many times this agent effectuated an output move)
  int		numEpisodes_lastMove;				//number of computed episodes in last external move (last batch)
  int		numEpisodes_total;					//number of all computed episodes (also over all external game steps) (since reset())
  int		numSimulatedActions_previousEpisode;//number of simulated actions in the previous episode (gets updated at each episode termination)
  int		numSimulatedActions_lastEpisode;	//number of simulated actions in last episode
  int		numSimulatedActions_lastMove;		//number of simulated actions in last getMove() call
  int		numSimulatedActions_total;			//number of all simulated actions, number of calls to simulatedGame->Play_Move()
  int		numNewStates_lastEpisode;			//number of memorized new states in last episode (needed to replicate MCTS behaviour)
  int		numVisitedKnownStates_lastEpisode;	//number of visited nodes in the last episode that were already known from previous episodes
  double	sumSimulatedRewards_lastEpisode;	//cumulative sum of rewards (return) in last episode
  double	sumSimulatedRewards_lastMove;		//cumulative sum of rewards in last external move
  double	sumSimulatedRewards_total;			//cumulative sum of rewards in total (since reset())

  double	maximumKnownReturn;		//highest known return (may be equal to observed, or extracted from game description), is not discounted with par_gamma
  double	minimumKnownReturn;		// lowest known return (may be equal to observed, or extracted from game description), is not discounted with par_gamma
  double	maximumObservedReturn;	//highest recorded (encountered) return so far, is not discounted with par_gamma
  double	minimumObservedReturn;	// lowest recorded (encountered) return so far, is not discounted with par_gamma

  double	computed_explorationWeight;		//last value used for exploration-weight
  //public variables - runtime and optimization settings
  bool	internal_game_force_copy;

  ////public variables - function approximation parameters
  //Tom_Function_Approximator* Func_App_UCT_Params;
  //int Func_App_UCT_num_params;

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

  //public vairables - warnings' switches
  int config_outputWarning_Qbounds;

  //public variables - experimental settings and memory storage pointers
  EXPERIMENTAL_SETTINGS::TYPE config_experiment;	// externally selected experimental setting
  Tool_Sample_Storage*** experiment_results;	// externally allocated 2d array of pointers to objects Tool_Sample_Storage to store results
  double* experiment_timers;					// array of times (usually contains externally defined starting times)

  //statics
  static const char * settingsLabels[];
  static const char * settingsFormat[];
  static const int	experimentNumMetrics[EXPERIMENTAL_SETTINGS::ENUM_COUNT_ELEMENTS];
  static const char * experimentLabels[EXPERIMENTAL_SETTINGS::ENUM_COUNT_ELEMENTS][20];
  
  static char * labelsPresetAlgorithms[];


protected:

  //private protected procedures
  virtual void Init_Settings();
  virtual void Allocate_Memory();
  virtual void Clear_Memory();
  virtual void New_Game2();

  virtual void Apply_Preset_Config(PRESET_ALGORITHMS::TYPE preset);	//set parameters by the selected preset - overrides certain settings, depending on which preset was selected

  //RL procedures
  virtual int			SingleExternalMove();
  virtual bool		SingleEpisode();

  virtual std::tuple<int, int, int, double, double, REWARD_GOALS::TYPE>	RL_Control_Policy(Game_Engine* localGame, HashTree::TreeNode* currentState, CONTROL_POLICIES::TYPE policy, REWARD_GOALS::TYPE rewardGoal);
  virtual std::tuple<int, int, int, double, double, REWARD_GOALS::TYPE>	RL_Opponent_Model(Game_Engine* localGame, HashTree::TreeNode* currentState);
  virtual std::tuple<double, int, int>							RL_Perform_Action(Game_Engine* localGame, int actionID);

  virtual void				Update_Memory_After_External_Change(int number_actions);
  virtual HashTree::TreeNode*	MemorizeNextState(Game_Engine* localGame, HashTree::TreeNode* previousState, int hashKey, int selected_child_index);
  virtual void				MarkStateVisit(HashTree::TreeNode* visitedNode);
  virtual void				AddTrajectoryEntry(int action, HashTree::TreeNode* state, double reward, REWARD_GOALS::TYPE rewardGoal, double onPolicyChildValue, double bestActionValue);
  
  virtual void				HandleEpisodeStep();
  virtual void				HandleEpisodeEnd();

  virtual void				UpdateTrajectoryOfflineValues();
  virtual void				UpdateTrajectoryBounds();
  virtual void				UpdateKnownReturnBounds(double lastReturn);

  virtual HashTree::TreeNode* AddNode(Game_Engine* localGame, int hashKey, HashTree::TreeNode* parent, int child_seq_index, double initialValue);
  virtual void				ResetNode(HashTree::TreeNode* newNode, double initialValue);

  virtual std::tuple<int, int, int, double, double>	RL_Control_Egreedy(Game_Engine* localGame, HashTree::TreeNode* currentState, double par_epsilon, REWARD_GOALS::TYPE goal);
  virtual std::tuple<int, int, int, double, double>	RL_Control_UCB(Game_Engine* localGame, HashTree::TreeNode* currentState, double par_C, REWARD_GOALS::TYPE goal);
  virtual void		RLofflineBackup();
  virtual void		RLsingleBackup(int trajectory_index, char* printLinePrefix = NULL);
  
  virtual double		GetTDerror(int trajectory_index, char* printLinePrefix = NULL);
  virtual void		BackupTDerror(double TDerror, int trajectory_index, char* printLinePrefix = NULL);

  virtual void		EpisodicMCsingleBackup(int trajectory_index, char* printLinePrefix = NULL);

  virtual double		GetRolloutAssumedValue(int trajectory_index);
  virtual double		GetStateBestActionValue(HashTree::TreeNode* node, REWARD_GOALS::TYPE goal);

  virtual double		NumericalErrorCorrection(double value);

  //protected procedures - visualization and debug
  virtual void		Output_ExternalMove_Start();
  virtual void		Output_Episode_Start();
  virtual void		Output_SimulatedMove_Start();
  virtual void		Output_ExternalMove_End();
  virtual void		Output_Episode_End();
  virtual void		Output_SimulatedMove_End();

  virtual void		Output_Batch(int depth);
  virtual void		Output_Current_Info(char* printLinePrefix = NULL);
  virtual void		Output_Summary(char* printLinePrefix = NULL);
  virtual void		Output_Memory(char* printLinePrefix = NULL);
  virtual void		Output_Trajectory(char* printLinePrefix = NULL);

  virtual void		Output_TDbackup1(int trajectory_index, double TDerror, double nextStateVal, double stateVal, int exploratory_move_trace_reset, char* printLinePrefix);
  virtual void		Output_TDbackup21(int b, int trajectory_index, double trace, HashTree::TreeNode* backupNode, char* printLinePrefix);
  virtual void		Output_TDbackup22(int b, HashTree::TreeNode* backupNode, double alpha, char* printLinePrefix);

  //protected procedures - experiments
  virtual void		Experiment_EpisodeMetrics(int depth);
  virtual void		Experiment_TimeStepMetrics(int depth);

  ////private protected variables
  ////double* actionsWeight;
  ////int* actionsNumWin;
  ////int* actionsNumSel;
  ////bool* actionsPlayed;
  //int all_actions_num;

  //private protected variables
  Game_Engine* internalGame;
  Game_Engine* simulatedGame;
  int numerical_correction_possible;

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