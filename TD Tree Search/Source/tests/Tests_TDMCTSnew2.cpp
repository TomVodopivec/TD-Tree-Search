#include "Tests_TDMCTSnew2.hpp"

namespace Tests_TDMCTSnew2
{

  void main()
  {

    // 2017.02.05

    // measuerements for Experiment5: two-player adversary games: Connect4, Hex, Gomoku
    //		- learning with self-play
    //		- building a minmax tree
    //		- planning
    //		- limited computation budged (number of timesteps)
    //		- retaining memorized values (tree) between external moves (so, tree is not deleted after each move)
    //	control variables : lambda, own_ucb_C, opponent ucb_C, computational budget of num timesteps (equal for both players)
    //	measured variables : average win rate against an UCT player from a single game, where 50% of games played as player1 and 50% times as player2
    int e = 0;

    // experiment 5.1: find best ucb_C for both players (by observing the draw rates - by hand)
    e = 1;
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, NULL, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 1000, new Game_TicTacToe(), 200, NULL, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, NULL, NULL);


    // experiment 5.2: find best ucb_C for evaluated UCT player
    e = 2;
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, 0.20, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, 0.35, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_ConnectFour(), 1000, 0.05, NULL);
  
    // experiment 5.3: find best lambda for evaluated SARSA-UCT player, with global normalization bounds
    e = 3;
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, 0.20, 0.20);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, 0.35, 0.30);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_ConnectFour(), 1000, 0.05, 0.15);

    // experiment 5.4: find best lambda for evaluated SARSA-UCT player, with local normalization bounds
    e = 4;
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, 0.20, 0.20);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, 0.35, 0.30);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(e, 20000, new Game_ConnectFour(), 1000, 0.05, 0.15);


    Game_Engine* gomo7 = new Game_Gomoku(); gomo7->board_length = 7; gomo7->board_height = 7; gomo7->Settings_Apply_Changes();
    Game_Engine* gomo9 = new Game_Gomoku(); gomo9->board_length = 9; gomo9->board_height = 9; gomo9->Settings_Apply_Changes();
    Game_Engine* gomo11 = new Game_Gomoku(); gomo11->board_length = 11; gomo11->board_height = 11; gomo11->Settings_Apply_Changes();
    Game_Engine* gomo13 = new Game_Gomoku(); gomo13->board_length = 13; gomo13->board_height = 13; gomo13->Settings_Apply_Changes();
    Game_Engine* hex7 = new Game_Hex(); hex7->board_length = 7; hex7->board_height = 7; hex7->Settings_Apply_Changes();
    Game_Engine* hex11 = new Game_Hex(); hex11->board_length = 11; hex11->board_height = 11; hex11->Settings_Apply_Changes();

    // fix wrong config from previous experiments
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 1000, hex11, 1000, 0.15, 0.15);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 10000, 0.15, 0.15);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 100000, 0.15, 0.15);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, hex11, 1000, 0.15, 0.15);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, hex11, 10000, 0.1, 0.1);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, hex11, 100000, 0.25, 0.25);


    //---------------------------- AMAF --------------------

    // !!!!!!!!!! DO NOT FORGET !!!!!!!!!!!! in Experiment5_perStep_BatchUCB() under 2017.02.05 EXPERIMENTS set self player0 to AMAFplayerSelf

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 2000, new Game_ConnectFour(), 500, 0.25, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 200, new Game_ConnectFour(), 1000, 0.05, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 2000, 0.05, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 5000, 0.05, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 10000, 0.15, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 1000, gomo9, 1000, 0.25, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 200, gomo9, 10000, 0.1, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 100000, 0.2, NULL);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 1000, hex11, 1000, 0.15, NULL);  // !!! set TOMPLAYER_AI_UCT_AMAF_VARIANT=2
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 10000, 0.1, NULL);  // !!! set TOMPLAYER_AI_UCT_AMAF_VARIANT=2
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 100000, 0.05, NULL);  // !!! set TOMPLAYER_AI_UCT_AMAF_VARIANT=2

    // !!!!!!!!!! DO NOT FORGET !!!!!!!!!!!! in Experiment5_perStep_BatchUCB() under 2017.02.05 EXPERIMENTS set player1 to AMAFplayer
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, new Game_ConnectFour(), 500, 0.05, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 200, new Game_ConnectFour(), 1000, 0.15, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 200, new Game_ConnectFour(), 2000, 0.20, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, new Game_ConnectFour(), 5000, 0.10, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, new Game_ConnectFour(), 10000, 0.15, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, gomo9, 1000, 0.25, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 200, gomo9, 10000, 0.15, 0.1);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, gomo9, 100000, 0.45, 0.2);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, hex11, 1000, 0.15, ?);  // !!! set TOMPLAYER_AI_UCT_AMAF_VARIANT=2
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 200, hex11, 10000, 0.1, ?);  // !!! set TOMPLAYER_AI_UCT_AMAF_VARIANT=2
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, hex11, 100000, 0.05, ?);  // !!! set TOMPLAYER_AI_UCT_AMAF_VARIANT=2


    //---------------------------- RAVE --------------------

    // !!!!!!!!!! DO NOT FORGET !!!!!!!!!!!! in Experiment5_perStep_BatchUCB() under 2017.02.05 EXPERIMENTS set self player0 to RAVEplayerSelf
    // put desired value of Cp as last argument
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 500, 0.25, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 500, 0.25, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 500, 0.25, NULL, 0.0, -1, -1, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 2000, 0.05, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 2000, 0.05, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 2000, 0.05, NULL, 0.0, -1, -1, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 10000, 0.15, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 10000, 0.15, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 10000, 0.15, NULL, 0.0, -1, -1, 0.25);

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 1000, 0.25, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 1000, 0.25, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 1000, 0.25, NULL, 0.0, -1, -1, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 10000, 0.10, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 10000, 0.10, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 10000, 0.10, NULL, 0.0, -1, -1, 0.10);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 100000, 0.15, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 100000, 0.15, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 100000, 0.15, NULL, 0.0, -1, -1, 0.15);

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 1000, 0.15, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 1000, 0.15, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 1000, 0.15, NULL, 0.0, -1, -1, 0.15);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 10000, 0.10, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 10000, 0.10, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 10000, 0.10, NULL, 0.0, -1, -1, 0.10);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 100000, 0.25, NULL, 0.0, -1, -1, 0.00);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 100000, 0.25, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 100000, 0.25, NULL, 0.0, -1, -1, 0.25);

    // !!!!!!!!!! DO NOT FORGET !!!!!!!!!!!! in Experiment5_perStep_BatchUCB() under 2017.02.05 EXPERIMENTS set self player1 to RAVEplayerSelf
    // put desired value of RAVE_V as last argument

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, new Game_ConnectFour(), 500, 0.05, 0.25, 0.0, -1, -1, 50.0);


    //---------------------------- MAST --------------------

    // !!!!!!!!!! DO NOT FORGET !!!!!!!!!!!! in Experiment5_perStep_BatchUCB() under 2017.02.05 EXPERIMENTS set self player0 to MASTplayerSelf
    // put desired value of Cp as last argument

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 1000, new Game_ConnectFour(), 500, 0.25, NULL, 0.0, -1, -1, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 2000, 0.05, NULL, 0.0, -1, -1, 0.05);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, new Game_ConnectFour(), 10000, 0.15, NULL, 0.0, -1, -1, 0.15);

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 1000, gomo9, 1000, 0.25, NULL, 0.0, -1, -1, 0.25);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 10000, 0.10, NULL, 0.0, -1, -1, 0.10);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, gomo9, 100000, 0.15, NULL, 0.0, -1, -1, 0.15);

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 1000, 0.15, NULL, 0.0, -1, -1, 0.15);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 10000, 0.10, NULL, 0.0, -1, -1, 0.10);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(2, 100, hex11, 100000, 0.25, NULL, 0.0, -1, -1, 0.25);

    // FOR FUN
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 200, new Game_ConnectFour(), 2000, 0.05, 0.25);


    // 2017-02-05
    //---------------------------- Sarsa-UCT + MAST --------------------

    // !!!!!!!!!! DO NOT FORGET: in Experiment5_perStep_BatchUCB() under "FOR THE 2017-02-28 EXPERIMENTS" uncomment the required lines
    // run this experiments both with ((Player_AI_RL*)(positionedPlayers[0]))->config_MASTenable = 1 and with config_MASTenable = 3

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, new Game_ConnectFour(), 500, 0.25, 0.25, 1.0, -1, -1, 1000);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, new Game_ConnectFour(), 2000, 0.05, 0.05, 1.0, -1, -1, 1000);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, new Game_ConnectFour(), 10000, 0.15, 0.15, 1.0, -1, -1, 1000);

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, gomo9, 1000, 0.25, 0.25, 1.0, -1, -1, 0.1);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, gomo9, 10000, 0.1, 0.1, 1.0, -1, -1, 0.1);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, gomo9, 100000, 0.15, 0.15, 1.0, -1, -1, 1);

    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 1000, hex11, 1000, 0.15, 0.15, 1.0, -1, -1, 0.1);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, hex11, 10000, 0.1, 0.1, 1.0, -1, -1, 0.1);
    //Tests_TDMCTSnew2::Experiment5_perStep_BatchUCB(3, 100, hex11, 100000, 0.25, 0.25, 1.0, -1, -1, 0.5);



