//include header
#include "Player_AI_UCT_MAST.hpp"

/**
Constructor for AI UCT player module calling general game player constructor

@param game Pointer to a Game_Engine object (or derivated class)
*/
Player_AI_UCT_MAST::Player_AI_UCT_MAST(Game_Engine* game, int player_number) : Player_Engine(game, player_number)
{
  //-- <- marked all changed procedures like this, so I can later set inheritance to UCT_Player
  //player definition
  player_name = "UCT_MAST";

  //call initialization procedures
  if (game != NULL)
    Initialize();
  else
    is_initialized = false;
}

//destructor
Player_AI_UCT_MAST::~Player_AI_UCT_MAST(void)
{
  if (is_initialized) {
    Clear_Memory();
    is_initialized = false;
  }
}

//allocate memory and initialize variables
void Player_AI_UCT_MAST::Initialize()
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

void Player_AI_UCT_MAST::Init_Settings()
{
  //init internal variables
  all_actions_num = game->maximum_allowed_moves;
  UCTtree_maxMemorySize = (int)(TOMPlayer_AI_UCT_MAST_TREE_SIZE_LIMIT_GB * (1 << 30));
  UCTtree_num_nodes = 0;
  UCTtree_memorySize = 0;

  //init optimization settings
  internal_game_force_copy = TOMPlayer_AI_UCT_MAST_OPTIMIZATION_INTERNAL_FORCE_COPY;

  //init learning parameters
  UCT_param_C = TOMPlayer_AI_UCT_MAST_PARAM_C;
  UCT_param_IterNum = TOMPlayer_AI_UCT_MAST_PARAM_NUMBER_ITERATIONS;
  UCT_param_defaultPolicy_maxPlys = TOMPlayer_AI_UCT_MAST_PARAM_DEFAULT_MAX_PLAYS;
  UCTtree_preserve = TOMPlayer_AI_UCT_MAST_PARAM_PRESERVE_TREE;
  UCT_param_SimMoveNum = -1;

  MAST_paramT = 1000000.0;  // uniform random default

}

void Player_AI_UCT_MAST::Allocate_Memory()
{
  //--
  //allocate resources
  UCTroot = UCT_Tree_Node_Init(-1, NULL, true);
  UCTroot_memory = UCTroot;
  internalGame = game->Create_Duplicate_Game();
  simulatedGame = game->Create_Duplicate_Game();

  

  //array for MAST heuristic

  MAST_prob = new double[all_actions_num];
  MAST_list = new int[all_actions_num];
  MAST_flagPlayer = new int[game->maximum_plys];
  MAST_flagMove = new int[game->maximum_plys];
  MAST_rewards = new double*[2];
  MAST_rewards[0] = new double[all_actions_num];
  MAST_rewards[1] = new double[all_actions_num];
  MAST_visits = new double*[2];
  MAST_visits[0] = new double[all_actions_num];
  MAST_visits[1] = new double[all_actions_num];

}

void Player_AI_UCT_MAST::Clear_Memory()
{
  //--
  //clean up memory
  if (is_initialized) {
    if (UCTtree_preserve)
      UCT_Tree_Delete(UCTroot_memory);
    else
      UCT_Tree_Delete(UCTroot);

    delete(internalGame);
    delete(simulatedGame);
    delete(MAST_prob);
    delete(MAST_list);
    delete(MAST_flagPlayer);
    delete(MAST_flagMove);
    delete(MAST_visits[0]);
    delete(MAST_visits[1]);
    delete(MAST_visits);
    delete(MAST_rewards[0]);
    delete(MAST_rewards[1]);
    delete(MAST_rewards);
  }
}

void Player_AI_UCT_MAST::New_Game2()
{

  //RESET internal game copy
  internalGame->Copy_Game_State_From(game);

  //null history-storing variables
  lastAction_node = NULL;
  numIterations_total = 0;
}

//public procedure: reset player (reset all learning values)
void Player_AI_UCT_MAST::Reset()
{

  //delete/free entire tree except root
  UCT_Tree_Reset();

  //reset root
  UCTroot->parent = NULL;
  UCT_Tree_Node_Reset(UCTroot);

  return New_Game2();
}

//public procedure: signal player that new game has been started
void Player_AI_UCT_MAST::New_Game()
{

  //reset root (and reset tree, optionally)
  if (UCTtree_preserve) {
    UCTroot = UCTroot_memory;
    New_Game2();
  }
  else {
    Reset();		//calls reset1(), newGame(), newGame1()
  }

}

//public procedure: returns players next selected move
int Player_AI_UCT_MAST::Get_Move()
{

  //--
  int moveNumber;
  int number_internal_moves;

#if(TOMPlayer_AI_UCT_MAST_VISUALIZE_LEVEL_UCT)
  printf("\n");
  printf("======================================================= NEXT MOVE =======================================================\n");
  printf("======================================================= NEXT MOVE =======================================================\n");
  printf("\n");
  printf("PLY %d PLAYER %s\n", game->current_plys, player_name.c_str());
  printf("\n");
  printf("======================================================= NEXT MOVE =======================================================\n");
  printf("======================================================= NEXT MOVE =======================================================\n");
  printf("\n");
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

  //Execute UCT AMAF algortihm and select best action
  moveNumber = UCT_AMAF();

  //DEBUG
#if(TOMPlayer_AI_UCT_MAST_DEBUG_ROOT_CHILDREN_VALUES)
  Output_UCT_Tree_Node_Children(UCTroot);		//show values of roots actions (children)
#endif
#if(TOMPlayer_AI_UCT_MAST_VISUALIZE_UCT_GETC_AFTER_MOVE)
  cin.get();
#endif

  //return selected move
  return moveNumber;
}

//Updates internal game to match external game (replay moves in internal game)
void Player_AI_UCT_MAST::UCT_Update_Internal_Game(int number_actions)
{

  //check if external game should be copied to or replayed in internal game
  if ((game->is_deterministic) && (internal_game_force_copy == false)) {

    //play all players moves in internal copy of game (including own last move)
    for (int i = number_actions; i > 0; i--)
      internalGame->Play_Move(game->history_moves[game->current_plys - i + 1]);

    //copy external game to internal game
  }
  else {
    internalGame->Copy_Game_State_From(game, true, internalGame->current_plys - 1);
  }

  //DEBUG: check if move history of external and internal game is equal
#if(TOMPlayer_AI_UCT_MAST_DEBUG_HISTORY_COPY_CHECK)
  for (int i = 0; i <= game->current_plys; i++) {
    if (game->history_moves[i] != internalGame->history_moves[i]) {
      printf("PLAYER AI UCT: UCT_Update_Internal_Game(): game copy error - external and internal game history does not match at index %d: ext %d int %d ... RESETTING UCT PLAYER\n", i, game->history_moves[i], internalGame->history_moves[i]);
      i = game->current_plys + 1;
      Reset();
    }
  }
#endif

}

int Player_AI_UCT_MAST::UCT_AMAF()
{

  //--
  UCTnode* selected_leaf;
  double* final_rewards;

  //reset MAST flags
  for (int i = 0; i < all_actions_num; i++) {
    MAST_flagPlayer[i] = 0;
    MAST_flagMove[i] = 0;
    MAST_rewards[0][i] = 0.0;
    MAST_rewards[1][i] = 0.0;
    MAST_visits[0][i] = 0.0;
    MAST_visits[1][i] = 0.0;
  }

  //execute simulations with given computational budget
  last_extMove_numSimMoves = 0;
  this->numIterations_lastMove = 0;
  for (int i = 0; i < UCT_param_IterNum; i++) {

    MASTcount = 0;

#if(TOMPlayer_AI_UCT_MAST_DEBUG_SIMULATED_GAMES_OUT)
    printf("-> GAME_PLY %d SIMULATION %d\n", internalGame->current_plys, i);
#endif
    //RESET simulated game position to initial state
    simulatedGame->Copy_Game_State_From(internalGame, false);


    //DEBUG
    //internalGame->output_chains_to_STD();
    //simulatedGame->output_chains_to_STD();
    //simulatedGame->output_state_to_STD();
    //printf("sim player %d\n",simulatedGame->current_player);

    //UCT algorithm
    selected_leaf = UCT_AMAF_Tree_Policy(UCTroot, i);
    final_rewards = UCT_AMAF_Default_Policy(i);
    UCT_AMAF_Backup(selected_leaf, final_rewards, i);

    //UCTbackup(UCTtreePolicy(root), UCTdefaultPolicy());	//compact version

    //check if memory limit was exceeded - TODO: this is a basic version that work well if only 1 node is added per iteration, otherwise the procedure must be implemented inside UCTtreePolicy, where new nodes are allocated
    if (UCTtree_memorySize >= UCTtree_maxMemorySize) {
      i = UCT_param_IterNum;	//end the simulations loop
    }

    //check if computational budged is exceeded (number of simulated moves)
    if ((UCT_param_SimMoveNum > 0) && (last_extMove_numSimMoves >= UCT_param_SimMoveNum))
      i = UCT_param_IterNum;

    //DEBUG


#if(TOMPlayer_AI_UCT_MAST_VISUALIZE_LEVEL_UCT)
    printf("\nSim num %2d     score", i);
    for (int t = 0; t < game->number_players; t++)
      printf("  %3.5f", final_rewards[t]);
#if(!TOMPlayer_AI_UCT_MAST_VISUALIZE_UCT_ACTIONS_TREE)
    printf("     root  %2d", UCTroot->action_index);
#else
    printf("     tree  %2d", UCTroot->action_index);
    printf("%s", visualizeActionsTree.str().c_str());
    visualizeActionsTree.str("");		//set stringstream to empty
    visualizeActionsTree.clear();		//clear flags
#endif
#if(TOMPlayer_AI_UCT_MAST_VISUALIZE_UCT_ACTIONS_PLAYOUT)
    printf("    \t playout:");
    printf("%s", visualizeActionsPlayout.str().c_str());
    visualizeActionsPlayout.str("");	//set stringstream to empty
    visualizeActionsPlayout.clear();	//clear flags
#endif
#endif

#if(TOMPlayer_AI_UCT_MAST_DEBUG_TREE_EXPANSION_SIM)
    Output_UCT_Tree();
    Output_UCT_Tree_Node_Children(UCTroot);
#endif

    //increase global counters
    this->numIterations_lastMove++;
    this->numIterations_total++;
  }

  //DEBUG
#if(TOMPlayer_AI_UCT_MAST_DEBUG_TREE_EXPANSION)
  Output_UCT_Tree();
#endif

  //return best action from root (without exploring factors) and remember node
  if (UCTroot->number_explored_children > 0) {
    lastAction_node = UCT_AMAF_Tree_Policy_Best_Child(UCTroot, 0.0);
    return (lastAction_node->action_index);

    //no simulations run - return random action
  }
  else if (UCT_param_IterNum == 0) {
    lastAction_node = NULL;
    return game->Select_Move_Random();

    //no valid action (no children explored), return error
  }
  else {
    printf("PLAYER AI UCT: UCT(): action selection error - no valid action available\n");
    lastAction_node = NULL;
    return -1;
  }
}