//


  }

  // measuerements for Experiment5: two-player adversary games: Connect4, Hex, Gomoku
  //		- learning with self-play
  //		- building a minmax tree
  //		- planning
  //		- limited computation budged (number of timesteps)
  //		- retaining memorized values (tree) between external moves (so, tree is not deleted after each move)
  //	control variables : lambda, own_ucb_C, opponent ucb_C, computational budget of num timesteps (equal for both players)
  //	measured variables : average win rate against UCT player from a single game, where 50% of games played as player1 and 50% times as player2

  void Experiment5_perStep_BatchUCB(int experimentType, int input_repeats, Game_Engine* game, const int timeSteps, double opponentUCBC, double evaluatedUCBC, double evaluatedTDlam, int startIndex, int endIndex, double additionalPar)
  {

    //-- EXECUTION SETTINGS --//
    int config_IndexStart;
    int config_IndexEnd;

    //set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
    if ((startIndex == -1) && (endIndex == -1)) {
      config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
      config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
    }
    else {
      config_IndexStart = startIndex;
      config_IndexEnd = endIndex;
    }

    //what will be the calculated confidence interval
    double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

    //output settings
    bool config_show_individual_final_output = 1;

    //-- END OF EXECUTION SETTINGS --//

    //---- common settings for this experiment ----//

    Player_AI_RL* player1 = new Player_AI_RL(game);		//THIS IS THE EVALUATED PLAYER <- THE RESULTS APPLY FOR THIS PLAYER
    Player_AI_RL* player2 = new Player_AI_RL(game);		//THIS IS THE OPPONENT PLAYER
    Player_AI_RL* players[2] = { player1, player2 };
    player1->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::TTT_METRICS_PER_TIMESTEPS;
    player2->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::TTT_METRICS_PER_TIMESTEPS;
    char* procedureName = "Experiment5_perStep_BatchUCB()";
    char* xAxisLabel = "tStp/mov";

    //CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
    int total_number_configurations = 0;
    int cucbMax = 0;
    int clMax = 0;

    if (experimentType == 1)
    {
      total_number_configurations = 15;
      //total_number_configurations = 7;
      cucbMax = total_number_configurations;
      clMax = 1;
    }
    else if (experimentType == 2)
    {
      total_number_configurations = 15;
      //total_number_configurations = 7;
      cucbMax = total_number_configurations;
      clMax = 1;
    }
    else if ((experimentType == 3) || (experimentType == 4))
    {
      total_number_configurations = 12;
      //total_number_configurations = 6;
      //total_number_configurations = 1;
      cucbMax = 1;
      clMax = total_number_configurations;
    }

    double config_CValues[] = {0.0, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 1.0};
    //double config_CValues[] = { 0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 80, 100, 150, 200, 400};  // FOR RAVE
    //double config_CValues[] = { 0.01, 0.1, 1, 10, 100, 1000, 10000}; // FOR MAST
    //double config_CValues[] = { 0.0, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30};
    //double config_CValues[] = { 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
    //double config_CValues[] = { 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40 };
    //double config_CValues[] = { 0.0, 0.01, 0.02, 0.04, 0.05, 0.08, 0.10 };
    
    double config_lambdaValues[] = {1.0, 0.9999, 0.999, 0.99, 0.95, 0.9, 0.8, 0.6, 0.4, 0.2, 0.1, 0.0};
    //double config_lambdaValues[] = {0.9999, 0.99, 0.95};
    //double config_lambdaValues[] = {1.0, 0.9999, 0.999, 0.99, 0.95, 0.90};
    //double config_lambdaValues[] = { 1.0, 0.999, 0.95, 0.90, 0.70, 0.50 };
    //double config_lambdaValues[] = { 1.00 };
    //double config_lambdaValues[] = { 0.2, 0.1, 0.05, 0.01, 0.005, 0.001 };

    int config_max_num_repeats = input_repeats;	//a single repeat consists of two games, one from each starting position
                          //1000   repeats ~ std. error 1.00%
                          //10000  repeats ~ std. error 0.33%
                          //20000  repeats ~ std. error 0.25%
                          //100000 repeats ~ std. error 0.10%
                          //1M	 repeats ~ std. error 0.03%

    int config_timeStepsPerMove_values[] = {
      timeSteps
    };
    int config_num_timeStepsPerMove_values = 1;	//approximately 35 seconds of computation for 1000 repeats (year 2015)

    //-- game configuration

    //-- player configuration 

    //// for description and list of possible parameters see "Player_AI_RL.hpp"

    //// evaluated player settings (player1)
    player1->config_policy_evaluation = Player_AI_RL::POLICY_EVALUATIONS::TDLAMBDA_ONPOLICY;
    player1->config_control_policy = Player_AI_RL::CONTROL_POLICIES::UCB1;
    player1->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::GLOBAL;
    player1->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::KNOWN_RETURN;
    player1->config_offpolicy_backup_recheck_best = 0;
    player1->config_ExplorationLinear_maxExtMoves = 0;
    player1->config_ExplorationLinear_maxEpisodes = 0;
    player1->par_egreedy_e = 0.1;	//not needed in this experimental setting, but just in case
    player1->par_ucb_c = 1.0;
    player1->par_td_initVal = 0.0;
    player1->par_task_gamma = 1.0;
    player1->par_td_lambda = 1.0;
    player1->par_num_episodes = -1;
    player1->par_simulated_horizon_lenght = -1;
    player1->config_memory_limitMB = 2048;	//in MegaBytes
    player1->config_ExplorationLinear_maxActions = 0;
    player1->config_num_new_nodes_per_episode = 1;
    player1->config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
    player1->config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
    player1->config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;
    player1->config_alpha_type = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;
    player1->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;
    player1->config_output_depth = 0;
    player1->config_outputWarning_Qbounds = 0;

    //// opponent settings (player2)
    player2->config_policy_evaluation = Player_AI_RL::POLICY_EVALUATIONS::TDLAMBDA_ONPOLICY;
    player2->config_control_policy = Player_AI_RL::CONTROL_POLICIES::UCB1;
    player2->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::GLOBAL;
    player2->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::KNOWN_RETURN;
    player2->config_offpolicy_backup_recheck_best = 0;
    player2->config_ExplorationLinear_maxExtMoves = 0;
    player2->config_ExplorationLinear_maxEpisodes = 0;
    player2->par_egreedy_e = 0.1;	//not needed in this experimental setting, but just in case
    player2->par_ucb_c = 1.0;
    player2->par_td_initVal = 0.0;
    player2->par_task_gamma = 1.0;
    player2->par_td_lambda = 1.0;
    player2->par_num_episodes = -1;
    player2->par_simulated_horizon_lenght = -1;
    player2->config_memory_limitMB = 2048;	//in MegaBytes
    player2->config_ExplorationLinear_maxActions = 0;
    player2->config_num_new_nodes_per_episode = 1;
    player2->config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
    player2->config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
    player2->config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;
    player2->config_alpha_type = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;
    player2->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;
    player2->config_output_depth = 0;
    player2->config_outputWarning_Qbounds = 0;

    // experiment runtime settings
    int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

    //---- end of common settings ----//

    //-- finalize init
    if (config_IndexStart < 0)
      config_IndexStart = 0;
    if (config_IndexStart >= total_number_configurations)
      config_IndexStart = total_number_configurations - 1;
    if (config_IndexEnd >= total_number_configurations)
      config_IndexEnd = total_number_configurations - 1;
    if (config_IndexEnd < config_IndexStart)
      config_IndexEnd = total_number_configurations - 1;

    //-- prepare storage structures
    int results_num_metrics = Player_AI_RL::experimentNumMetrics[player1->config_experiment];

    Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
    for (int c = config_IndexStart; c <= config_IndexEnd; c++) {
      gatheredResults[c] = new Tool_Sample_Storage**[config_num_timeStepsPerMove_values];
      for (int m = 0; m < config_num_timeStepsPerMove_values; m++) {
        gatheredResults[c][m] = new Tool_Sample_Storage*[results_num_metrics];
        for (int s = 0; s < results_num_metrics; s++) {
          gatheredResults[c][m][s] = new Tool_Sample_Storage(0);	//do not store individual samples, but compute only descriptive statistics (online)
        }
      }
    }

    //-- prepare files
    int results_num_files = results_num_metrics;
    MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
    for (int m = 0; m < results_num_metrics; m++) {
      resultsFilePrinter->filenames[m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player1->config_experiment][m] + "_mean.txt");
    }

    if (resultsFilePrinter->Create_Output_Files() != 0) {
      gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
      cout << endl << "Press any key to exit.";
      cin.get();
      exit(EXIT_FAILURE);
    }

    //-- initial output (to stdout and to files)
    gmp->Print("\n%s\n", procedureName);
    gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
    game->Output_Description(false);

    // print headers of result files
    for (int f = 0; f < results_num_files; f++) {
      resultsFilePrinter->PrintI(f, "\n%s\n", procedureName);
      resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
      resultsFilePrinter->PrintI(f, "  P1cp P2cp P1lam  P1gam  P1alp  ConfigID             ");
      for (int e = 0; e < config_num_timeStepsPerMove_values; e++)
        resultsFilePrinter->PrintI(f, "  %8d", config_timeStepsPerMove_values[e]);
      resultsFilePrinter->PrintI(f, "\n");
    }

    //---- execute batch of experiments ----//

    char printLinePrefix[256];

    //index of current configuration
    int sInd = 0;

    if ((experimentType == 4) || (experimentType == 5))
    {
      player1->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL_THEN_GLOBAL;
      player1->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::KNOWN_RETURN;
      player1->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::CHILDREN_CURRENT_QVAL;
    }

    ////different UCB C
    for (int cucb = 0; cucb < cucbMax; cucb++) {
      //for (int cucb = 8; cucb < 8+1; cucb++){
      if (experimentType == 1)
      {
        //player1->par_ucb_c = (double)cucb / 10.0;
        //player2->par_ucb_c = (double)cucb / 10.0;

        player1->par_ucb_c = config_CValues[cucb];
        player2->par_ucb_c = config_CValues[cucb];
        //player1->par_simulated_horizon_lenght = 10;
        //player2->par_simulated_horizon_lenght = 10;
      }
      else if (experimentType == 2)
      {
        //double tmpMin = max(opponentUCBC - (cucbMax-1)/2/20.0, 0.0);
        //player1->par_ucb_c = tmpMin + (double)cucb / 20.0;
        //player1->par_ucb_c = (double)cucb / 10.0;
        player1->par_ucb_c = config_CValues[cucb];
        player2->par_ucb_c = opponentUCBC;
      }
      else if ((experimentType == 3) || (experimentType == 4))
      {
        player1->par_ucb_c = evaluatedUCBC;
        player2->par_ucb_c = opponentUCBC;
      }

      //different lambda for player1
      for (int cl = 0; cl < clMax; cl++) {
        //for (int cl = clMax - 1; cl < clMax; cl++){
        if ((experimentType == 1) || (experimentType == 2))
        {
          player1->par_td_lambda = 1.0;
          player2->par_td_lambda = 1.0;
        }
        else if ((experimentType == 3) || (experimentType == 4))
        {          
          //player1->par_td_lambda = config_lambdaValues[cl%2]; //measure only first two values in array
          player1->par_td_lambda = config_lambdaValues[cl];
          player2->par_td_lambda = 1.0;
        }

        //for (int cl = 19; cl >= 19; cl--){
        //	if (cl < 10)
        //		player1->par_td_lambda = (double)(cl) / 10.0;				//from 0.0 to 0.9 with step 0.1
        //	else if (cl < 19)
        //		player1->par_td_lambda = 0.9 + (double)(cl - 9) / 100.0;	//from 0.91 to 0.99 with step 0.01
        //	else
        //		player1->par_td_lambda = 1.0;

        // prepare output line string
        sprintf_s(printLinePrefix, "  %4.2f %4.2f %5.4f", player1->par_ucb_c, player2->par_ucb_c, player1->par_td_lambda);

        // increase external counter
        sInd++;
        int configurationSerialID = sInd - 1;

        //safety check
        if (configurationSerialID > total_number_configurations) {
          gmp->Print("ERROR: Experiment5_perStep_BatchUCB(): configurationSerialID %d > total_number_configurations %d; ABORTING\n", configurationSerialID, total_number_configurations);
          return;
        }
        //consider the execution settings
        if (!((configurationSerialID < config_IndexStart) || (configurationSerialID > config_IndexEnd) || (config_IndexEnd < config_IndexStart))) {

          //different number of simulated steps per external move
          for (int cnt_stpsPerMove = 0; cnt_stpsPerMove < config_num_timeStepsPerMove_values; cnt_stpsPerMove++) {
            player1->par_num_simulatedActions_perMove = config_timeStepsPerMove_values[cnt_stpsPerMove];
            player2->par_num_simulatedActions_perMove = config_timeStepsPerMove_values[cnt_stpsPerMove];

            //compose string
            char experimentName[256];
            sprintf_s(experimentName, "//--  %s : configuration C%d steps%d --//", procedureName, configurationSerialID, config_timeStepsPerMove_values[cnt_stpsPerMove]);

            //execute experiment
            Experiment_SingleGame(game, players, experimentName, xAxisLabel, config_max_num_repeats, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults[configurationSerialID][cnt_stpsPerMove], additionalPar);
          }

          //write results to files
          for (int m = 0; m < results_num_metrics; m++) {
            resultsFilePrinter->PrintI(m + 0, "%s  %5.3f  %5.3f  C%04d_A%01d_a%03d_L%05d  ", printLinePrefix, players[0]->par_task_gamma, players[0]->par_td_alpha, configurationSerialID, 0, (int)(players[0]->par_td_alpha * 100), (int)(players[0]->par_td_lambda * 10000));
            for (int s = 0; s < config_num_timeStepsPerMove_values; s++) {
              resultsFilePrinter->PrintI(m + 0, "  %8.5f", gatheredResults[configurationSerialID][s][m]->mean);
            }
            resultsFilePrinter->PrintI(m + 0, "\n");
          }
        }

      }
    }

    //---- end of experiments ----//

    //-- clean up
    delete(resultsFilePrinter);
    for (int c = config_IndexStart; c <= config_IndexEnd; c++) {
      for (int s = 0; s < config_num_timeStepsPerMove_values; s++) {
        for (int m = 0; m < results_num_metrics; m++) {
          delete(gatheredResults[c][s][m]);
        }
        delete[] gatheredResults[c][s];
      }
      delete[] gatheredResults[c];
    }
    delete[] gatheredResults;
    delete(player1);
    delete(player2);
    delete(game);

  }


  void Experiment_SingleGame(
    Game_Engine* game,
    Player_AI_RL** players,
    char* experimentName,
    char* xAxisLabel,
    int num_repeats,
    int show_per_repeat_output,
    double config_confidenceInterval,
    bool show_final_output,
    Tool_Sample_Storage** externalStorage,
    double additionalPar
    )
  {

    //-- config
    int evaluatedPlayerPosition = 0;	// valid 0 or 1, regarding to (Player_AI_RL** players)


                                      //// apply settings
    game->Settings_Apply_Changes();
    for (int p = 0; p < game->number_players; p++)
      players[p]->Apply_Settings();

    //initial output
    gmp->Print("\n%s\n", experimentName);
    game->Output_Settings();
    for (int p = 0; p < game->number_players; p++) {
      gmp->Print("\nPlayer %d", p + 1);
      players[p]->Output_Settings();
    }

    //prepare storage
    int results_num_metrics = Player_AI_RL::experimentNumMetrics[players[0]->config_experiment];
    Tool_Sample_Storage** results;
    if (externalStorage == NULL) {
      results = new Tool_Sample_Storage*[results_num_metrics];
      for (int j = 0; j < results_num_metrics; j++) {
        results[j] = new Tool_Sample_Storage(0);		//do not store individual samples, but compute only descriptive statistics (online)
      }
    }
    else {
      results = externalStorage;
    }

    //prepare timers		
    double* times = new double[2];
    players[0]->experiment_timers = times;

    //experiment starting time
    times[0] = getCPUTime();

    //prepare temporary storage for function Evaluate_Players()
    double* lastWinCounts = new double[3];

    //execute experiments (with initial positions)
    Player_Engine* positionedPlayers[2];
    game->players = positionedPlayers;
    positionedPlayers[0] = players[0];
    positionedPlayers[1] = players[1];

    // FOR THE 2017.02.05 EXPERIMENTS

        //Debug: test with UCT player (first implementation): evaluated player
        Player_AI_UCT* UCTplayerSelf = new Player_AI_UCT(game);
        UCTplayerSelf->UCT_param_IterNum = players[0]->par_num_simulatedActions_perMove;
        UCTplayerSelf->UCT_param_SimMoveNum = players[0]->par_num_simulatedActions_perMove;
        UCTplayerSelf->UCT_param_C = players[0]->par_ucb_c / 2.0;

        //Debug: test with UCT player (first implementation) + AMAF: evaluated player
        Player_AI_UCT_AMAF* AMAFplayerSelf = new Player_AI_UCT_AMAF(game);
        AMAFplayerSelf->UCT_param_IterNum = players[0]->par_num_simulatedActions_perMove;
        AMAFplayerSelf->UCT_param_SimMoveNum = players[0]->par_num_simulatedActions_perMove;
        AMAFplayerSelf->UCT_param_C = players[0]->par_ucb_c / 2.0;

        //Debug: test with UCT player (first implementation) + RAVE: evaluated player
        Player_AI_UCT_RAVE* RAVEplayerSelf = new Player_AI_UCT_RAVE(game);
        RAVEplayerSelf->UCT_param_IterNum = players[0]->par_num_simulatedActions_perMove;
        RAVEplayerSelf->UCT_param_SimMoveNum = players[0]->par_num_simulatedActions_perMove;
        RAVEplayerSelf->UCT_param_C = additionalPar / 2.0;
        RAVEplayerSelf->RAVE_param_V = players[0]->par_ucb_c;

        //Debug: test with UCT player (first implementation) + MAST: evaluated player
        Player_AI_UCT_MAST* MASTplayerSelf = new Player_AI_UCT_MAST(game);
        MASTplayerSelf->UCT_param_IterNum = players[0]->par_num_simulatedActions_perMove;
        MASTplayerSelf->UCT_param_SimMoveNum = players[0]->par_num_simulatedActions_perMove;
        MASTplayerSelf->UCT_param_C = additionalPar / 2.0;
        MASTplayerSelf->MAST_paramT = players[0]->par_ucb_c;

        //Debug: test with UCT player (first implementation): opponent player
        Player_AI_UCT* UCTplayer = new Player_AI_UCT(game);
        UCTplayer->UCT_param_IterNum = players[1]->par_num_simulatedActions_perMove;
        UCTplayer->UCT_param_SimMoveNum = players[1]->par_num_simulatedActions_perMove;
        UCTplayer->UCT_param_C = players[1]->par_ucb_c / 2.0;

        //Debug: test with UCT player (first implementation) + AMAF
        Player_AI_UCT_AMAF* AMAFplayer = new Player_AI_UCT_AMAF(game);
        AMAFplayer->UCT_param_IterNum = players[1]->par_num_simulatedActions_perMove;
        AMAFplayer->UCT_param_SimMoveNum = players[1]->par_num_simulatedActions_perMove;
        AMAFplayer->UCT_param_C = players[1]->par_ucb_c / 2.0;

        //Debug: test with UCT player (first implementation) + RAVE
        Player_AI_UCT_RAVE* RAVEplayer = new Player_AI_UCT_RAVE(game);
        RAVEplayer->UCT_param_IterNum = players[1]->par_num_simulatedActions_perMove;
        RAVEplayer->UCT_param_SimMoveNum = players[1]->par_num_simulatedActions_perMove;
        RAVEplayer->UCT_param_C = players[1]->par_ucb_c / 2.0;
        RAVEplayer->RAVE_param_V = additionalPar;

        //Debug: test with UCT player (first implementation) + MAST
        Player_AI_UCT_MAST* MASTplayer = new Player_AI_UCT_MAST(game);
        MASTplayer->UCT_param_IterNum = players[1]->par_num_simulatedActions_perMove;
        MASTplayer->UCT_param_SimMoveNum = players[1]->par_num_simulatedActions_perMove;
        MASTplayer->UCT_param_C = players[1]->par_ucb_c / 2.0;
        MASTplayer->MAST_paramT = additionalPar;

        // swap the Sarsa-UCT algorithms with some other (defined above)
        //positionedPlayers[0] = UCTplayerSelf;
        //positionedPlayers[0] = AMAFplayerSelf;
        //positionedPlayers[0] = RAVEplayerSelf;
        //positionedPlayers[0] = MASTplayerSelf;
        //positionedPlayers[1] = UCTplayer;
        //positionedPlayers[1] = AMAFplayer;
        //positionedPlayers[1] = RAVEplayer;
        //positionedPlayers[1] = MASTplayer;
        //
        // FOR FUN:
        //players[0]->config_alpha_type = Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT;
        //players[0]->par_td_alpha = players[0]->par_td_lambda;
        //players[0]->par_td_lambda = 0.99;

    // FOR THE 2017-02-28 EXPERIMENTS
        //((Player_AI_RL*)(positionedPlayers[0]))->config_MASTenable = 1;
        //((Player_AI_RL*)(positionedPlayers[0]))->config_MAST_paramT = additionalPar;

        //positionedPlayers[1] = UCTplayer;
        //((Player_AI_RL*)(positionedPlayers[1]))->config_MASTenable = 1;
        //((Player_AI_RL*)(positionedPlayers[1]))->config_MAST_paramT = additionalPar;

        //((Player_AI_RL*)(positionedPlayers[0]))->config_MASTenable = 3;

    // 2017-02-28 END

    game->Evaluate_Players(num_repeats, 1, -1, positionedPlayers, 0, 0, NULL, 0, 0, lastWinCounts);

    results[0]->Add_Sample((lastWinCounts[0] * 0.5 + lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins + draws
    results[1]->Add_Sample((lastWinCounts[0] * 0.5 + lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins + draws

    results[3]->Add_Sample((lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins
    results[4]->Add_Sample((lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins

    results[6]->Add_Sample((lastWinCounts[0]) / (double)num_repeats);	// draws
    results[7]->Add_Sample((lastWinCounts[0]) / (double)num_repeats);	// draws

                                                                      //execute experiments (swap positions)
    evaluatedPlayerPosition = 1 - evaluatedPlayerPosition;
    Player_Engine* tmpP;
    tmpP = positionedPlayers[0];
    positionedPlayers[0] = positionedPlayers[1];
    positionedPlayers[1] = tmpP;
    game->Evaluate_Players(num_repeats, 1, -1, positionedPlayers, 0, 0, NULL, 0, 0, lastWinCounts);

    results[0]->Add_Sample((lastWinCounts[0] * 0.5 + lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins + draws
    results[2]->Add_Sample((lastWinCounts[0] * 0.5 + lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins + draws

    results[3]->Add_Sample((lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins
    results[5]->Add_Sample((lastWinCounts[evaluatedPlayerPosition + 1]) / (double)num_repeats);	// wins

    results[6]->Add_Sample((lastWinCounts[0]) / (double)num_repeats);	// draws
    results[8]->Add_Sample((lastWinCounts[0]) / (double)num_repeats);	// draws

                                                                      //prepare results for output
    for (int j = 0; j < results_num_metrics; j++) {
      ////the sum and mean should have already been calculated in Player_AI_RL->Get_Move()
      ////results[j][i]->Calc_Sum();
      ////results[j][i]->Calc_Mean();
      //results[j]->Calc_Confidence(config_confidenceInterval);
    }

    //final output
    if (show_final_output) {
      gmp->Print("\n\nFinal results after %d repeats:\n\n", num_repeats);
      gmp->Print("        .");
      gmp->Print("    ");
      gmp->Print(" Mean(s)");
      for (int j = 0; j < results_num_metrics - 1; j++)
        gmp->Print("       .");
      //gmp->Print("    ");
      //gmp->Print("  Conf95");
      //for (int j = 0; j < results_num_metrics - 1; j++)
      //	gmp->Print("       .");
      gmp->Print("\n\n");
      gmp->Print(" %s", xAxisLabel);
      gmp->Print("    ");
      for (int j = 0; j < results_num_metrics; j++)
        gmp->Print("  %s", Player_AI_RL::experimentLabels[players[0]->config_experiment][j]);
      //gmp->Print("    ");
      //for (int j = 0; j < results_num_metrics; j++)
      //	gmp->Print("  %s", Player_AI_RL::experimentLabels[players[0]->config_experiment][j]);
      gmp->Print("\n");
      gmp->Print(" %8d", players[0]->par_num_simulatedActions_perMove);
      gmp->Print("    ");
      gmp->Print("  %6.3f", results[0]->mean);
      for (int j = 1; j < results_num_metrics; j++)
        gmp->Print("  %6.4f", results[j]->mean);
      //gmp->Print("    ");
      //for (int j = 0; j < results_num_metrics; j++)
      //	gmp->Print("  %6.4f", results[j]->conf);
      //gmp->Print("\n");
    }
    gmp->Print("\n%s --- ENDED --- repeats %d, runtime: %9.3f s\n", experimentName, num_repeats, getCPUTime() - times[0]);

    //clean up
    if (externalStorage == NULL) {
      for (int j = 0; j < results_num_metrics; j++) {
        delete(results[j]);
      }
      delete[] results;
    }
    delete[] times;
    delete[] lastWinCounts;
  }

}