Player_AI_UCT_MAST::UCTnode* Player_AI_UCT_MAST::UCT_AMAF_Tree_Policy(UCTnode* root, int simulation_number)
{

  //--
  UCTnode* currentNode = root;
  int terminalNode = (int)(simulatedGame->game_ended);

  //move through the tree and game
  while (terminalNode == 0) {

    MAST_flagPlayer[MASTcount] = simulatedGame->current_player;

    //check expanding condition and descend tree according to tree policy
    if (currentNode->number_explored_children >= simulatedGame->current_number_moves[simulatedGame->current_player]) {

      //select best child node/action
      currentNode = UCT_AMAF_Tree_Policy_Best_Child(currentNode, UCT_param_C);

      //play simulated move (if game not ended yet playMove() returns value 0)
      terminalNode = simulatedGame->Play_Move(currentNode->action_index);
      last_extMove_numSimMoves++;


      //DEBUG
#if(TOMPlayer_AI_UCT_MAST_DEBUG_TRACE_BEST_UCT)
      printf("Best node: %d  %4.1f %3.0f  %3.0f  %3.3f\n", currentNode->action_index, currentNode->rewards, currentNode->parent->visits, currentNode->visits, currentNode->value);
#endif
#if(TOMPlayer_AI_UCT_MAST_DEBUG_SIMULATED_GAMES_OUT)
      printf("-tree-\n");
#endif

      //expand if not fully expanded
    }
    else {

      //select a nontried action
      currentNode = UCT_Expand(currentNode);

      //play simulated move
      simulatedGame->Play_Move(currentNode->action_index);
      last_extMove_numSimMoves++;

      //is last node in tree
      terminalNode = 1;

#if(TOMPlayer_AI_UCT_MAST_DEBUG_SIMULATED_GAMES_OUT)
      printf("-tree expand-\n");
#endif
    }
    
    MAST_flagMove[MASTcount] = currentNode->action_index;
    MASTcount++;

    //check if computational budged is exceeded (number of simulated moves)
    if ((UCT_param_SimMoveNum > 0) && (last_extMove_numSimMoves >= UCT_param_SimMoveNum))
      terminalNode = 1;

#if(TOMPlayer_AI_UCT_MAST_VISUALIZE_UCT_ACTIONS_TREE)
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
#if(TOMPlayer_AI_UCT_MAST_DEBUG_SIMULATED_GAMES_OUT)

    simulatedGame->Output_Board_State();
    //simulatedGame->output_state_to_STD();
    //simulatedGame->output_chains_to_STD();
    //printf("Moves: %d %d\n",simulatedGame->num_moves[0], simulatedGame->num_moves[1]);
#endif
  }

  //save number of actions from root to selected leaf (search depth)
  UCTtree_treePolicy_lastDepth = simulatedGame->current_plys - internalGame->current_plys;

  //return selected leaf
  return currentNode;

};

/**
Select next child from given tree node and with given UCT exploration weight C.
*/
Player_AI_UCT_MAST::UCTnode* Player_AI_UCT_MAST::UCT_AMAF_Tree_Policy_Best_Child(UCTnode* parent, double param_C) {

  //--
  double bestValue, bestMAST;
  int multiple_best, randAction;
  UCTnode* selectedChild;

  //find best-valued children node
  bestValue = -DBL_MAX;
  bestMAST = -DBL_MAX;
  multiple_best = 1;
  selectedChild = NULL;
  for (int i = 0; i < parent->number_allowed_actions; i++) {


    //check if children was already allocated (for safety)
    if (parent->children[i] != NULL) {

      //---- UCB equation ----
      UCTnode* child = parent->children[i];


      child->value =
        ((child->rewards) / (child->visits)) +
        2.0 * param_C * sqrt(2 * log(parent->visits) / (child->visits));


      ////UCB equation
      //parent->children[i]->value = 
      //	(parent->children[i]->rewards / parent->children[i]->visits) +
      //	2.0 * param_C * sqrt(2*log(parent->visits) / parent->children[i]->visits);

      //printf("DEBUG VAL: %d %3.1f\n", i, value);

      //MAST for tie-breaking in tree policy
      int ai = child->action_index;
      double mastVal = (MAST_rewards[simulatedGame->current_player][ai]) / (MAST_visits[simulatedGame->current_player][ai] + 0.000001);

      //remember best children and count number of equal best children
      if (child->value == bestValue) {
        if (mastVal > bestMAST) {
          selectedChild = parent->children[i];
          bestMAST = mastVal;
        }
        else if (mastVal == bestMAST) {
          multiple_best++;
        }
      }
      else if (child->value > bestValue) {
        selectedChild = parent->children[i];
        bestValue = parent->children[i]->value;
        multiple_best = 1;
        bestMAST = mastVal;
      }

      //if (parent->children[i]->value == bestValue) {
      //  multiple_best++;
      //}
      //else if (parent->children[i]->value > bestValue) {
      //  selectedChild = parent->children[i];
      //  bestValue = parent->children[i]->value;
      //  multiple_best = 1;
      //}

      //DEBUG
#if(TOMPlayer_AI_UCT_MAST_DEBUG_TRACE_ALL_UCT)
      printf("-> node %d value: %5.3f\n", parent->children[i]->action_index, child->value);
#endif
    }
  }

  //if multiple best actions/children, break ties uniformly random
  if (multiple_best > 1) {
    randAction = (int)((rand() / (float)(RAND_MAX + 1)) * multiple_best);
    for (int i = 0; i < parent->number_allowed_actions; i++) {
      if (parent->children[i] != NULL) {
        int ai = parent->children[i]->action_index;
        double mastVal = (MAST_rewards[simulatedGame->current_player][ai]) / (MAST_visits[simulatedGame->current_player][ai] + 0.000001);
        if ((parent->children[i]->value == bestValue) && (mastVal == bestMAST)) {
          if (randAction <= 0) {
            selectedChild = parent->children[i];
            i = parent->number_allowed_actions;	//break loop
          }
          else {
            randAction--;
          }
        }
      }
    }
  }

  ////if multiple best actions/children, break ties uniformly random
  //if (multiple_best > 1) {
  //  randAction = (int)((rand() / (float)(RAND_MAX + 1)) * multiple_best);
  //  for (int i = 0; i < parent->number_allowed_actions; i++) {
  //    if (parent->children[i] != NULL) {
  //      if (parent->children[i]->value == bestValue) {
  //        if (randAction <= 0) {
  //          selectedChild = parent->children[i];
  //          i = parent->number_allowed_actions;	//break loop
  //        }
  //        else {
  //          randAction--;
  //        }
  //      }
  //    }
  //  }
  //}

  //return selected untried action
  return selectedChild;
}

/**
Expand the tree
*/
Player_AI_UCT_MAST::UCTnode* Player_AI_UCT_MAST::UCT_Expand(UCTnode* parent) {

  int randAction, cntAvailable;
  UCTnode* selectedChild;

#if(TOM_DEBUG)
  if ((parent->children == NULL) && (parent->number_explored_children > 0)) {
    printf("WARNING: PLAYER AI UCT: UCT_Expand(): node children list NOT allocated but number of explored children is %d\n", parent->number_explored_children);
  }
  else if ((parent->children != NULL) && (parent->number_explored_children <= 0)) {
    printf("WARNING: PLAYER AI UCT: UCT_Expand(): node children list allocated but number of explored children is %d ... ALLOCATING LIST (causing memory leak)\n", parent->number_explored_children);
    UCT_Tree_Node_AllocateList(parent, simulatedGame->current_number_moves[simulatedGame->current_player]);
  }
#endif

  //allocate memory resources when exploring first action from node
  if (parent->children == NULL)
    UCT_Tree_Node_AllocateList(parent, simulatedGame->current_number_moves[simulatedGame->current_player]);

  //printf("DEBUG: parent p %d %d\n", parent, parent->allowedActionNum);
  //for(int i = 0; i < parent->allowedActionNum; i++)
  //	printf("DEBUG: child p %d %d\n", parent->children[i], i);

  //choose random untried action

#if(!TOMPlayer_AI_UCT_MAST_DEBUG_DISABLE_RANDOM)
  randAction = (int)((rand() / (float)(RAND_MAX + 1))*(parent->number_allowed_actions - parent->number_explored_children));
#else
  randAction = 0;
#endif

  //find nontried action, cycle through all actions
  cntAvailable = 0;
  selectedChild = NULL;
  for (int i = 0; i < all_actions_num; i++) {

    //check available actions
    if (simulatedGame->current_moves[simulatedGame->current_player][i]) {

      //check if action was already tried / already exists in the tree
      if ((parent->children[cntAvailable]) == NULL) {
        if (randAction <= 0) {

          //allocate and init new children
          parent->children[cntAvailable] = UCT_Tree_Node_Init(i, parent);

          //mark as selected child/action
          selectedChild = parent->children[cntAvailable];

          //increase number of explored children actions/nodes
          parent->number_explored_children++;

          //second variant: DONT KNOW WHY YET, BUT THIS DOESNT WORK correctly when 5000+ simulations
          //int curPos = parent->number_explored_children;
          //parent->children[curPos] = UCT_Tree_Node_Init(i, parent);
          //selectedChild = parent->children[cntAvailable];

          //break the loop
          i = all_actions_num;
        }
        else {
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
Play default policy from current game position untill game end
*/
double* Player_AI_UCT_MAST::UCT_AMAF_Default_Policy(int simulation_number) {

  //--
  int gameStatus, lastMove;
  int num_simulated_plys;

  //simulate game until game-end
  num_simulated_plys = 0;
  gameStatus = (int)(simulatedGame->game_ended);
  while ((gameStatus == 0) && ((simulatedGame->current_plys - internalGame->current_plys) < UCT_param_defaultPolicy_maxPlys)) {


    //check if computational budged is exceeded (number of simulated moves)
    if ((UCT_param_SimMoveNum > 0) && (last_extMove_numSimMoves >= UCT_param_SimMoveNum)) {
      gameStatus = 1;
    }
    else {
      //DEBUG
      //if(simulatedGame->number_of_plays == 38) 
      //	printf("DEBUG: plys == %d", simulatedGame->number_of_plays);	

      // MAST
      int mcp = simulatedGame->current_player;
      MAST_flagPlayer[MASTcount] = mcp;

      int mnum = simulatedGame->current_number_moves[mcp];
      
      int aa = 0;
      double sumSoftMax = 0.0;
      for (int ml = 0; ml < simulatedGame->maximum_allowed_moves; ml++) {
        if (simulatedGame->current_moves[mcp][ml]) {
          MAST_list[aa] = ml;          
          double mastVal = (MAST_rewards[mcp][MAST_list[aa]]) / (MAST_visits[mcp][MAST_list[aa]] + 0.000001);
          sumSoftMax += exp(mastVal / (this->MAST_paramT + 0.000001));
          aa++;
        }
      }

      double sumProb = 0.0;
      for (int aa = 0; aa < mnum; aa++) {
        double mastVal = (MAST_rewards[mcp][MAST_list[aa]]) / (MAST_visits[mcp][MAST_list[aa]] + 0.000001);
        double mastP = exp(mastVal / (this->MAST_paramT + 0.000001)) / sumSoftMax;
        MAST_prob[aa] = mastP;
        sumProb += mastP;
      }

      double roll = rand() / ((double)(RAND_MAX)+0.000001) * sumProb;
      int lastMove = 0;
      for (int aa = 0; aa < mnum; aa++) {
        roll -= MAST_prob[aa];
        if (roll <= 0) {
          lastMove = MAST_list[aa];
          break;
        }
      }

      //pick random move if softmax overflows
      if(isnan(roll) || !isfinite(roll))
        lastMove = simulatedGame->Select_Move_Random();

      //play move in internal simulated game
      gameStatus = simulatedGame->Play_Move(lastMove);
      last_extMove_numSimMoves++;

      //DEBUG
#if((TOMPlayer_AI_UCT_MAST_VISUALIZE_LEVEL_UCT)&&TOMPlayer_AI_UCT_MAST_VISUALIZE_UCT_ACTIONS_TREE)
      //sprintf(visualizeActionsTree, "  > %2d", currentNode->action_index);
      visualizeActionsPlayout << "  > " << lastMove;
      //printf("  > %2d", currentNode->action_index);
#endif
#if(TOMPlayer_AI_UCT_MAST_DEBUG_SIMULATED_GAMES_OUT)
      printf("-playout-\n");
      simulatedGame->Output_Board_State();
      //simulatedGame->output_state_to_STD();
      //simulatedGame->output_chains_to_STD();
      //printf("Moves: %d %d\n",simulatedGame->num_moves[0], simulatedGame->num_moves[1]);
#endif

      MAST_flagMove[MASTcount] = lastMove;
      MASTcount++;

      //todo: pseudocode some-first-amaf, pseudocode: 
      //#if(SOME_FIRST_AMAF_ENABLED)
      //		if(num_simulated_plys < some_first_threshold)
      //			AMAF_flagList[lastMove] = simulation_number;
      //#endif

      //num_simulated_plys++;
    }

  }

  //calculate score
  simulatedGame->Calculate_Score();

  //return final score
  return (simulatedGame->score);

}

/**
Single- or two-player backup reward through the tree
*/
void Player_AI_UCT_MAST::UCT_AMAF_Backup(UCTnode* leaf, double* rewards, int simulation_number) {

  //--
  UCTnode* currentNode = leaf;
  int belonging_player;

  //select correct players' reward
  //if(UCTtree_treePolicy_lastDepth % 2 == 0)
  //	if(internalGame->current_plys % 2 == 0)
  //		belonging_player = 1;
  //	else
  //		belonging_player = 0;
  //else
  //	if(internalGame->current_plys % 2 == 0)
  //		belonging_player = 0;
  //	else
  //		belonging_player = 1;

  //TODO IMPROVE: NOW TEMPORARY SOLUTION FOR SINGLEPLAYER and TWOPLAYER games
  if (game->number_players > 1)
    //select correct players' reward: bitwise replacement for upper if-sentences (instead of modulo 2)
    belonging_player = (UCTtree_treePolicy_lastDepth & 1) == (internalGame->current_plys & 1);
  else
    belonging_player = 0;

  //propagate reward up through the tree
  //while(currentNode != NULL){
  //	currentNode->visits += 1.0;
  //	currentNode->rewards += rewards[belonging_player];
  //	currentNode = currentNode->parent;
  //	belonging_player = internalGame->Get_Previous_Player(belonging_player);
  //}

  //propagate reward up through the tree
  //while(currentNode != NULL){	//this was the old implementation (new one below should be better for optimization)
  for (int i = 0; i < UCTtree_treePolicy_lastDepth + 1; i++) {

    //update current node
    currentNode->visits += 1.0;
    currentNode->rewards += rewards[belonging_player];

    //move to parent
    currentNode = currentNode->parent;

    //MAST
    MASTcount--;
    int mp = MAST_flagPlayer[MASTcount];
    int mm = MAST_flagMove[MASTcount];
    if (MASTcount > 0) {  // so the root is ignored
      MAST_rewards[mp][mm] += rewards[belonging_player];
      MAST_visits[mp][mm] += 1.0;
    }

    //change active player (to get correct reward)
    belonging_player = internalGame->Get_Previous_Player(belonging_player);

  }

  //DEBUG AMAF
#if(TOMPlayer_AI_UCT_MAST_DEBUG_BACKUP_SHOW_AMAFTAGS)
  printf("AMAF TAGS, real_ply %3d,  sim %3d: \t", internalGame->current_plys, simulation_number);
  for (int i = 0; i < all_actions_num; i++)
    printf(" %d", AMAF_flagList[i] - simulation_number - 1);
  printf("\n");
#endif

}

/**
UCT Tree Node - initialization
*/
Player_AI_UCT_MAST::UCTnode* Player_AI_UCT_MAST::UCT_Tree_Node_Init(int action, UCTnode* parent, const bool rootNode)
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
  //if(!rootNode)
  //  parent->number_explored_children++;

  return node;
}

/**
UCT Tree Node - reset values
*/
void Player_AI_UCT_MAST::UCT_Tree_Node_Reset(UCTnode* node)
{
  //--
  node->visits = 0.0;
  node->rewards = 0.0;
  node->number_explored_children = 0;

}

/**
UCT Tree Node - allocate children (actions) list
*/
void Player_AI_UCT_MAST::UCT_Tree_Node_AllocateList(UCTnode* node, int list_length)
{
  //remember list length
  node->number_allowed_actions = list_length;

  //allocate and init list
  node->children = new UCTnode*[list_length];
  for (int i = 0; i < list_length; i++)
    node->children[i] = NULL;

  //increase memory consumption counter
  UCTtree_memorySize += list_length*sizeof(UCTnode*);
}

void Player_AI_UCT_MAST::UCT_Tree_Change_Root(int number_actions)
{
  //is root change needed?
  if (number_actions > 0) {

    //trim tree, delete unrelevant part of tree
    if (!UCTtree_preserve) {

      UCTtree_newRoot = NULL;
      UCT_Tree_Trim(UCTroot, number_actions);

      //new root has been found
      if (UCTtree_newRoot != NULL) {

        //delete old root and set new root
        if (UCTroot != UCTtree_newRoot) {		//redundant check, but may be needed in some special cases
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
      else {

        //decrease tree memory size counter for old UCTroot as recursive call did not decrease it
        //UCTtree_num_nodes--;
        //UCTtree_memorySize -= sizeof(UCTnode);

        //reset root node
        UCTroot->action_index = internalGame->history_moves[internalGame->current_plys];
        UCTroot->children = NULL;
        UCT_Tree_Node_Reset(UCTroot);

        //DEBUG
#if(TOMPlayer_AI_UCT_MAST_DEBUG_MEMORY_SIZE_COUNT)
        if ((UCTtree_num_nodes != 1) || (UCTtree_memorySize != sizeof(UCTnode)))
          printf("PLAYER AI UCT: Tree_Change_Root(): tree error - tree incorrectly deleted, remaining nodes %d\n", UCTtree_num_nodes);
#endif

      }

      //preserve complete tree structure in memory, only move root pointer to different node
    }
    else {

      UCT_Tree_Preserve();

    }

  }

}


/**
Select new tree root for current game state and trim tree if UCTtree_preserve is not set: delete all nodes (and free memory) except active branch
WARNING: does not delete first call branchRoot node
*/
void Player_AI_UCT_MAST::UCT_Tree_Trim(UCTnode* branchRoot, int remaining_depth)
{

  //new root has not yet been found
  if (remaining_depth > 0) {

    //search deeper in the tree if branchRoot is not a leaf - if has children
    if (branchRoot->children != NULL) {

      //decrease tree memory size counter (must be done before loop, because number_explored_children is decreased to 0)
      UCTtree_num_nodes -= (branchRoot->number_explored_children);
      UCTtree_memorySize -= ((branchRoot->number_allowed_actions*sizeof(UCTnode*) + branchRoot->number_explored_children*sizeof(UCTnode)));

      //loop through all children
      for (int i = 0; i < branchRoot->number_allowed_actions, branchRoot->number_explored_children > 0; i++) {

        //children is valid
        if (branchRoot->children[i] != NULL) {

          //selected action found in tree
          if (branchRoot->children[i]->action_index == internalGame->history_moves[internalGame->current_plys - remaining_depth + 1]) {

            UCT_Tree_Trim(branchRoot->children[i], remaining_depth - 1);

            //delete child if it is not new found root
            if (remaining_depth - 1 > 0)
              delete(branchRoot->children[i]);

            //delete non-selected tree branch
          }
          else {

            UCT_Tree_Delete(branchRoot->children[i]);

          }

          //decrease counter of children
          branchRoot->number_explored_children--;

          //delete child
          //delete(branchRoot->children[i]);
        }
      }

      //delete root node list of children
      delete(branchRoot->children);

    }

    //new root has been found
  }
  else {

    UCTtree_newRoot = branchRoot;

  }

}


/**
Recursively delete tree from selected node, including root node
WARNING: does not delete first call branchRoot node
*/
void Player_AI_UCT_MAST::UCT_Tree_Delete(UCTnode* branchRoot)
{

  //search deeper in the tree if branchRoot is not a leaf - if has children
  if (branchRoot->children != NULL) {

    //decrease tree memory size counter (must be done before loop, because number_explored_children is decreased to 0)
    UCTtree_num_nodes -= (branchRoot->number_explored_children);
    UCTtree_memorySize -= ((branchRoot->number_allowed_actions*sizeof(UCTnode*) + (branchRoot->number_explored_children)*sizeof(UCTnode)));	//size decreased by number of children nodes and by size of children list of root node

                                                                                                                                            //loop through all children
    for (int i = 0; i < branchRoot->number_allowed_actions, branchRoot->number_explored_children > 0; i++) {
      if (branchRoot->children[i] != NULL) {
        UCT_Tree_Delete(branchRoot->children[i]);
        branchRoot->number_explored_children--;
      }
    }

    //delete root node list of children
    delete(branchRoot->children);

  }

  //delete self
  delete(branchRoot);

}

/**
Recursively delete selected tree branch, without root node
*/
void Player_AI_UCT_MAST::UCT_Tree_Reset()
{

  UCTnode* branchRoot;

  //from which node to reset the tree
  if (!UCTtree_preserve)
    branchRoot = UCTroot;
  else
    branchRoot = UCTroot_memory;

  //node has children
  if (branchRoot->children != NULL) {

    //find and delete children nodes
    for (int i = 0; i < branchRoot->number_allowed_actions, branchRoot->number_explored_children > 0; i++) {
      if (branchRoot->children[i] != NULL) {
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
void Player_AI_UCT_MAST::UCT_Tree_Preserve()
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
void Player_AI_UCT_MAST::Output_UCT_Tree()
{
  printf("\n========== BEGIN OUTPUT_UCT_TREE ==========\n\nTREE SIZE: %d nodes, memory: %d B (%.3f MB)\n", UCTtree_num_nodes, UCTtree_memorySize, UCTtree_memorySize / 1024.0 / 1024.0);
  printf("Leafs < Root\n");
  Output_UCT_Tree_Branch(UCTroot);
  printf("\n========== END OUTPUT_UCT_TREE ==========\n\n");
}

void Player_AI_UCT_MAST::Output_UCT_Tree_Node_Children(UCTnode* parent)
{
  //--
  printf("\n========== BEGIN OUTPUT_UCT_TREE_NODE_CHILDREN ==========\naction:    N        R  amafN  amafQ  \tvalue:\n");
  for (int i = 0; i < UCTroot->number_allowed_actions; i++) {
    if (UCTroot->children[i] != NULL) {
      printf("   %3d:  %5.1f  %5.1f  %5.1f  %5.1f  \t%3.3f\n",
        UCTroot->children[i]->action_index,
        UCTroot->children[i]->visits,
        UCTroot->children[i]->rewards,
        UCTroot->children[i]->value
        );
    }
    else {
      printf("Untried action: parent->children[%d]\n", i);
    }
  }
  printf("\n========== END OUTPUT_UCT_TREE_NODE_CHILDREN ==========\n\n");
}

/**
Output part of tree starting from branchRoot
*/
void Player_AI_UCT_MAST::Output_UCT_Tree_Branch(UCTnode* branchRoot)
{
  UCTnode* tmpNode;

  //print current node and its parents
  printf("%d", branchRoot->action_index);
  tmpNode = branchRoot->parent;
  while (tmpNode != NULL) {
    printf(" < %d", tmpNode->action_index);
    tmpNode = tmpNode->parent;
  }

  //print current nodes' values
  printf("\t :\t %2.1f %2.1f", branchRoot->visits, branchRoot->rewards);

  //search deeper in the tree if branchRoot is not a leaf - if has children
  if (branchRoot->children != NULL) {

    //print children info
    printf("\t %d/%d :", branchRoot->number_explored_children, branchRoot->number_allowed_actions);

    //print current nodes' children list
    for (int i = 0, c = 0; i < branchRoot->number_allowed_actions, c < branchRoot->number_explored_children; i++) {
      if (branchRoot->children[i] != NULL) {
        printf(" %d", branchRoot->children[i]->action_index);
        c++;
      }
    }

    printf("\n");

    //recursively call children nodes' output
    for (int i = 0, c = 0; i < branchRoot->number_allowed_actions, c < branchRoot->number_explored_children; i++) {
      if (branchRoot->children[i] != NULL) {
        Output_UCT_Tree_Branch(branchRoot->children[i]);
        c++;
      }
    }

  }
  else {
    printf("\n");
  }

}

void Player_AI_UCT_MAST::Debug_UCT_Tree_MemoryState()
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

int Player_AI_UCT_MAST::Debug_UCT_Tree_Size(UCTnode*)
{
  return 0;
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