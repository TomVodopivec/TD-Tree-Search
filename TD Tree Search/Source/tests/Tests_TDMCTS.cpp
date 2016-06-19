#include "Tests_TDMCTS.hpp"

namespace Tests_TDMCTS
{

	void main()
	{

		//srand(1422916216);
		//srand(1423134958);

		//Tests_TDMCTS::UnitTest_RandomWalk();
		//Tests_TDMCTS::UnitTest_PlayerRL();
		//Tests_TDMCTS::UnitTest_Two_PlayerRL();
		//Tests_TDMCTS::Fixed_Play_Testing();
		//Tests_TDMCTS::UnitTest_PlayerRL_singleMove();

		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode();
		//Tests_TDMCTS::Experiment_RandomWalk_perTimeStep();

		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch();		


		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_negativeStep_episodes10k();
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_DEBUG_rollout_assumptions_equality_RW21();
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_initialValues();
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_numNewNodes();
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW_differentLengths();



		//// (finished 2015.03.08) measurements for Experiment1 : randomWalk with final reward 1 (or with negative reward -1 at each step), random policy, measurements per episode
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch(0, 1151);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch(1152,2015);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch(2016,2591);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch(2592,2879);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_DifferentInitialValues();
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_LambdaSensitivity100(0, 4544);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_LambdaSensitivity100(4545, 6059);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_LambdaSensitivity100(6060, 7575);
		//Tests_TDMCTS::Experiment_RandomWalk_perEpisode_Batch_stepNegativeReward();

		// measuerements for Experiment2 : randomWalk with negative reward -1 at each step, epsilon-greedy policy, measurements per step
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_Batch(0, 179);
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_Batch(180, 329);
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_Batch(330, 449);
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_Batch(450, 539);
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_Batch(540, 599);
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_Batch_LambdaSensitivity100();

		// measuerements for Experiment3 : randomWalk with negative reward -1 at each step, UCB1 policy, measurements per step
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(0,1359);		//approximately 3 days of computation
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(1360,2719);	//approximately 3 days of computation
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(2720,4079);	//approximately 3 days of computation
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(4080,5439);	//approximately 3 days of computation
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(5440,6799);	//approximately 3 days of computation
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(6800,8159);	//approximately 3 days of computation
		//Tests_TDMCTS::Experiment_RandomWalk_perStep_BatchUCB(8160, 16319);	//UCB with decreasing C -> approximately 17 days of computation

		// measuerements for Experiment4 : Tic Tac Toe, two-player adversary classic game
		//		- learning with self-play
		//		- building a minmax tree
		//		- planning
		//		- limited computation budged (number of timesteps)
		//		- retaining memorized values (tree) between external moves (so, tree is not deleted after each move)
		//	control variables : lambda, own_ucb_C, opponent ucb_C, computational budget of num timesteps (equal for both players)
		//	measured variables : average win rate against an UCT player from a single game, where 50% of games played as player1 and 50% times as player2
		//Tests_TDMCTS::Experiment_TicTacToe_perStep_BatchUCB();

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
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, NULL, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, NULL, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_ConnectFour(), 1000, NULL, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 2000, new Game_ConnectFour(), 10000, NULL, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 500, new Game_ConnectFour(), 50000, NULL, NULL);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 10000, game, 1000, NULL, NULL);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 10000, NULL, NULL);
		//Game_Engine* game = new Game_Hex(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 10000, game, 1000, NULL, NULL);
		//Game_Engine* game = new Game_Hex(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 10000, NULL, NULL);

		// experiment 5.2: find best ucb_C for evaluated UCT player
		e = 2;
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, 0.20, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, 0.35, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_ConnectFour(), 1000, 0.05, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 2000, new Game_ConnectFour(), 10000, 0.20, NULL);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 500, new Game_ConnectFour(), 50000, 0.30, NULL);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 10000, game, 1000, 0.10, NULL);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 10000, 0.15, NULL);
		//Game_Engine* game = new Game_Hex(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 10000, game, 1000, 0.05, NULL);
		//Game_Engine* game = new Game_Hex(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 10000, 0.20, NULL);
		
		// experiment 5.3: find best lambda for evaluated SARSA-UCT player (with global normalization bounds)
		e = 3;
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 100, 0.20, 0.20);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_TicTacToe(), 1000, 0.35, 0.30);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 20000, new Game_ConnectFour(), 1000, 0.05, 0.15);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 2000, new Game_ConnectFour(), 10000, 0.20, 0.20);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 500, new Game_ConnectFour(), 50000, 0.30, 0.25);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 10000, game, 1000, 0.10, 0.05);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 10000, 0.15, 0.20);
		//Game_Engine* game = new Game_Hex(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 10000, game, 1000, 0.05, 0.25);
		//Game_Engine* game = new Game_Hex(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 10000, 0.20, 0.20);

		//PREVERI ÈE 5.4 deluje pravilno ali je to ista zadeva kot 5.3
		// experiment 5.4: find best lambda for evaluated SARSA-UCT player (with local normalization bounds)
		e = 4;
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 5000, new Game_TicTacToe(), 100, 0.20, 0.20);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 5000, new Game_TicTacToe(), 1000, 0.35, 0.35);
		//
		// experiment 5.5: find best lambda and ucb_C for evaluated SARSA-UCT player (with local normalization bounds)
		e = 5;
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, new Game_TicTacToe(), 100, 0.20, NULL);
		// ??? experiment 5.6: poskusi optimizirat tudi gamma(ampak mislim da rabim kakšen drugi assumption potem)

		// experiment 5.6debug: debug why SARSA-UCT(1) performs differently than UCT
		e = 6;
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(6, 1000, new Game_ConnectFour(), 1000, 0.15, 0.15, 0.7);
		//Game_Engine* game = new Game_Gomoku(); game->board_length = 7; game->board_height = 7; game->Settings_Apply_Changes(); Tests_TDMCTS::Experiment5_perStep_BatchUCB(e, 1000, game, 1000, 0.1, 0.1);
		//Tests_TDMCTS::Experiment5_perStep_BatchUCB(6, 1, new Game_TicTacToe(), 100, 0.2, 0.2, 1.0);

		//PREVERI èe se 5.3 performase pri ta boljših lambda ujemajo tudi proti original implementaciji UCT
		//	-> se ne ujemajo, original UCT je bistveno boljši od SARSA-UCT -> ugotovi zakaj!
		//		?drugaèna normalizacija, fiksiraj število epizod in ne korakov, ali je mogoèe to ? )
		//		* ali izvede veèje število iteracij?
		//		* ali je kaj narobe z two-player drevesom pri SARSA-UCT?


	}

	//currently this experiment measures the performance of FVMC and TD(lamdba) under several control variables for a total of 2880 different configurations
	void Experiment_RandomWalk_perEpisode_Batch(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch()";
		char* xAxisLabel = " episode";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations = 
			1 * 5 * 3 * 
			( 1 * 2 * 1 * 6 
			+ 3 * 2 * 5 * 6
			);	// = 2880

		int config_max_num_episodes = 100;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxActions = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl Qin nn tn ra al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different game definitions (different reward functions)
		for (int gd = 0; gd < 1; gd++){
			if (gd == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (gd == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 0; wl < 5; wl++){
				if (wl == 0){
					config_walk_length = 5;
				}
				else if (wl == 1){
					config_walk_length = 7;
				}
				else if (wl == 2){
					config_walk_length = 11;
				}
				else if (wl == 3){
					config_walk_length = 15;
				}
				else{
					config_walk_length = 21;
				}
				par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				maximum_plys = 10000;

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different initial values
				for (int qi = 0; qi < 3; qi++){
					if (qi == 0){
						par_td_initVal = 0.0;
					}
					else if (qi == 1){
						par_td_initVal = -0.5;
					}
					else{
						par_td_initVal = 0.5;
					}

					//different number of added nodes per episode (UCT behaviour)
					for (int nn = 0; nn < 4; nn++){
						int raMax;
						if (nn == 0){
							config_num_new_nodes_per_episode = -1;
							raMax = 1;
						}
						else if (nn == 1){
							config_num_new_nodes_per_episode = 1;
							raMax = 5;
						}
						else if (nn == 2){
							config_num_new_nodes_per_episode = 5;
							raMax = 5;
						}
						else{
							config_num_new_nodes_per_episode = 10;
							raMax = 5;
						}

						//with/without transpositions
						for (int tn = 0; tn < 2; tn++){
							if (tn == 0){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
							}
							else{
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							}

							//different rollout assumptions						
							for (int ra = 0; ra < raMax; ra++){
								if (ra == 0){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
								}
								else if (ra == 1){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
								}
								else if (ra == 2){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
								}
								else if (ra == 3){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
								}
								else{
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
								}


								//-//-// single set of different algorithms

								sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2s %2s", gd, config_walk_length, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption]);

								//--- Episodic
								config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;


								//-- Exponential step rate by state-visits
								config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

								//- First-visit MC
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//- Episodic TD(lambda) with exponential alpha by state-visits
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);


								////-- Constant step rate
								//config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT;

								////- Constant-alpha MC
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								////- Episodic TD(lambda) with constant alpha
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//-//-//

							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		//for (int c = config_IndexStart; c <= config_IndexEnd; c++){
		//	for (int m = 0; m < results_num_metrics; m++){
		//		if (gatheredResults[c][m] != NULL){
		//			for (int s = 0; s < config_max_num_episodes + 1; s++)
		//				delete[] gatheredResults[c][m][s];
		//			delete[] gatheredResults[c][m];
		//		}
		//	}
		//	delete[] gatheredResults[c];
		//}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}

	void Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(
		int* address_configurationSerialID,
		int algorithmSerialID,
		int num_repeats,
		int config_walk_length,
		int maximum_plys,
		int par_num_episodes,
		double par_td_initVal,
		double par_td_alpha,
		double par_td_lambda,
		Player_AI_RL::PRESET_ALGORITHMS::TYPE config_preset_algorithm,
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType,
		Player_AI_RL::ELIGIBILITY_TRACES::TYPE config_trace_type,
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alpha_type,
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions,
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption,
		int config_num_new_nodes_per_episode,
		Game_RandomWalk* game,
		Player_AI_RL* player,
		char* experimentName,
		char* xAxisLabel,
		int show_per_repeat_output,
		double config_confidenceInterval,
		bool config_show_individual_final_output,
		Tool_Sample_Storage**** gatheredResults,
		MultiPrinter* resultsFilePrinter,
		char* printLinePrefix,
		int config_IndexStart,
		int config_IndexEnd
		)
	{

		// increase external counter
		(*address_configurationSerialID)++;
		int configurationSerialID = (*address_configurationSerialID) - 1;

		//consider the execution settings
		if ((configurationSerialID < config_IndexStart) || (configurationSerialID > config_IndexEnd) || (config_IndexEnd < config_IndexStart))
			return;

		//// apply controlled parameter values
		game->config_walk_length = config_walk_length;
		game->maximum_plys = maximum_plys;
		player->par_num_episodes = par_num_episodes;
		player->config_preset_algorithm = config_preset_algorithm;
		player->par_td_lambda = par_td_lambda;
		player->par_td_alpha = par_td_alpha;
		player->par_td_initVal = par_td_initVal;
		player->config_TDupdateType = config_TDupdateType;
		player->config_trace_type = config_trace_type;
		player->config_alpha_type = config_alpha_type;
		player->config_transpositions = config_transpositions;
		player->config_rollout_assumption = config_rollout_assumption;
		player->config_num_new_nodes_per_episode = config_num_new_nodes_per_episode;

		//compose string
		char procedureName[256];
		sprintf_s(procedureName, "//--  %s : configuration C%d  --//", experimentName, configurationSerialID);

		//prepare temporary storage
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];
		int results_num_steps;
		if (par_num_episodes >= 0)
			results_num_steps = par_num_episodes + 1;
		else
			results_num_steps = player->par_num_simulatedActions_perMove + 1;
		for (int m = 0; m < results_num_metrics; m++){
			gatheredResults[configurationSerialID][m] = new Tool_Sample_Storage*[results_num_steps];
			for (int s = 0; s < results_num_steps; s++)
				gatheredResults[configurationSerialID][m][s] = new Tool_Sample_Storage(0);	//do not store individual samples, but compute only descriptive statistics (online)
		}

		//execute experiment
		Experiment_SingleExternalMove(game, player, procedureName, xAxisLabel, num_repeats, show_per_repeat_output, results_num_steps, config_confidenceInterval, config_show_individual_final_output, gatheredResults[configurationSerialID]);

		//write results to files
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->PrintI(2 * m + 0, "%s %2d  %5.3f  %5.3f  %5.3f  C%04d_A%02d_a%03d_L%03d  ", printLinePrefix, algorithmSerialID, player->par_task_gamma, player->par_td_alpha, player->par_td_lambda, configurationSerialID, algorithmSerialID, (int)(player->par_td_alpha * 100), (int)(player->par_td_lambda * 100));
			resultsFilePrinter->PrintI(2 * m + 1, "%s %2d  %5.3f  %5.3f  %5.3f  C%04d_A%02d_a%03d_L%03d  ", printLinePrefix, algorithmSerialID, player->par_task_gamma, player->par_td_alpha, player->par_td_lambda, configurationSerialID, algorithmSerialID, (int)(player->par_td_alpha * 100), (int)(player->par_td_lambda * 100));
			for (int s = 0; s < results_num_steps; s++){
				resultsFilePrinter->PrintI(2 * m + 0, "  %8.5f", gatheredResults[configurationSerialID][m][s]->mean);
				resultsFilePrinter->PrintI(2 * m + 1, "  %8.5f", gatheredResults[configurationSerialID][m][s]->conf);
			}
			resultsFilePrinter->PrintI(2 * m + 0, "\n");
			resultsFilePrinter->PrintI(2 * m + 1, "\n");
		}

		//clear temporary and external storage
		for (int m = 0; m < results_num_metrics; m++){
			for (int s = 0; s < results_num_steps; s++)
				delete(gatheredResults[configurationSerialID][m][s]);
			delete[] gatheredResults[configurationSerialID][m];
		}
		delete[] gatheredResults[configurationSerialID];
	}

	void Experiment_RandomWalk_perStep_Batch(int startIndex, int endIndex, int useUCB)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 0;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ----//

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_TIMESTEPS;
		char* procedureName = "Experiment_RandomWalk_perStep_Batch()";
		char* xAxisLabel = " timStep";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations =
			1 * 5 * 2 * 2 * 1 *
			( 3 * 6
			+ 2 * 6
			);	// = 600

		int config_max_num_timeSteps = 10000;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 0.1;
		player->par_ucb_c = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = config_max_num_timeSteps;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
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
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\n%s\n", procedureName);
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl cp cPar Qin nn tn ra al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_timeSteps + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_simulated_actions;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different game definitions (different reward functions)
		for (int gd = 1; gd < 2; gd++){
			if (gd == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (gd == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 0; wl < 5; wl++){
				if (wl == 0){
					config_walk_length = 5;
				}
				else if (wl == 1){
					config_walk_length = 7;
				}
				else if (wl == 2){
					config_walk_length = 11;
				}
				else if (wl == 3){
					config_walk_length = 15;
				}
				else{
					config_walk_length = 21;
				}
				par_num_simulated_actions = config_max_num_timeSteps;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				maximum_plys = 10000;
				if (gd == 0){
					game->maxScore = 1.0;
					game->minScore = 0.0;
				}
				else{
					game->maxScore = -(config_walk_length - 1) / 2;
					game->minScore = -(game->maximum_plys);
				}

				//safety checks
				if (par_num_simulated_actions > config_max_num_timeSteps){
					gmp->Print("ERROR: %s: par_num_episodes > config_max_num_episodes\n", procedureName);
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: %s: num_repeats > config_max_num_repeats\n", procedureName);
					return;
				}

				//different control policy settings
				if (useUCB == 0){
					player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;
				}
				else{
					player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::UCB1;
				}
				for (int cpp = 0; cpp < 2; cpp++){
					if (cpp == 0){
						player->par_egreedy_e = 0.1;
						player->par_ucb_c = 1.0;
						player->config_ExplorationLinear_maxActions = 0;
					}
					else{
						player->par_egreedy_e = 0.1;
						player->par_ucb_c = 1.0;
						player->config_ExplorationLinear_maxActions = config_max_num_timeSteps;
					}
					double policyPar;
					if (player->config_control_policy == Player_AI_RL::CONTROL_POLICIES::EGREEDY)
						policyPar = player->par_egreedy_e;
					else if (player->config_control_policy == Player_AI_RL::CONTROL_POLICIES::UCB1)
						policyPar = player->par_ucb_c;

					//different initial values
					for (int qi = 0; qi < 2; qi++){
						if (qi == 0){
							par_td_initVal = 0.0;
						}
						else{
							par_td_initVal = (game->maxScore - game->param_score_draw);
						}

						//different number of added nodes per episode (UCT behaviour)
						for (int nn = 1; nn < 2; nn++){
							int raMax;
							if (nn == 0){
								config_num_new_nodes_per_episode = -1;
								raMax = 1;
							}
							else if (nn == 1){
								config_num_new_nodes_per_episode = 1;
								raMax = 3;
							}
							else if (nn == 2){
								config_num_new_nodes_per_episode = 5;
								raMax = 3;
							}
							else{
								config_num_new_nodes_per_episode = 10;
								raMax = 3;
							}

							//with/without transpositions
							for (int tn = 0; tn < 2; tn++){
								if (tn == 0){
									config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
								}
								else{
									config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
									if (raMax > 2)
										raMax = 2;
								}

								//different rollout assumptions						
								for (int ra = 0; ra < raMax; ra++){
									if (ra == 0){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
									}
									else if (ra == 1){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
									}
									else if (ra == 2){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
									}
									else if (ra == 3){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
									}
									else{
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
									}

									sprintf_s(printLinePrefix, "  %2d %2d %2d %4.2f %3.1f %2d %2s %2s", gd, config_walk_length, cpp, policyPar, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption]);

									//-//-// single set of different algorithms

									//--- Episodic
									config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;


									//-- Exponential step rate by state-visits
									config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

									//- First-visit MC
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

									//- Episodic TD(lambda) with exponential alpha by state-visits
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);


									////-- Constant step rate
									//config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT;

									////- Constant-alpha MC
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

									////- Episodic TD(lambda) with constant alpha
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
									//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

									//-//-//

								}
							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		//for (int c = config_IndexStart; c <= config_IndexEnd; c++){
		//	for (int m = 0; m < results_num_metrics; m++){
		//		if (gatheredResults[c][m] != NULL){
		//			for (int s = 0; s < config_max_num_timeSteps + 1; s++)
		//				delete[] gatheredResults[c][m][s];
		//			delete[] gatheredResults[c][m];
		//		}
		//	}
		//	delete[] gatheredResults[c];
		//}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}

	void Experiment_RandomWalk_perEpisode()
	{

		//-- declarations and init
		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		Player_Engine* players[] = { player };
		game->players = players;
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode()";
		char* xAxisLabel = "  episode";

		//-- user-defined experimental settings

		// common setting for this experiment (do not comment out)
		Experiment_RandomWalk_perEpisode_CommonSettings(game, player);

		// experiment runtime settings
		int num_repeats = 1000;			// define the number of repeats of the experiments -> only for statistical accuracy
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//// preset algorithm (for details see procedure "Apply_Preset_Config()" in "Player_AI_RL.cpp")
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_MC;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::ONLINE_TD_ZERO_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::EPISODIC_TD_ZERO_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::EVERYVISIT_MC_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC;
		player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;
		player->config_trace_type = Player_AI_RL::ELIGIBILITY_TRACES::REPLACING;
		player->config_alpha_type = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

		//// parameter values (if not already defined by the selected preset algorithm)
		player->par_td_lambda = 0.9995;
		player->par_td_alpha = 0.5;
		player->par_td_initVal = 0.0;
		player->par_num_episodes = 100;

		//-- end of user-defined experimental settings (do not change code below this line unless you know what you are doing)

		//execute experiment
		int results_num_steps = player->par_num_episodes + 1;
		Experiment_SingleExternalMove(game, player, procedureName, xAxisLabel, num_repeats, show_per_repeat_output, results_num_steps);

		//clean up
		delete(player);
		delete(game);
	}

	// 2015.02.05 configurations for experiment #1
	void Experiment_RandomWalk_perEpisode_CommonSettings(Game_RandomWalk* game, Player_AI_RL* player)
	{

		//-- game configuration
		game->config_walk_length = 21;
		game->maximum_plys = 10000;
		game->param_score_win = 1.0;
		game->param_score_lose = 0.0;
		game->param_score_step = 0.0;
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;
		player->config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;

		//// settings not defined by presets
		player->config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
		player->config_num_new_nodes_per_episode = 1;
		player->config_offpolicy_backup_recheck_best = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

	}

	// 2015.02.05 experiment #2: randomWalk, by time steps (simulated actions)
	void Experiment_RandomWalk_perTimeStep()
	{

		//-- declarations and init
		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		Player_Engine* players[] = { player };
		game->players = players;
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_TIMESTEPS;
		char* procedureName = "Experiment_RandomWalk_perTimeStep()";
		char* xAxisLabel = " timeStep";

		//-- user-defined experimental settings

		// common setting for this experiment (do not comment out)
		Experiment_RandomWalk_perTimeStep_CommonSettings(game, player);

		// experiment runtime settings
		int num_repeats = 200;			// define the number of repeats of the experiments -> only for statistical accuracy
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//// preset algorithm (for details see procedure "Apply_Preset_Config()" in "Player_AI_RL.cpp")
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::EPISODIC_MC;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::ONLINE_TD_ZERO_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::EPISODIC_TD_ZERO_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY;
		//player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::EVERYVISIT_MC_ONPOLICY;
		player->config_preset_algorithm = Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA;

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;
		player->config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
		player->config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;
		player->config_trace_type = Player_AI_RL::ELIGIBILITY_TRACES::REPLACING;
		player->config_alpha_type = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

		//// settings not defined by presets
		player->config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
		player->config_num_new_nodes_per_episode = 1;
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxActions = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values (if not already defined by the selected preset algorithm)
		player->par_egreedy_e = 0.10;
		player->par_task_gamma = 1.00;
		player->par_td_lambda = 0.50;
		player->par_td_alpha = 0.15;
		player->par_td_initVal = 0.0;
		player->par_num_simulatedActions_perMove = 500;

		//-- end of user-defined experimental settings (do not change code below this line unless you know what you are doing)

		//execute experiment
		int results_num_steps = player->par_num_simulatedActions_perMove + 1;
		Experiment_SingleExternalMove(game, player, procedureName, xAxisLabel, num_repeats, show_per_repeat_output, results_num_steps);

		//clean up
		delete(player);
		delete(game);
	}

	void Experiment_RandomWalk_perTimeStep_CommonSettings(Game_RandomWalk* game, Player_AI_RL* player)
	{
		//-- game configuration
		game->config_walk_length = 7;
		game->maximum_plys = 10000;
		game->param_score_win = 0.0;
		game->param_score_lose = -1.0;
		game->param_score_step = -1.0;
		game->param_score_draw = 0.0;
		game->maxScore = -(game->config_walk_length - 1) / 2;
		game->minScore = -(game->maximum_plys);

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// parameter values
		player->par_num_episodes = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;
	}

	// 2015.02.05 experiment #1: randomWalk, by episodes
	void Experiment_SingleExternalMove(
		Game_RandomWalk* game,
		Player_AI_RL* player,
		char* experimentName,
		char* xAxisLabel,
		int num_repeats,
		int show_per_repeat_output,
		int results_num_steps,
		double config_confidenceInterval,
		bool show_final_output,
		Tool_Sample_Storage*** externalStorage
		)
	{

		//// apply settings
		game->Settings_Apply_Changes();
		player->Apply_Settings();
		if (player->config_experiment == Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES)
			game->Compute_OptimalStateValues();

		//initial output
		gmp->Print("\n%s\n", experimentName);
		game->Output_Settings();
		player->Output_Settings();

		//prepare storage
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];
		Tool_Sample_Storage*** results;
		if (externalStorage == NULL){
			results = new Tool_Sample_Storage**[results_num_metrics];
			for (int j = 0; j < results_num_metrics; j++){
				results[j] = new Tool_Sample_Storage*[results_num_steps];
				for (int i = 0; i < results_num_steps; i++)
					results[j][i] = new Tool_Sample_Storage(0);		//do not store individual samples, but compute only descriptive statistics (online)
			}
		}
		else{
			results = externalStorage;
		}
		player->experiment_results = results;

		//prepare timers		
		double* times = new double[2];
		player->experiment_timers = times;

		//output header
		if (show_per_repeat_output >= 0){
			gmp->Print("\n");
			gmp->Print("    repeat   time[s]   last[s]  %s\n", xAxisLabel);
			gmp->Print("                              ");
			for (int i = 0; i < results_num_steps; i++)
				gmp->Print("  %5d", i);
		}

		//experiment starting time
		times[0] = getCPUTime();

		//execute experiments
		for (int r = 0; r < num_repeats; r++){
			// last repeat starting time
			times[1] = getCPUTime();

			// reset the game
			game->Game_Reset();

			// reset the player
			player->Reset();

			// execute batch of simulations
			(game->players[game->current_player])->Get_Move();

			// single-repeat output
			if (show_per_repeat_output >= 0){
				gmp->Print("\n  %8d  %8.2f  %8.0f", r + 1, getCPUTime() - times[1], getCPUTime() - times[0]);
				for (int i = 0; i < results_num_steps; i++){
					double printVal;
					if (show_per_repeat_output != 4){
						printVal = results[show_per_repeat_output][i]->mean;
					}
					else{
						if (results[4][i]->mean <= -1)
							printVal = INFINITY;
						else
							printVal = results[4][i]->mean = -results[4][i]->mean / (1.0 - (-results[4][i]->mean)) + 1.0;
					}
					gmp->Print("  %5.3f", printVal);
				}
			}
		}

		//prepare results for output
		for (int i = 0; i < results_num_steps; i++){
			for (int j = 0; j < results_num_metrics; j++){
				////the sum and mean should have already been calculated in Player_AI_RL->Get_Move()
				////results[j][i]->Calc_Sum();
				////results[j][i]->Calc_Mean();
				results[j][i]->Calc_Confidence(config_confidenceInterval);
			}
		}

		//exceptionally in this experimental scenario we alter the metric (average reward in step X)
		for (int i = 0; i < results_num_steps; i++){
			if (results[4][i]->mean <= -1){
				results[4][i]->mean = INFINITY;
				results[4][i]->conf = 0.0;
			}
			else{
				double meanRewStep = results[4][i]->mean;
				results[4][i]->mean = -meanRewStep / (1.0 - (-meanRewStep)) + 1.0;
				results[4][i]->conf = results[4][i]->conf * (results[4][i]->mean / meanRewStep) * (results[4][i]->mean / meanRewStep);	//todo: not sure if that is correct, but for now it's a quick solution: IT IS PROBABLY WAY TO LARGE (not sure tho') :P
			}
		}

		//final output
		if (show_final_output){
			gmp->Print("\n\nFinal results after %d repeats:\n\n", num_repeats);
			gmp->Print("        .");
			gmp->Print("    ");
			gmp->Print(" Mean(s)");
			for (int j = 0; j < results_num_metrics - 1; j++)
				gmp->Print("       .");
			gmp->Print("    ");
			gmp->Print("  Conf95");
			for (int j = 0; j < results_num_metrics - 1; j++)
				gmp->Print("       .");
			gmp->Print("\n\n");
			gmp->Print("%s", xAxisLabel);
			gmp->Print("    ");
			for (int j = 0; j < results_num_metrics; j++)
				gmp->Print("  %s", Player_AI_RL::experimentLabels[player->config_experiment][j]);
			gmp->Print("    ");
			for (int j = 0; j < results_num_metrics; j++)
				gmp->Print("  %s", Player_AI_RL::experimentLabels[player->config_experiment][j]);
			gmp->Print("\n");
			for (int i = 0; i < results_num_steps; i++){
				gmp->Print(" %8d", i);
				gmp->Print("    ");
				gmp->Print("  %6.3f", results[0][i]->mean);
				for (int j = 1; j < results_num_metrics; j++)
					gmp->Print("  %6.4f", results[j][i]->mean);
				gmp->Print("    ");
				for (int j = 0; j < results_num_metrics; j++)
					gmp->Print("  %6.4f", results[j][i]->conf);
				gmp->Print("\n");
			}
		}
		gmp->Print("\n%s --- ENDED --- repeats %d, runtime: %9.3f s\n", experimentName, num_repeats, getCPUTime() - times[0]);

		//clean up
		if (externalStorage == NULL){
			for (int j = 0; j < results_num_metrics; j++){
				for (int i = 0; i < results_num_steps; i++)
					delete(results[j][i]);
				delete(results[j]);
			}
			delete[] results;
		}
		delete[] times;

	}


	void UnitTest_PlayerRL_singleMove()
	{
		//declaration
		Game_Engine* game = new Game_RandomWalk();
		//Player_Engine* player[] = { new Player_AI_UCT(game) };
		//Player_Engine* player[] = { new Player_Random(game) };
		Player_Engine* player[] = { new Player_AI_RL(game) };
		game->players = player;

		//init
		player[0]->Reset();
		player[0]->player_number = 0;
		game->Game_Reset();

		player[0]->Output_Settings();
		//get single move
		(game->players[game->current_player])->Get_Move();

		//final check
		player[0]->Reset();
	}

	void UnitTest_Two_PlayerRL()
	{
		//declaration
		Game_Engine* game = new Game_TicTacToe();
		//Player_Engine* players[] = { new Player_AI_UCT(game), new Player_AI_UCT(game) };
		Player_Engine* players[] = { new Player_AI_UCT(game), new Player_AI_RL(game) };
		game->players = players;

		//test #3
		players[0]->Reset();
		players[1]->Reset();
		players[1]->Output_Settings();
		((Player_AI_UCT*)(players[0]))->UCT_param_IterNum = 100;
		((Player_AI_RL*)(players[1]))->par_num_episodes = 100;
		game->Simulate_Output_Game();
		players[0]->Reset();
		players[1]->Reset();
	}

	void UnitTest_PlayerRL()
	{
		//declaration
		Game_Engine* game = new Game_RandomWalk();
		//Player_Engine* player[] = { new Player_AI_UCT(game) };
		//Player_Engine* player[] = { new Player_Random(game) };
		Player_Engine* player[] = { new Player_AI_RL(game) };
		game->players = player;

		//test #1
		player[0]->Reset();
		player[0]->player_number = 0;
		game->Game_Reset();
		game->Simulate_Output_Game();
		player[0]->Reset();

		////test #2
		//((Player_AI_RL*)player[0])->config_control_policy = Player_AI_RL::CONTROL_POLICIES::UCB1;
		//((Player_AI_RL*)player[0])->config_policy_evaluation = Player_AI_RL::EVALUATION_TYPES::EVALUATION_WATKINS_Q_LAMBDA;
		//((Player_AI_RL*)player[0])->config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
		//((Player_AI_RL*)player[0])->config_onlineUpdates = 0;
		//((Player_AI_RL*)player[0])->config_nonEpisodicTasks_updateInterval = 200;
		//((Player_AI_RL*)player[0])->config_num_new_nodes_per_episode = 10;
		//((Player_AI_RL*)player[0])->config_opponent_alignment = Player_AI_RL::OPPONENT_ALIGNMENTS::COOPERATIVE;
		//((Player_AI_RL*)player[0])->config_opponent_policy = Player_AI_RL::OPPONENT_POLICIES::SELFPLAY;
		//((Player_AI_RL*)player[0])->config_trace_type = Player_AI_RL::ELIGIBILITY_TRACES::ACCUMULATING;
		//((Player_AI_RL*)player[0])->config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::INITIAL_VALUE;
		//((Player_AI_RL*)player[0])->par_egreedy_e = 0.35;
		//((Player_AI_RL*)player[0])->par_ucb_c = 0.35;
		//((Player_AI_RL*)player[0])->par_gamma = 0.875;
		//((Player_AI_RL*)player[0])->par_td_alpha = 0.175;
		//((Player_AI_RL*)player[0])->par_td_lambda = 0.564;
		//((Player_AI_RL*)player[0])->par_td_initVal = 0.475;
		//((Player_AI_RL*)player[0])->par_initNormMin = 1;
		//((Player_AI_RL*)player[0])->par_initNormMax = -1;
		//((Player_AI_RL*)player[0])->par_num_episodes = 50;
		//((Player_AI_RL*)player[0])->memory_limit = (double)2.0 * (1 << 30);
		//player[0]->Apply_Settings();

		//game->maximum_plys = 30;
		//game->param_score_draw = -5.0;
		//game->param_score_win = 0.5;
		//game->param_score_lose = -5.0;
		//((Game_RandomWalk*)game)->param_score_step = -1.0;
		//game->Settings_Apply_Changes();

		//game->Game_Reset();
		//game->Simulate_Output_Game();
		//game->Game_Reset();
		//player[0]->Reset();
	}

	void UnitTest_RandomWalk()
	{
		Game_Engine* walk = new Game_RandomWalk();
		Player_Engine* player[] = { new Player_Human(walk) };
		walk->players = player;

		player[0]->Reset();
		player[0]->player_number = 0;	//assign player number (must be in same order as in array player[]; must recode this better in new version)
		walk->Game_Reset();
		walk->Simulate_Output_Game();
	}

	void Fixed_Play_Testing(double input_param1, double input_param2)
	{

		//--- SET GAME AND PLAYERS HERE ---//

		//Game_Engine* game = new Game_ConnectFour();
		//Game_Engine* game = new Game_Gomoku();
		Game_Engine* game = new Game_TicTacToe();
		//Game_Engine* game = new Game_Hex();

		////variable board size
		//if(input_param1 > 0){
		//	game->board_length = (int)input_param1;
		//	game->board_height = (int)input_param1;
		//	game->board_size = game->board_length * game->board_height;
		//	game->maximum_allowed_moves = game->board_size;
		//	game->maximum_plys = game->board_size;
		//	game->Settings_Apply_Changes();
		//}

		Player_Engine* players[2];

		Player_AI_UCT* opponent = new Player_AI_UCT(game);
		//Player_AI_UCT* benchmarkOpponent = new Player_AI_UCT(game);

		//Player_AI_UCT* evaluated = new Player_AI_UCT(game);
		Player_AI_RL* evaluated = new Player_AI_RL(game);
		Player_AI_TDUCT* benchmarkEvaluated = new Player_AI_TDUCT(game);

		//Player_AI_UCT_TomTest* evaluated = new Player_AI_UCT_TomTest();
		//Player_AI_UCT_TomTest* benchmarkEvaluated = new Player_AI_UCT_TomTest();

		//--- pre-init (no need to change this) ---//

		Tom_Function_Approximator* funcApp1 = new Tom_Function_Approximator();
		funcApp1->Initialize();
		funcApp1->num_results = TOMPLAYER_AI_UCT_TOMTEST_FUNC_APPROX_NUM_PARAMS;
		funcApp1->Settings_Apply_New();

		//evaluated->Func_App_UCT_Params = funcApp1;
		evaluated->game = game;
		benchmarkEvaluated->Func_App_UCT_Params = funcApp1;
		benchmarkEvaluated->game = game;

		//evaluated->Initialize();
		benchmarkEvaluated->Initialize();
		//evaluated->Output_Log_Level_Create_Headers();

		//--- SET BENCHMARK PARAMETERS HERE ---//

		int repeats = 20000;
		//1000000, 95% confidence that true value deviates less by 0.1%
		//200000,  95% confidence that true value deviates less by 0.3%
		//20000,   95% confidence that true value deviates less by 1%
		//5000,    95% confidence that true value deviates less by 2%
		//1200,    95% confidence that true value deviates less by 4%

		int eval_player_position = 1;			//which player to test: 0 or 1; works only for two-player games
		int benchmark_same_player = 0;
		//0 - disabled (default)
		//1 - benchmark "opponent" vs "opponent"
		//2 - benchmark "evaluated" vs "evaluated"
		int human_opponent_override = 0;
		//0 - disabled (default)
		//1 - replace opponent AI player with human input and output game state after every move
		int display_output_game = 0;	//display single output game regardless of human or AI opponent
		int measure_time_per_move = 0;	//output time per move for each player at end of evaluation procedure
		int output_interval_repeats = (int)(sqrt(repeats));	//output interval of average values from evaluation function (0 = disabled)
		//int output_interval_repeats = 0;

		//--- SET PLAYERS PARAMETERS HERE ---//

		////opponent->UCT_param_IterNum = (int)input_param1;
		opponent->UCT_param_IterNum = 100;
		//opponent->UCT_param_C = 0.2;
		////evaluated->UCT_param_IterNum = (int)input_param1;
		////evaluated->UCT_param_IterNum = (int)input_param2;
		//evaluated->UCT_param_IterNum = 100;
		//evaluated->UCT_param_C = 0.2;//0.5/sqrt(2);

		//2015.01.26 Player_AI_RL first tests
		evaluated->par_num_episodes = 100;



		//////2014_12_19 TTT 10iter UCT vs TDUCT ~ 41% win rate TDUCT as P2
		//opponent->UCT_param_IterNum = 10;
		//opponent->UCT_param_C = 0.2;
		//evaluated->UCT_param_IterNum = 10;
		//evaluated->UCT_param_C = 0.0119;
		//evaluated->QVALUE_param_scoreWeight = 0.7900;
		//evaluated->QVALUE_param_alpha = 1.9152;
		//evaluated->QVALUE_param_gamma = 0.2351;
		//evaluated->QVALUE_param_lambda = 1.4491;
		//evaluated->QVALUE_param_initVal = 0.0;

		//---execute testing---//

		//benchmarkOpponent->UCT_param_IterNum = opponent->UCT_param_IterNum;
		//benchmarkOpponent->UCT_param_C = opponent->UCT_param_C;
		//benchmarkEvaluated->UCT_param_IterNum = evaluated->UCT_param_IterNum;
		//benchmarkEvaluated->UCT_param_C = evaluated->UCT_param_C;
		////TODO copy all new Qval params to benchmarkEvaluated

		players[1 - eval_player_position] = opponent;
		players[eval_player_position] = evaluated;

		//setup result storage
		Tom_Sample_Storage<double>* score[2];

		gmp->Print("Fixed_Play_Testing()\n");
		gmp->Print("%s repeats %d (input params %3.3lf %3.3lf)\n", (game->game_name).c_str(), repeats, input_param1, input_param2);
		//		gmp->Print("Evaluated player %d sim %d\n", eval_player_position + 1, evaluated->UCT_param_IterNum);


		if ((display_output_game == 0) && (human_opponent_override == 0)){

			gmp->Print("Opponent C %3.3f, sim %d\n", opponent->UCT_param_C, opponent->UCT_param_IterNum);
			gmp->Print("\n");
			gmp->Print("        Score[%%]\n");
			gmp->Print(" Repeats     Avg  Conf95     Dev Runtime[s]\n");

			score[0] = new Tom_Sample_Storage<double>(repeats);
			score[1] = new Tom_Sample_Storage<double>(repeats);

			double cpu_time = getCPUTime();

			if (benchmark_same_player == 0){
				game->Evaluate_Players(1, repeats, -1, players, false, eval_player_position, score, output_interval_repeats, measure_time_per_move);
			}
			else if (benchmark_same_player == 1){
				gmp->Print("! benchmark_same_player = opponent vs opponent !\n");
				//players[eval_player_position] = benchmarkOpponent;
				game->Evaluate_Players(1, repeats, -1, players, false, eval_player_position, score, output_interval_repeats, measure_time_per_move);
			}
			else if (benchmark_same_player == 2){
				gmp->Print("! benchmark_same_player = evaluated vs evaluated !\n");
				players[1 - eval_player_position] = benchmarkEvaluated;
				game->Evaluate_Players(1, repeats, -1, players, false, eval_player_position, score, output_interval_repeats, measure_time_per_move);
			}

			cpu_time = getCPUTime() - cpu_time;

			gmp->Print("%8d  %6.2f  %6.2f  %6.2f  %9.3f\n",
				repeats,
				score[eval_player_position]->avg * 100,
				score[eval_player_position]->Calc_Confidence() * 100,
				score[eval_player_position]->dev * 100,
				cpu_time
				);

			delete(score[0]);
			delete(score[1]);

		}
		else{

			gmp->Print("! HUMAN Opponent !\n");
			gmp->Print("\n");
			if (human_opponent_override == 1)
				players[1 - eval_player_position] = new Player_Human(game);
			game->Simulate_Output_Game(players);
			if (human_opponent_override == 1)
				delete(players[1 - eval_player_position]);
		}

		gmp->Flush();

		//gmp->Print("\n\nFixed_Play_Testing(): TotalRuntime: %9.3f s\n", cpu_time);
		delete(game);
		delete(opponent);
		//delete(benchmarkOpponent);
		delete(evaluated);
		//delete(benchmarkEvaluated);
	}

	//Improved LRP search v1 - restart from kNN best average score after a batch of iterations
	//kNN is weighted according to the number of repeated evaluations (num_repeats), evaluated sample can be set to a higher weight
	void LRP_improved_v1(double* score_avg, double* score_avg_last10, double** last_param_val, bool force_setting_output, const int set_final_evaluations, double* avg_num_games, double* final_eval_score)
	{

		//configuration
		const int		num_iterations_self = 100;						//number MCTS simulations per move: evaluated player
		const int		num_iterations_opponent = 100;	//number MCTS simulation per move: opponent
		const int		num_games_start = 10;				//number of games per score output at LRP start
		const int		num_games_end = num_games_start;	//number of games per score output at LRP end
		const double	min_increase_num_games_fact = 1.0;		//minimal increase factor of games per evaluation if confidence below threshold (is ignored if max_increase_num_games_fact <= 1.0)
		const double	max_increase_num_games_fact = 1.0;		//maximal increase factor of games per evaluation requested by LRP confidence statistical test (disable by setting <= 1.0)
		const double	start_Cp_self = 0.2;		//initial Cp: evaluated player
		const double	fixed_CP_opponent = 0.2;		//initial Cp: opponent
		const double	funcApp_init_weights = 0.0;		//initial function approximator weights (to be optimized by LRP)
		const int		num_LRP_iterations = 500;		//number of LRP iterations (must be > 1 otherwise invalid values appear)
		const double	dw_start = 0.2000;	//LRP delta weight (change in Cp value): at start
		const double	dw_limit = 0.0010;	//LRP delta weight (change in Cp value): at end
		const double	lrp_ab_max = 0.75;		//LRP learning parameter alpha: maximal value
		const double	lrp_ab_min = 0.02;		//LRP learning parameter alpha: minmal value
		const double	lrp_ab_dscore_min = 1.0 / (double)((num_games_start + num_games_end) / 2.0);	//LRP minimum delta score (to change probabilites with minimum alpha value)
		const double	lrp_ab_dscore_max = lrp_ab_dscore_min * 10.0;	//MUST BE HIGHER OR EQUAL TO lrp_ab_dscore_min
		const double	lrp_b_koef = 1;		//LRP learning parameter beta koeficient [0,1] of alpha value
		const bool		exp_dw_decrease = 0;		//use exponential weight decrease (instead of linear)
		const int		eval_player_position = 1;		//which player to optimize and evaluate 0 or 1, currently works only for two-player games
		const bool		LRP_output_best_kNN = true;					//if true final param values will be set according to kNN best avg, otherwise final param values are left from the last LRP iteration (true is default setting)
		const bool		KNN_weight_repeats = true;					//LRP best neighbour by kNN weight by number of repeats per sample (true is default setting)
		const double	LRP_best_neighbour_weight_central = 1.1;	//scalar factor of central (observed) sample weight when averaging with kNN	(1.1 is default setting, 1.0 means equal weight to other samples)

		//number of games to evaluate final combination of parameters
		//const int		final_evaluation_num_games = 5000;
		const int		final_evaluation_num_games = set_final_evaluations;
		//20000, 95% confidence that true value deviates less by 1%
		//5000,  95% confidence that true value deviates less by 2%
		//1200,  95% confidence that true value deviates less by 4%
		//750,   95% confidence that true value deviates less by 5% (default setting)
		//200,	 95% confidence that true value deviates less by 10%
		const int		final_evaluation_num_iterations_self = num_iterations_self;
		const int		final_evaluation_num_iterations_opponent = num_iterations_opponent;
		const int		final_eval_player_position = eval_player_position;

		//number of LRP_iterations between restarts from best position in parameter space (disable by setting to num_LRP_iterations or 0)	
		//const int		LRP_restart_condition_iterations = 0;	//never restart
		const int		LRP_restart_condition_iterations = (int)(sqrt(num_LRP_iterations) + 0.5);	//sqare root of LRP iterations (default setting)
		//const int		LRP_restart_condition_iterations = (int)(num_LRP_iterations/10.0 + 0.5);	//linear to numer of LRP iterations

		//user-defined equations for LRP_best_neighbours_num: number of nearest neighbours when searching combination of parameters with best average score
		const int		LRP_best_neighbours_num = (int)(min((sqrt(num_LRP_iterations / 10.0 * 1000.0 / ((num_games_start + num_games_end) / 2.0)))*0.5, num_LRP_iterations*0.1*LRP_best_neighbour_weight_central) + 0.5);	//sqare root of num LRP iterations and games (default setting)
		//const int		LRP_best_neighbours_num = (int)(min( (sqrt(num_LRP_iterations/20.0 * 1000.0/((num_games_start+num_games_end)/2.0)))*0.5 , num_LRP_iterations*0.1*LRP_best_neighbour_weight_central) + 0.5);	//less KNN, sqare root of num LRP iterations and games
		//const int		LRP_best_neighbours_num = (int)(min( (sqrt(num_LRP_iterations/10.0)*(100.0/((num_games_start+num_games_end)/2.0))) , num_LRP_iterations*0.1*0.5*LRP_best_neighbour_weight_central) + 0.5);	//sqare root of num LRP iterations, linear in games	

		//restart from best only if current score differs from best by more than this factor, if (1-current/best >= factor) then restart) (0.0 restarts always, also if last is best), is ignored if LRP_restart_condition_iterations == 0
		//const double	LRP_restart_condition_score_rel_diff = 0.0;	//always restart
		const double	LRP_restart_condition_score_rel_diff = 0.1 * 1 / sqrt(LRP_best_neighbours_num) * LRP_best_neighbour_weight_central;	//(default setting)
		const double	LRP_restart_condition_score_rel_diff_end = 0.2 * LRP_restart_condition_score_rel_diff;	//the factor decreases linearly by the number of iterations down to this value

		//confidence interval factor for assessing if two scores belong to different distributions
		const bool		LRP_change_AB_by_confidence = true;		//change LRP alpha-beta parameters proportionally to confidence between scores (true, default setting) or to absolute difference (false)
		const bool		LRP_change_DW_by_confidence = false;	//NOT YET IMPLEMENTED: change LRP delta weight proportionally to confidence between scores (true) or linearly/exponentially between dw_start and dw_limit (false, default setting)
		const double	lrp_score_diff_conf_factor = 1.44;		//(1.44 <- 85% is default setting)
		//99% -> 2.58
		//95% -> 1.96
		//90% -> 1.645
		//85% -> 1.44
		//80% -> 1.28
		//75% -> 1.15
		//70% -> 1.04

		//THE NUMBER OF Func_App_UCT_Params must be set in Player_AI_UCT_TomTest.hpp with the constant TOMPLAYER_AI_UCT_TOMTEST_FUNC_APPROX_NUM_PARAMS


		//TODO1: da ce je slabši rezultat, da razveljaviš in daš na prejšnje stanje, parameter pa ni treba dat celo pot nazaj ampak samo do doloèene mere

		//TODO2 (veè dela): preizkusi èe bi dva loèena LRPja delovala boljše za iskanje 2 parametrov, 2 varianti:
		//			*oba LRPja istoèasno izvedeta akcijo in opazujeta izhod
		//			*LRPja izmenièno izvajata akcije (to pomeni, da je na razpolago pol manj korakov za posamezen LRP)

		const bool show_full_output = true; //runtime setting

		//Game_Engine* game = new Game_ConnectFour();
		Game_Engine* game = new Game_Gomoku();
		//Game_Engine* game = new Game_TicTacToe();
		//Game_Engine* game = new Game_Hex();

		Player_AI_UCT_TomTest* optimizingPlayer = new Player_AI_UCT_TomTest();
		Player_AI_UCT* opponent = new Player_AI_UCT(game);

		Tom_Function_Approximator* funcApp1 = new Tom_Function_Approximator();
		funcApp1->Initialize();
		funcApp1->num_results = optimizingPlayer->Func_App_UCT_num_params;
		funcApp1->Settings_Apply_New();

		for (int i = 0; i < funcApp1->num_params; i++)
			funcApp1->parameter_weights[i] = funcApp_init_weights;

		optimizingPlayer->Func_App_UCT_Params = funcApp1;
		optimizingPlayer->game = game;
		optimizingPlayer->Initialize();
		optimizingPlayer->Output_Log_Level_Create_Headers();

		optimizingPlayer->UCT_param_C = start_Cp_self;

		//-------- end of settings -------- //

		bool silence_output = ((score_avg != NULL) || (score_avg_last10 != NULL) || (last_param_val != NULL));

		//apply settings and initialize structurs
		optimizingPlayer->UCT_param_IterNum = num_iterations_self;
		opponent->UCT_param_IterNum = num_iterations_opponent;
		opponent->UCT_param_C = fixed_CP_opponent;

		Player_Engine* players[2];
		players[eval_player_position] = optimizingPlayer;
		players[1 - eval_player_position] = opponent;

		Tom_Lrp* Lrp = new Tom_Lrp();
		Lrp->Initialize();
		Lrp->num_actions = funcApp1->num_actions;
		Lrp->Settings_Apply_New();
		Lrp->Evaluations_History_Allocate(num_LRP_iterations + 1, funcApp1->num_params);

		//results storage
		Tom_Sample_Storage<double>* score_history = new Tom_Sample_Storage<double>(num_LRP_iterations + 1);

		//srand((unsigned int)time(NULL));
		double cpu_time = getCPUTime();
		double cpu_time1;

		//calculate exponential time constant
		double dw_tau = (double)num_LRP_iterations / (log(dw_start / dw_limit));

		//output test settings
		if ((!silence_output) || (force_setting_output)){
			gmp->Print("LRP_improved_v1()\n");
			gmp->Print("%s %dx%d\n", game->game_name.c_str(), game->board_length, game->board_height);
			gmp->Print("Players: "); for (int i = 0; i < 2; i++) gmp->Print("%s \t", players[i]->player_name.c_str()); gmp->Print("\n");
			gmp->Print("Evaluated_player %d  sim %d  start_Cp %1.3f  par_w_init %1.3f\n", eval_player_position + 1, num_iterations_self, start_Cp_self, funcApp_init_weights);
			gmp->Print("Opponent_player  %d  sim %d  fixed_Cp %3.3f\n", 2 - eval_player_position, num_iterations_opponent, fixed_CP_opponent);
			gmp->Print("LRP_steps %5d  games %d %d\n", num_LRP_iterations, num_games_start, num_games_end);
			gmp->Print("LRP_restart %4d  restart_threshold %5.3f %5.3f\n", LRP_restart_condition_iterations, LRP_restart_condition_score_rel_diff, LRP_restart_condition_score_rel_diff_end);
			gmp->Print("kNN %2d  central_weight %3.1f  weight_repeats %d\n", LRP_best_neighbours_num, LRP_best_neighbour_weight_central, (int)KNN_weight_repeats);
			gmp->Print("enable_output_best_kNN %d  final_eval_games %d\n", (int)LRP_output_best_kNN, final_evaluation_num_games);
			gmp->Print("Score_conf_test %4.2f\n", lrp_score_diff_conf_factor);
			gmp->Print("Games_by_conf_fact %3.1f %3.1f\n", min_increase_num_games_fact, max_increase_num_games_fact);
			gmp->Print("LRP_ab_by_conf %d  LRP_dw_by_conf %d\n", (int)LRP_change_AB_by_confidence, (int)LRP_change_DW_by_confidence);
			gmp->Print("LRP_ab_min %1.3f  LRP_ab_max %1.3f  LRP_b_koef %1.3f\n", lrp_ab_min, lrp_ab_max, lrp_b_koef);
			gmp->Print("lrp_ab_dscore_min %1.3f lrp_ab_dscore_max %1.3f\n", lrp_ab_dscore_min, lrp_ab_dscore_max);
			gmp->Print("Use_linear_dw_decrease %d  dw %1.5f %1.5f  dw_tau %1.5f\n", (int)(!exp_dw_decrease), dw_start, dw_limit, dw_tau);
			gmp->Print("\n");
		}

		//--- LRP algorithm ---//

		double score, previous_score, score_tmp, final_score;
		int num_LRP_batch_iterations, num_games_tmp;
		int selected_action;
		int index_best_setting;
		int count_restarts, count_restart_checks;
		double confidence_normal_dist1;
		double confidence_normal_dist2;
		double confidence_num_games1, confidence_num_games2;
		int total_games_count;

		double dw = dw_start;
		double lrp_ab = 0.0;
		int num_games = num_games_start;

		//evaluate starting setting
		score = game->Evaluate_Players(1, num_games, -1, players, false, eval_player_position) / num_games;
		score_history->Add_Sample(score);
		Lrp->Evaluations_History_Add_Sample(-1, num_games, score, 0.0, funcApp1->parameter_weights);
		total_games_count = num_games;

		//int best_iteration = -1;
		//double best_score = score;
		//double best_paramC = start_c1;

		if (!silence_output){
			if (show_full_output){
				gmp->Print("  \t     \t Parameters");
			}
			gmp->Print("\ni \t score");
			for (int p = 0; p < funcApp1->num_params; p++)
				gmp->Print("\t P%d", p);
			if (show_full_output){
				gmp->Print(" \t\t action");
				for (int a = 0; a < Lrp->num_actions; a++)
					gmp->Print("\t A%d[%%]", a);
				gmp->Print("\t dw \t\t lrp_ab");
				gmp->Print("\t Games");
				gmp->Print("\t NormDistConf");
			}
			gmp->Print("\n%d \t%5.1f%", 0, score * 100);
			for (int p = 0; p < funcApp1->num_params; p++)
				gmp->Print("\t%6.3f", funcApp1->parameter_weights[p]);
			if (show_full_output){
				gmp->Print(" \t\t ");
				gmp->Print("//");
				Lrp->Debug_Display_Probabilites(0);
				gmp->Print(" \t %1.5f \t %1.3f", dw, lrp_ab);
				gmp->Print(" \t %4d", num_games);
			}
			gmp->Print("\n");
		}

		//debug
		//double debug_scores[num_LRP_iterations] = {0.1 , 0.2 , 0.3 , 0.4 , 0.5};
		//srand(0);

		//Lrp iterations
		num_LRP_batch_iterations = 0;
		count_restarts = 0;
		count_restart_checks = 0;
		for (int i = 0; i < num_LRP_iterations; i++){

			if (exp_dw_decrease){
				//exponential iterative decrease of weight change step
				dw = dw_start * exp(-i / dw_tau);
			}
			else{
				//linear iterative decrease of weight change step
				dw = dw_limit + (dw_start - dw_limit) * (1.0 - (double)i / (num_LRP_iterations - 1));
			}

			//increase number of games per evalation

			num_games = (int)((num_games_start + (num_games_end - num_games_start) * ((double)(i + 1) / num_LRP_iterations)) + 0.5);

			//Lrp select action
			selected_action = Lrp->Select_Action(TOM_LRP_SELECT_ACTION_CHECK_SUM);

			//apply action
			//if(selected_action == Lrp->num_actions-1){
			//	funcApp1->parameter_weights[0] = 0.2;
			//}else{
			//	funcApp1->parameter_weights[0] = -0.5;
			//}
			funcApp1->Action_Update_Weights(selected_action, dw);
			//optimizingPlayer->UCT_param_C = funcApp1->parameter_weights[0];

			//evaluate new setting and save scores
			previous_score = score;						//save previous score
			score = game->Evaluate_Players(1, num_games, -1, players, false, eval_player_position) / num_games;

			//-- statistical difference test --//
			int stat_run_once = 0;
			while (stat_run_once < 2){

				//calculate the confidence, that the last two scores belong to different normal distributions
				confidence_normal_dist1 =
					sqrt(
					(Lrp->evaluations_history[Lrp->evaluations_history_num_samples - 1].num_repeats)
					* (score - previous_score) * (score - previous_score)
					/ (previous_score * (1 - previous_score) + 0.00001)	// + 0.00001 only to avoid division by 0
					/ 2.0 //optional
					);
				//calculate the confidence, that the last two scores belong to different normal distributions
				confidence_normal_dist2 =
					sqrt(
					(num_games)
					* (score - previous_score) * (score - previous_score)
					/ (score * (1 - score) + 0.00001)	// + 0.00001 only to avoid division by 0
					/ 2.0 //optional
					);
				confidence_num_games1 = lrp_score_diff_conf_factor*lrp_score_diff_conf_factor*(previous_score * (1 - previous_score)) * 2.0 / ((score - previous_score) * (score - previous_score) + 0.00001);
				confidence_num_games2 = lrp_score_diff_conf_factor*lrp_score_diff_conf_factor*(score * (1 - score)) * 2.0 / ((score - previous_score) * (score - previous_score) + 0.00001);

				//re-evaluate with higher number of games if confidence below threshold (lrp_score_diff_conf_factor)
				num_games_tmp = (int)(((max_increase_num_games_fact - 1.0)*num_games) * (1.0 - min(1.0, max(confidence_normal_dist1, confidence_normal_dist2) / lrp_score_diff_conf_factor)));
				if ((num_games_tmp > 0) && (stat_run_once == 0)){										//if confidence below threshold, then repeat player evaluation with higher number of games
					num_games_tmp = (int)max(num_games_tmp, num_games*(min_increase_num_games_fact - 1.0));		//set number of additional games minimum to increase_num_games_thr
					score_tmp = game->Evaluate_Players(1, num_games_tmp, -1, players, false, eval_player_position) / num_games_tmp;	//perform additional evaluations
					score = (score_tmp*num_games_tmp + score*num_games) / (num_games_tmp + num_games);	//update score
					num_games += num_games_tmp;		//update number of evaluation games
					stat_run_once = 1;	//repeat statistical test
				}
				else{
					stat_run_once = 2;	//do not repeat statistical test
				}

			}
			//-- END - statistical difference test --//

			score_history->Add_Sample(score);
			Lrp->Evaluations_History_Add_Sample(selected_action, num_games, score, 0.0, funcApp1->parameter_weights);
			total_games_count += num_games;

			//score = debug_scores[i]; //DEBUG

			if (!silence_output){
				gmp->Print("%d \t%5.1f%", i + 1, score * 100);
				for (int p = 0; p < funcApp1->num_params; p++)
					gmp->Print("\t%6.3f", funcApp1->parameter_weights[p]);
				gmp->Print(" \t\t ");
			}

			//-- adaptively change LRP learning parameter alpha (and beta) --//
			//proportional to confidence between scores
			if (LRP_change_AB_by_confidence){

				lrp_ab = max(lrp_ab_min, lrp_ab_max * min(1.0, max(confidence_normal_dist1, confidence_normal_dist2) / lrp_score_diff_conf_factor));
				//inverse, for testing only - should perform worse //lrp_ab = lrp_ab_min + lrp_ab_max - max(lrp_ab_min, lrp_ab_max * min(1.0 , max(confidence_normal_dist1, confidence_normal_dist2) / 1.96));

				//linearly proportional lrp learning parameter
			}
			else{
				lrp_ab =
					lrp_ab_min + (lrp_ab_max - lrp_ab_min) * max(0.0, min(1.0,
					(abs(score - previous_score) - lrp_ab_dscore_min) / (lrp_ab_dscore_max - lrp_ab_dscore_min)
					));
			}
			Lrp->learn_param_a = lrp_ab;
			Lrp->learn_param_b = lrp_ab * lrp_b_koef;
			//-- END - adaptively change LRP learning parameter alpha (and beta) --//

			//Lrp correct probabilites based on previous and current score
			if (score > previous_score){
				Lrp->Update_Probabilites_Reward(selected_action, Lrp->learn_param_a);
				if (!silence_output) if (show_full_output) gmp->Print("+");
			}
			else{
				Lrp->Update_Probabilites_Penalty(selected_action, Lrp->learn_param_b);
				if (!silence_output) if (show_full_output) gmp->Print("-");
			}

			//output
			if (!silence_output){
				if (show_full_output){
					gmp->Print("%d", selected_action);
					Lrp->Debug_Display_Probabilites(0);
					gmp->Print(" \t %1.5f \t %1.3f", dw, lrp_ab);
					gmp->Print(" \t %4d", num_games);
					gmp->Print(" \t %5.2f %5.2f %4.0f %4.0f", confidence_normal_dist1, confidence_normal_dist2, confidence_num_games1, confidence_num_games2);
				}
			}
			//remember best
			//if(score >= best_score){
			//	best_iteration = i;
			//	best_score = score;
			//	best_paramC = playerUCT1->UCT_param_C;
			//}

			//Restart from best position periodically after LRP_restart_condition_iterations iterations
			num_LRP_batch_iterations++;
			if ((LRP_restart_condition_iterations > 0) && (num_LRP_batch_iterations >= LRP_restart_condition_iterations)){

				//calculate kNN scores and find best parameter setting
				index_best_setting = Lrp->Evaluations_History_Best_KNN_Average_Slow(LRP_best_neighbours_num, KNN_weight_repeats, LRP_best_neighbour_weight_central, false, 0);

				//check difference between scores of last sample (current state) and best score, threshold decreases linearly (by increasing number of iterations, it is more likely to restart from best position)
				double last_sample_score = Lrp->evaluations_history[(Lrp->evaluations_history_num_samples) - 1].kNN_score;
				double best_sample_score = Lrp->evaluations_history[index_best_setting].kNN_score;
				double current_score_ratio;
				if (best_sample_score != 0.0)	//division safety
					current_score_ratio = 1.0 - last_sample_score / best_sample_score;
				else
					current_score_ratio = 0.0;
				double restart_threshold = LRP_restart_condition_score_rel_diff_end + (LRP_restart_condition_score_rel_diff - LRP_restart_condition_score_rel_diff_end) * (1.0 - (double)i / (num_LRP_iterations - 1));

				//DEBUG
				//gmp->Print("\n"); Lrp->Debug_Display_Evaluations_History();
				//gmp->Print("\t %d %f %d %f\t",index_best_setting, best_sample_score, (Lrp->evaluations_history_num_samples)-1, last_sample_score);

				if (current_score_ratio >= restart_threshold){

					if (!silence_output){
						gmp->Print(" \t RESTART %3.3f", current_score_ratio);
					}

					//--do execute restart from best position--

					//reset LRP probabilites
					Lrp->State_Reset();

					//set parameter values to best combination found so far
					for (int p = 0; p < funcApp1->num_params; p++)
						funcApp1->parameter_weights[p] = Lrp->evaluations_history[index_best_setting].param_values[p];

					//set appropriate score to compare in next iteration
					score = Lrp->evaluations_history[index_best_setting].score;

					//increase counter of restarts
					count_restarts++;
				}
				else{
					if (!silence_output){
						gmp->Print(" \t CHECK %3.3f", current_score_ratio);
					}
				}

				num_LRP_batch_iterations = 0;
				count_restart_checks++;
			}

			if (!silence_output){
				gmp->Print("\n");
			}
		}


		//output best parameter combination from history instead of values in last iteration
		if (LRP_output_best_kNN){
			index_best_setting = Lrp->Evaluations_History_Best_KNN_Average_Slow(LRP_best_neighbours_num, KNN_weight_repeats, LRP_best_neighbour_weight_central, false, 0);
			for (int p = 0; p < funcApp1->num_params; p++)
				funcApp1->parameter_weights[p] = Lrp->evaluations_history[index_best_setting].param_values[p];
		}

		//--- LRP algorithm END---//

		cpu_time = getCPUTime() - cpu_time;

		//evaluation of final parameters
		optimizingPlayer->UCT_param_IterNum = final_evaluation_num_iterations_self;
		opponent->UCT_param_IterNum = final_evaluation_num_iterations_opponent;
		players[final_eval_player_position] = optimizingPlayer;
		players[1 - final_eval_player_position] = opponent;
		cpu_time1 = getCPUTime();
		final_score = game->Evaluate_Players(1, final_evaluation_num_games, -1, players, false, eval_player_position) / final_evaluation_num_games;
		cpu_time1 = getCPUTime() - cpu_time;

		//output best
		//gmp->Print("\nBest score: %5.1f% \t P1->Cp  %5.3f \t i  %d\n", best_score*100, best_paramC, best_iteration+1);

		//output values
		score_history->Calc_AvgDev();
		double score10 = score_history->Calc_Avg_On_Interval((int)(num_LRP_iterations*0.9), num_LRP_iterations);
		if (!silence_output){

			double final_eval_dev = sqrt(1.96*1.96*final_score*(1 - final_score)*2.0 / final_evaluation_num_games);

			//Lrp output (best parameters value)
			gmp->Print("\n");
			//Lrp->Debug_Display_Evaluations_History();	//output LRP evaluations history
			Lrp->Evaluations_History_Best_Single();
			Lrp->Evaluations_History_Best_KNN_Average_Slow(LRP_best_neighbours_num, true, LRP_best_neighbour_weight_central, false);

			//Statistics and final evaluation
			gmp->Print("\navgGam \t avg100\t avg10 \t fEval", final_evaluation_num_games);
			for (int p = 0; p < funcApp1->num_params; p++)
				gmp->Print("\t FinP%d", p);
			gmp->Print("\t fEvaConf95");
			gmp->Print("\n%6.1f \t %5.2f \t %5.2f \t %5.2f", (double)total_games_count / (num_LRP_iterations + 1), score_history->avg * 100, score10 * 100, final_score * 100);
			for (int p = 0; p < funcApp1->num_params; p++)
				gmp->Print("\t%7.4f", funcApp1->parameter_weights[p]);
			gmp->Print("\t %5.2f", final_eval_dev * 100);

			//runtime
			gmp->Print("\n\nRuntime [s]:\n  Lrp\t%9.3f\n  Eval\t%9.3f (%d games)\n  Total\t%9.3f\n", cpu_time, cpu_time1, final_evaluation_num_games, cpu_time + cpu_time1);
		}


		//DEBUG
		//gmp->Print("RR: %5.2f%% \t ",(double)count_restarts/count_restart_checks*100.0);	//output restart rate
		//gmp->Print("ratio p0: %3.3f\n",optimizingPlayer->debug_dbl_cnt1 / optimizingPlayer->debug_dbl_cnt2 *100.0);	//2-interval C search ratio of use p0 to (p0+p1)

		//return values
		if (score_avg != NULL)
			(*score_avg) = score_history->Calc_Avg();
		if (last_param_val != NULL)
		for (int i = 0; i < funcApp1->num_params; i++)
			(*last_param_val)[i] = funcApp1->parameter_weights[i];
		if (score_avg_last10 != NULL)
			(*score_avg_last10) = score_history->Calc_Avg_On_Interval((int)(num_LRP_iterations*0.9), num_LRP_iterations);
		if (avg_num_games != NULL)
			(*avg_num_games) = (double)total_games_count / (num_LRP_iterations + 1);
		if (final_eval_score != NULL)
			(*final_eval_score) = final_score;

		gmp->Flush();

		//free memory
		delete(score_history);
		delete(Lrp);
		delete(optimizingPlayer);
		delete(opponent);
		delete(game);
	}

	void LRP_test_wrapperMultiPar()
	{

		const int num_repeats = 100;				//number of LRP repeats (not STEPS!)
		const int num_LRP_params = TOMPLAYER_AI_UCT_TOMTEST_FUNC_APPROX_NUM_PARAMS;			//the number of weights set by LRP
		const int num_final_evaluations = 20000;	//number of games to evaluate final combination of parameters (default 750)
		//20000, 95% confidence that true value deviates less by 1%
		//5000,  95% confidence that true value deviates less by 2%
		//1200,  95% confidence that true value deviates less by 4%
		//750,   95% confidence that true value deviates less by 5%
		//200,	 95% confidence that true value deviates less by 10%
		// --- settings end --- //

		double score_avg;
		double score_avg_last10;
		double* last_param_val = new double[num_LRP_params];
		double avg_num_games;
		double final_eval_score;

		bool output_settings_once = true;

		double cpu_time = getCPUTime();

		Tom_Sample_Storage<double>* avg_score = new Tom_Sample_Storage<double>(num_repeats);
		Tom_Sample_Storage<double>* avg_score10 = new Tom_Sample_Storage<double>(num_repeats);
		Tom_Sample_Storage<double>* last_param[num_LRP_params];
		for (int p = 0; p < num_LRP_params; p++)
			last_param[p] = new Tom_Sample_Storage<double>(num_repeats);
		Tom_Sample_Storage<double>* final_score = new Tom_Sample_Storage<double>(num_repeats);
		Tom_Sample_Storage<double>* num_games_per_step = new Tom_Sample_Storage<double>(num_repeats);

		gmp->Print("LRP_test_wrapperMultiPar(), %d repeats %d params\n\n", num_repeats, num_LRP_params);

		for (int r = 0; r < num_repeats; r++){
			//LRP_test_linAB_exponentDW_FunApp_MulParams(&score_avg,&score_avg_last10,&last_param_val,output_settings_once,num_LRP_params);
			LRP_improved_v1(&score_avg, &score_avg_last10, &last_param_val, output_settings_once, num_final_evaluations, &avg_num_games, &final_eval_score);

			if (output_settings_once){
				gmp->Print("\nRun       avg    [%%]    [%%]    [%%]   Final_params\n");
				gmp->Print("        games scr100  scr10  final   "); for (int p = 0; p < num_LRP_params; p++) gmp->Print("P%d       ", p); gmp->Print("\n");
			}

			gmp->Print("%3d    %6.1f %6.2f %6.2f %6.2f  ", r, avg_num_games, score_avg * 100, score_avg_last10 * 100, final_eval_score * 100); for (int p = 0; p < num_LRP_params; p++) gmp->Print("%7.4f  ", last_param_val[p]); gmp->Print("\n");
			avg_score->Add_Sample(score_avg);
			avg_score10->Add_Sample(score_avg_last10);
			for (int p = 0; p < num_LRP_params; p++)
				last_param[p]->Add_Sample(last_param_val[p]);
			final_score->Add_Sample(final_eval_score);
			num_games_per_step->Add_Sample(avg_num_games);

			output_settings_once = false;

			gmp->Flush();
		}

		avg_score->Calc_AllExceptSum();
		avg_score10->Calc_AllExceptSum();
		for (int p = 0; p < num_LRP_params; p++){
			last_param[p]->Calc_AllExceptSum();
		}
		final_score->Calc_AllExceptSum();
		num_games_per_step->Calc_AllExceptSum();

		gmp->Print("\n\n");

		gmp->Print("Summary   avg    [%%]    [%%]    [%%]   Final_params\n");
		gmp->Print("        games scr100  scr10  final   "); for (int p = 0; p < num_LRP_params; p++) gmp->Print("P%d       ", p); gmp->Print("\n");
		gmp->Print("avg    %6.1f %6.2f %6.2f %6.2f  ", num_games_per_step->avg, avg_score->avg * 100, avg_score10->avg * 100, final_score->avg * 100); for (int p = 0; p < num_LRP_params; p++) gmp->Print("%7.4f  ", last_param[p]->avg); gmp->Print("\n");
		gmp->Print("dev    %6.1f %6.2f %6.2f %6.2f  ", num_games_per_step->dev, avg_score->dev * 100, avg_score10->dev * 100, final_score->dev * 100); for (int p = 0; p < num_LRP_params; p++) gmp->Print("%7.4f  ", last_param[p]->dev); gmp->Print("\n");
		gmp->Print("conf   %6.1f %6.2f %6.2f %6.2f  ", num_games_per_step->conf, avg_score->conf * 100, avg_score10->conf * 100, final_score->conf * 100); for (int p = 0; p < num_LRP_params; p++) gmp->Print("%7.4f  ", last_param[p]->conf); gmp->Print("\n");
		gmp->Print("median %6.1f %6.2f %6.2f %6.2f  ", num_games_per_step->median, avg_score->median * 100, avg_score10->median * 100, final_score->median * 100); for (int p = 0; p < num_LRP_params; p++) gmp->Print("%7.4f  ", last_param[p]->median); gmp->Print("\n");

		cpu_time = getCPUTime() - cpu_time;
		gmp->Print("\n\nTotalRuntime: %9.3f s\n", cpu_time);
		gmp->Flush();

		delete[] last_param_val;
		delete(avg_score);
		delete(avg_score10);
		for (int p = 0; p < num_LRP_params; p++)
			delete(last_param[p]);
	}




	//-------------- 2015.03.01 EXPERIMENT1 debug instances --------------//

	void Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_negativeStep_episodes10k(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_negativeStep_episodes10k()";
		char* xAxisLabel = " episode";

		int total_number_configurations = 5;		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int config_max_num_episodes = 10000;
		int config_max_num_repeats = 2000;	//running time of approximately 6 seconds per repeat

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  rf wl iVa tn ra al  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		int sInd = 0;	//index of current configuration

		//different game definitions (different reward functions)
		for (int rf = 1; rf < 2; rf++){
			if (rf == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (rf == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 2; wl < 3; wl++){
				if (wl == 0){
					config_walk_length = 5;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else if (wl == 1){
					config_walk_length = 11;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else{
					config_walk_length = 21;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different initial values
				for (int iv = 0; iv < 1; iv++){
					if (iv == 0){
						par_td_initVal = 0.0;
					}
					else if (iv == 1){
						par_td_initVal = -0.5;
					}
					else{
						par_td_initVal = 0.5;
					}

					//with/without transpositions, add all nodes or just one (UCT behaviour)
					for (int tn = 0; tn < 1; tn++){
						int raMax;
						if (tn == 0){
							config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
							config_num_new_nodes_per_episode = -1;
							raMax = 1;
						}
						else if (tn == 1){
							config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							config_num_new_nodes_per_episode = -1;
							raMax = 1;
						}
						else{
							config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							config_num_new_nodes_per_episode = 1;
							raMax = 3;
						}

						//different rollout assumptions						
						for (int ra = 0; ra < raMax; ra++){
							if (ra == 0){
								config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
							}
							else if (ra == 1){
								config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
							}
							else{
								config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
							}

							//-//-// single set of different algorithms

							sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2d", rf, config_walk_length, par_td_initVal, tn, ra);

							config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;

							//Episodic MC
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							////Episodic TD(0)
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Episodic TD(lambda)
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//-//-//
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}


	void Experiment_RandomWalk_perEpisode_Batch_DEBUG_rollout_assumptions_equality_RW21(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_DEBUG_rollout_assumptions_equality_RW21()";
		char* xAxisLabel = " episode";

		int total_number_configurations = 2*3*2*4*5;		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int config_max_num_episodes = 100;
		int config_max_num_repeats = 100; //approximately 30s per repeat

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  rf gl iVa tn ra al  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		int sInd = 0;	//index of current configuration

		//different game definitions (different reward functions)
		for (int rf = 0; rf < 2; rf++){
			if (rf == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (rf == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 2; wl < 3; wl++){
				if (wl == 0){
					config_walk_length = 5;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else if (wl == 1){
					config_walk_length = 11;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else{
					config_walk_length = 21;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different gamma/lambda combinations
				double TDlambda;
				for (int gl = 0; gl < 3; gl++){
					if (gl == 0){
						player->par_task_gamma = 1.0;
						TDlambda = 1.0;
					}
					else if (gl == 1){
						player->par_task_gamma = 1.0;
						TDlambda = 0.8;
					}
					else{
						player->par_task_gamma = 0.9;
						TDlambda = 0.8;
					}

					//different initial values
					for (int iv = 0; iv < 2; iv++){
						if (iv == 0){
							par_td_initVal = 0.0;
						}
						else{
							par_td_initVal = 0.5;
						}

						//with/without transpositions, add all nodes or just one (UCT behaviour)
						for (int tn = 0; tn < 4; tn++){
							if (tn == 0){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
								config_num_new_nodes_per_episode = -1;
							}
							else if (tn == 1){
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
								config_num_new_nodes_per_episode = -1;
							}
							else if (tn == 2){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
								config_num_new_nodes_per_episode = 1;
							}
							else {
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
								config_num_new_nodes_per_episode = 1;
							}

							//different rollout assumptions						
							for (int ra = 0; ra < 5; ra++){
								if (ra == 0){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
								}
								else if (ra == 1){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
								}
								else if (ra == 2){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
								}
								else if (ra == 3){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
								}
								else{
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
								}
								//-//-// single set of different algorithms

								sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2d", rf, gl, par_td_initVal, tn, ra);

								config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;
								srand(0);	//THIS IS HERE ON PURPOSE, SO THAT EVERY CONFIGURATION HAS THE SAME SEQUENCE OF RANDOM NUMBERS
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, TDlambda, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//-//-//
							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}


	void Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_initialValues(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_initialValues()";
		char* xAxisLabel = " episode";

		int total_number_configurations = 5*2*5;		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int config_max_num_episodes = 100;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  rf wl iVa tn ra al  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		int sInd = 0;	//index of current configuration

		//different game definitions (different reward functions)
		for (int rf = 0; rf < 1; rf++){
			if (rf == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (rf == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 2; wl < 3; wl++){
				if (wl == 0){
					config_walk_length = 5;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else if (wl == 1){
					config_walk_length = 11;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else{
					config_walk_length = 21;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different initial values
				for (int iv = 0; iv < 5; iv++){
					if (iv == 0){
						par_td_initVal = 0.0;
					}
					else if (iv == 1){
						par_td_initVal = 5.0;
					}
					else if (iv == 2){
						par_td_initVal = -5.0;
					}
					else if (iv == 3){
						par_td_initVal = 20.0;
					}
					else{
						par_td_initVal = -20.0;
					}

					//with/without transpositions, add all nodes or just one (UCT behaviour)
					for (int tn = 0; tn < 2; tn++){
						if (tn == 0){
							config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
							config_num_new_nodes_per_episode = -1;
						}
						else{
							config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							config_num_new_nodes_per_episode = 1;
						}

						//different rollout assumptions						
						for (int ra = 1; ra < 2; ra++){
							if (ra == 0){
								config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
							}
							else if (ra == 1){
								config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
							}
							else{
								config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
							}

							//-//-// single set of different algorithms

							sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2d", rf, config_walk_length, par_td_initVal, tn, ra);

							config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;

							//Episodic MC
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							////Episodic TD(0)
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Episodic TD(lambda)
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//-//-//
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}



	void Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_numNewNodes(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW21_numNewNodes()";
		char* xAxisLabel = " episode";

		int total_number_configurations = 2 * 2 * 5 * 6 * 1;		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int config_max_num_episodes = 100;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  rf wl ra tr nn al  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		int sInd = 0;	//index of current configuration

		//different game definitions (different reward functions)
		for (int rf = 0; rf < 2; rf++){
			if (rf == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (rf == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 2; wl < 3; wl++){
				if (wl == 0){
					config_walk_length = 5;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else if (wl == 1){
					config_walk_length = 11;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}
				else{
					config_walk_length = 21;
					maximum_plys = 10000;
					par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
					num_repeats = config_max_num_repeats;
				}

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different rollout assumptions						
				for (int ra = 0; ra < 5; ra++){
					if (ra == 0){
						config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
					}
					else if (ra == 1){
						config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
					}
					else if (ra == 2){
						config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
					}
					else if (ra == 3){
						config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
					}
					else{
						config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
					}

					//with/without transpositions, add all nodes or just one (UCT behaviour)
					for (int tr = 0; tr < 2; tr++){
						if (tr == 0){
							config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
						}
						else{
							config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
						}

						//different rollout assumptions						
						for (int nn = 0; nn < 6; nn++){
							if (nn == 0){
								config_num_new_nodes_per_episode = -1;
							}
							else{
								config_num_new_nodes_per_episode = nn;
							}

							//-//-// single set of different algorithms

							sprintf_s(printLinePrefix, "  %2d %2d %2d %2d %2d", rf, config_walk_length, ra, tr, config_num_new_nodes_per_episode);
							
							par_td_initVal = 0.0;
							config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;

							//Episodic MC
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							////Episodic TD(0)
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Episodic TD(lambda)
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
							//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 5, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

							//-//-//
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}


	void Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW_differentLengths(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_DEBUG_RW_differentLengths()";
		char* xAxisLabel = " episode";

		int total_number_configurations = 4 * 10;		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int config_max_num_episodes = 100;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  rf gl iVa wl ra al  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		int sInd = 0;	//index of current configuration

		//different game definitions (different reward functions)
		for (int rf = 0; rf < 1; rf++){
			if (rf == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (rf == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different gamma/lambda combinations
			player->par_task_gamma = 1.0;
			double TDlambda;
			for (int gl = 0; gl < 4; gl++){
				if (gl == 0){
					TDlambda = 1.0;
				}
				else if (gl == 1){
					TDlambda = 0.99;
				}
				else if (gl == 2){
					TDlambda = 0.5;
				}
				else{
					TDlambda = 0.1;
				}

				//different game sizes
				config_walk_length = 3;
				maximum_plys = 10000;
				par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				for (int wl = 0; wl < 10; wl++){

					config_walk_length += 2;

					//safety checks
					if (par_num_episodes > config_max_num_episodes){
						gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
						return;
					}
					if (num_repeats > config_max_num_repeats){
						gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
						return;
					}

					//different initial values
					for (int iv = 1; iv < 2; iv++){
						if (iv == 0){
							par_td_initVal = 0.0;
						}
						else{
							par_td_initVal = 0.5;
						}

						//with/without transpositions, add all nodes or just one (UCT behaviour)
						for (int tn = 3; tn < 4; tn++){
							if (tn == 0){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
								config_num_new_nodes_per_episode = -1;
							}
							else if (tn == 1){
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
								config_num_new_nodes_per_episode = -1;
							}
							else if (tn == 2){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
								config_num_new_nodes_per_episode = 1;
							}
							else {
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
								config_num_new_nodes_per_episode = 1;
							}

							//different rollout assumptions						
							for (int ra = 0; ra < 1; ra++){
								if (ra == 0){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
								}
								else if (ra == 1){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
								}
								else if (ra == 2){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
								}
								else if (ra == 3){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
								}
								else{
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
								}
								//-//-// single set of different algorithms

								sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2d", rf, gl, par_td_initVal, config_walk_length, ra);

								config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 4, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, TDlambda, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//-//-//
							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}

	//currently this experiment measures the performance of FVMC and TD(lamdba) under several control variables for a total of 2880 different configurations
	void Experiment_RandomWalk_perEpisode_Batch_stepNegativeReward(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_stepNegativeReward()";
		char* xAxisLabel = " episode";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations = 1 * 5 * 1 * 4 * 2 * 5 * 6;	// = 1200

		int config_max_num_episodes = 1000;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxActions = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl Qin nn tn ra al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different game definitions (different reward functions)
		for (int gd = 1; gd < 2; gd++){
			if (gd == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (gd == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 0; wl < 5; wl++){
				if (wl == 0){
					config_walk_length = 5;
				}
				else if (wl == 1){
					config_walk_length = 7;
				}
				else if (wl == 2){
					config_walk_length = 11;
				}
				else if (wl == 3){
					config_walk_length = 15;
				}
				else{
					config_walk_length = 21;
				}
				par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				maximum_plys = 10000;

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different initial values
				for (int qi = 0; qi < 1; qi++){
					if (qi == 0){
						par_td_initVal = 0.0;
					}
					else if (qi == 1){
						par_td_initVal = -0.5;
					}
					else{
						par_td_initVal = 0.5;
					}

					//different number of added nodes per episode (UCT behaviour)
					for (int nn = 0; nn < 4; nn++){
						int raMax;
						if (nn == 0){
							config_num_new_nodes_per_episode = -1;
							raMax = 1;
						}
						else if (nn == 1){
							config_num_new_nodes_per_episode = 1;
							raMax = 5;
						}
						else if (nn == 2){
							config_num_new_nodes_per_episode = 5;
							raMax = 5;
						}
						else{
							config_num_new_nodes_per_episode = 10;
							raMax = 5;
						}

						//with/without transpositions
						for (int tn = 0; tn < 2; tn++){
							if (tn == 0){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
							}
							else{
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							}

							//different rollout assumptions						
							for (int ra = 0; ra < raMax; ra++){
								if (ra == 0){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
								}
								else if (ra == 1){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
								}
								else if (ra == 2){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
								}
								else if (ra == 3){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
								}
								else{
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
								}


								//-//-// single set of different algorithms

								sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2s %2s", gd, config_walk_length, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption]);

								//--- Episodic
								config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;


								//-- Exponential step rate by state-visits
								config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

								//- First-visit MC
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//- Episodic TD(lambda) with exponential alpha by state-visits
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);


								////-- Constant step rate
								//config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT;

								////- Constant-alpha MC
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								////- Episodic TD(lambda) with constant alpha
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//-//-//

							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}

	void Experiment_RandomWalk_perEpisode_Batch_DifferentInitialValues(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_DifferentInitialValues()";
		char* xAxisLabel = " episode";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations = 1 * 1 * 5 * 1 * 2 * 2 * 6;	// = 120

		int config_max_num_episodes = 100;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxActions = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl Qin nn tn ra al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different game definitions (different reward functions)
		for (int gd = 0; gd < 1; gd++){
			if (gd == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (gd == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 4; wl < 5; wl++){
				if (wl == 0){
					config_walk_length = 5;
				}
				else if (wl == 1){
					config_walk_length = 7;
				}
				else if (wl == 2){
					config_walk_length = 11;
				}
				else if (wl == 3){
					config_walk_length = 15;
				}
				else{
					config_walk_length = 21;
				}
				par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				maximum_plys = 10000;

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different initial values
				for (int qi = 0; qi < 5; qi++){
					if (qi == 0){
						par_td_initVal = 0.0;
					}
					else if (qi == 1){
						par_td_initVal = 0.5;
					}
					else if (qi == 2){
						par_td_initVal = 5.0;
					}
					else if (qi == 3){
						par_td_initVal = 10.0;
					}
					else{
						par_td_initVal = 20.0;
					}

					//different number of added nodes per episode (UCT behaviour)
					for (int nn = 1; nn < 2; nn++){
						int raMax;
						if (nn == 0){
							config_num_new_nodes_per_episode = -1;
							raMax = 1;
						}
						else if (nn == 1){
							config_num_new_nodes_per_episode = 1;
							raMax = 2;
						}
						else if (nn == 2){
							config_num_new_nodes_per_episode = 5;
							raMax = 2;
						}
						else{
							config_num_new_nodes_per_episode = 10;
							raMax = 2;
						}

						//with/without transpositions
						for (int tn = 0; tn < 2; tn++){
							if (tn == 0){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
							}
							else{
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							}

							//different rollout assumptions						
							for (int ra = 0; ra < raMax; ra++){
								if (ra == 0){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
								}
								else if (ra == 1){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
								}
								else if (ra == 2){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
								}
								else if (ra == 3){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
								}
								else{
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
								}


								//-//-// single set of different algorithms

								sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2s %2s", gd, config_walk_length, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption]);

								//--- Episodic
								config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;


								//-- Exponential step rate by state-visits
								config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

								//- First-visit MC
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//- Episodic TD(lambda) with exponential alpha by state-visits
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);


								////-- Constant step rate
								//config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::CONSTANT;

								////- Constant-alpha MC
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 2, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_EPISODIC_ALPHA_MC, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								////- Episodic TD(lambda) with constant alpha
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.20, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.10, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.05, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
								//Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 3, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.01, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

								//-//-//

							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}


	void Experiment_RandomWalk_perEpisode_Batch_LambdaSensitivity100(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ---- //

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_EPISODES;
		char* procedureName = "Experiment_RandomWalk_perEpisode_Batch_LambdaSensitivity100()";
		char* xAxisLabel = " episode";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations = 5 * 5 * 3 * 101; // ~ 7575 configurations

		int config_max_num_episodes = 20;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;
		game->maxScore = 1.0;
		game->minScore = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxActions = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = -1;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
			gmp->Print("Program abort by resultsFilePrinter->Create_Output_Files()\n");
			cout << endl << "Press any key to exit.";
			cin.get();
			exit(EXIT_FAILURE);
		}

		//-- initial output (to stdout and to files)
		gmp->Print("\nExperiment_RandomWalk_perEpisode_Batch()\n");
		gmp->Print("Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
		game->Output_Description(false);

		// print headers of result files
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\nExperiment_RandomWalk_perEpisode_Batch()\n");
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl Qin nn tn ra al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_episodes + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_episodes;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different game definitions (different reward functions)
		for (int gd = 0; gd < 1; gd++){
			if (gd == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (gd == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 0; wl < 5; wl++){
				if (wl == 0){
					config_walk_length = 5;
				}
				else if (wl == 1){
					config_walk_length = 7;
				}
				else if (wl == 2){
					config_walk_length = 11;
				}
				else if (wl == 3){
					config_walk_length = 15;
				}
				else{
					config_walk_length = 21;
				}
				par_num_episodes = config_max_num_episodes;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				maximum_plys = 10000;

				//safety checks
				if (par_num_episodes > config_max_num_episodes){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): par_num_episodes > config_max_num_episodes\n");
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: Experiment_RandomWalk_perEpisode_Batch(): num_repeats > config_max_num_repeats\n");
					return;
				}

				//different initial values
				for (int qi = 0; qi < 5; qi++){
					if (qi == 0){
						par_td_initVal = 0.0;
					}
					else if (qi == 1){
						par_td_initVal = 0.5;
					}
					else if (qi == 2){
						par_td_initVal = 5.0;
					}
					else if (qi == 3){
						par_td_initVal = 10.0;
					}
					else{
						par_td_initVal = 20.0;
					}

					//different number of added nodes per episode (UCT behaviour)
					for (int nn = 1; nn < 2; nn++){
						int raMax;
						if (nn == 0){
							config_num_new_nodes_per_episode = -1;
							raMax = 1;
						}
						else if (nn == 1){
							config_num_new_nodes_per_episode = 1;
							raMax = 3;
						}
						else if (nn == 2){
							config_num_new_nodes_per_episode = 5;
							raMax = 3;
						}
						else{
							config_num_new_nodes_per_episode = 10;
							raMax = 3;
						}

						//with/without transpositions
						for (int tn = 1; tn < 2; tn++){
							if (tn == 0){
								config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
							}
							else{
								config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
							}

							//different rollout assumptions						
							for (int ra = 0; ra < raMax; ra++){
								if (ra == 0){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
								}
								else if (ra == 1){
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
								}
								else{
									config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
								}

								//different lambda
								for (int tdl = 0; tdl <= 100; tdl++){
									
									double TDlambda = (double)tdl / 100.0;

									//-//-// single set of different algorithms

									sprintf_s(printLinePrefix, "  %2d %2d %3.1f %2d %2s %2s", gd, config_walk_length, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption]);

									//--- Episodic
									config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;

									//-- Exponential step rate by state-visits
									config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

									//- Episodic TD(lambda) with exponential alpha by state-visits
									Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, par_num_episodes, par_td_initVal, 0.00, TDlambda, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

									//-//-//
								}
							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int m = 0; m < results_num_metrics; m++){
				if (gatheredResults[c][m] != NULL){
					for (int s = 0; s < config_max_num_episodes + 1; s++)
						delete[] gatheredResults[c][m][s];
					delete[] gatheredResults[c][m];
				}
			}
			delete[] gatheredResults[c];
		}
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}


	void Experiment_RandomWalk_perStep_Batch_LambdaSensitivity100(int startIndex, int endIndex, int useUCB)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 0;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ----//

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_TIMESTEPS;
		char* procedureName = "Experiment_RandomWalk_perStep_Batch()";
		char* xAxisLabel = " timStep";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations = 30000; // total of 27472; ~around 40 days of computation

		int config_max_num_timeSteps = 10000;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy
		player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 0.1;
		player->par_ucb_c = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = config_max_num_timeSteps;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
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
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\n%s\n", procedureName);
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl cp cPar Qin nn tn ra al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_timeSteps + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_simulated_actions;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different game definitions (different reward functions)
		for (int gd = 1; gd < 2; gd++){
			if (gd == 0){
				game->param_score_win = 1.0;
				game->param_score_lose = 0.0;
				game->param_score_step = 0.0;
			}
			else if (gd == 1){
				game->param_score_win = 0.0;
				game->param_score_lose = -1.0;
				game->param_score_step = -1.0;
			}

			//different game sizes
			for (int wl = 1; wl < 4; wl++){
				if (wl == 0){
					config_walk_length = 5;
				}
				else if (wl == 1){
					config_walk_length = 7;
				}
				else if (wl == 2){
					config_walk_length = 11;
				}
				else if (wl == 3){
					config_walk_length = 15;
				}
				else{
					config_walk_length = 21;
				}
				par_num_simulated_actions = config_max_num_timeSteps;	//MUST NOT EXCEED config_max_num_episodes!
				num_repeats = config_max_num_repeats;
				maximum_plys = 10000;
				if (gd == 0){
					game->maxScore = 1.0;
					game->minScore = 0.0;
				}
				else{
					game->maxScore = -(config_walk_length - 1) / 2;
					game->minScore = -(game->maximum_plys);
				}

				//safety checks
				if (par_num_simulated_actions > config_max_num_timeSteps){
					gmp->Print("ERROR: %s: par_num_episodes > config_max_num_episodes\n", procedureName);
					return;
				}
				if (num_repeats > config_max_num_repeats){
					gmp->Print("ERROR: %s: num_repeats > config_max_num_repeats\n", procedureName);
					return;
				}

				//different control policy settings
				for (int cpp = 0; cpp < 1; cpp++){
					if (cpp == 0){
						player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;
						player->par_egreedy_e = 0.1;
						player->config_ExplorationLinear_maxActions = 0;
					}
					else{
						player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;
						player->par_egreedy_e = 0.1;
						player->config_ExplorationLinear_maxActions = config_max_num_timeSteps;
					}
					double policyPar;
					if (player->config_control_policy == Player_AI_RL::CONTROL_POLICIES::EGREEDY)
						policyPar = player->par_egreedy_e;
					else if (player->config_control_policy == Player_AI_RL::CONTROL_POLICIES::UCB1)
						policyPar = player->par_ucb_c;

					//different initial values
					for (int qi = 0; qi < 4; qi++){
						if (qi == 0){
							par_td_initVal = 0.0;
						}
						else if (qi == 1){
							par_td_initVal = game->maxScore;
						}
						else if (qi == 2){
							par_td_initVal = game->maxScore*2;
						}
						else{
							par_td_initVal = -game->maxScore;
						}

						//different number of added nodes per episode (UCT behaviour)
						for (int nn = 0; nn < 4; nn++){
							int raMax;
							if (nn == 0){
								config_num_new_nodes_per_episode = -1;
								raMax = 1;
							}
							else if (nn == 1){
								config_num_new_nodes_per_episode = 1;
								raMax = 3;
							}
							else if (nn == 2){
								config_num_new_nodes_per_episode = 5;
								raMax = 3;
							}
							else{
								config_num_new_nodes_per_episode = 10;
								raMax = 3;
							}

							//with/without transpositions
							for (int tn = 0; tn < 2; tn++){
								if (tn == 0){
									config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
								}
								else{
									config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
									if (raMax > 2)
										raMax = 2;
								}

								//different rollout assumptions						
								for (int ra = 0; ra < raMax; ra++){
									if (ra == 0){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
									}
									else if (ra == 1){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
									}
									else if (ra == 2){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
									}
									else if (ra == 3){
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
									}
									else{
										config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
									}

									//different lambda
									for (int tdl = 0; tdl <= 100; tdl++){

										double TDlambda = (double)tdl / 100.0;

										//-//-// single set of different algorithms

										sprintf_s(printLinePrefix, "  %2d %2d %2d %4.2f %3.1f %2d %2s %2s", gd, config_walk_length, cpp, policyPar, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption]);

										//--- Episodic
										config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;

										//-- Exponential step rate by state-visits
										config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

										//- Episodic TD(lambda) with exponential alpha by state-visits
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, TDlambda, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

										//-//-//
									}

								}
							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}

	void Experiment_RandomWalk_perStep_BatchUCB(int startIndex, int endIndex, int useUCB)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 0;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ----//

		Game_RandomWalk* game = new Game_RandomWalk();
		Player_AI_RL* player = new Player_AI_RL(game);
		player->player_number = 0;
		player->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::RW_RIGHTWIN_METRICS_PER_TIMESTEPS;
		char* procedureName = "Experiment_RandomWalk_perStep_Batch()";
		char* xAxisLabel = " timStep";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations =
			2 * 1 * 5 * 2 * 2 *
			(2 + 5 + 5 + 5) * 8 * 6
			;	// = 16320

		int config_max_num_timeSteps = 10000;
		int config_max_num_repeats = 20000;

		//-- game configuration
		game->param_score_draw = 0.0;

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// control policy

		//// other TD update settings (if not already defined by the selected preset algorithm)
		player->config_trace_exploratory_reset = Player_AI_RL::ELIGIBILITY_EXPLORATORY_RESET::DISABLED;

		//// settings not defined by presets
		player->config_offpolicy_backup_recheck_best = 0;
		player->config_ExplorationLinear_maxExtMoves = 0;
		player->config_ExplorationLinear_maxEpisodes = 0;

		//// parameter values
		player->par_egreedy_e = 0.1;
		player->par_ucb_c = 1.0;
		player->par_task_gamma = 1.0;
		player->par_num_simulatedActions_perMove = config_max_num_timeSteps;
		player->par_simulated_horizon_lenght = -1;

		//// fixed default settings
		player->config_memory_limitMB = 2048;	//in MegaBytes

		//// output and visualization
		player->config_output_depth = 0;
		player->config_outputWarning_Qbounds = 0;

		// experiment runtime settings
		int show_per_repeat_output = -1;	// which metric should be printed out after each repeat (-1 disabled)

		//---- end of common settings ----//

		//-- finalize init
		Player_Engine* players[] = { player };
		game->players = players;

		if (config_IndexStart < 0)
			config_IndexStart = 0;
		if (config_IndexStart >= total_number_configurations)
			config_IndexStart = total_number_configurations - 1;
		if (config_IndexEnd >= total_number_configurations)
			config_IndexEnd = total_number_configurations - 1;
		if (config_IndexEnd < config_IndexStart)
			config_IndexEnd = total_number_configurations - 1;

		//-- prepare storage structures
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[player->config_experiment];

		Tool_Sample_Storage**** gatheredResults = new Tool_Sample_Storage***[total_number_configurations];
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[results_num_metrics];
			for (int m = 0; m < results_num_metrics; m++)
				gatheredResults[c][m] = NULL;
		}

		//-- prepare files
		int results_num_files = results_num_metrics * 2;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[2 * m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_mean.txt");
			resultsFilePrinter->filenames[2 * m + 1] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player->config_experiment][m] + "_conf.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
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
		for (int f = 0; f < results_num_files; f++){
			resultsFilePrinter->PrintI(f, "\n%s\n", procedureName);
			resultsFilePrinter->PrintI(f, "Runtime configs: indexStart %d, indexEnd %d, confidenceIntervalFactor %f\n\n", config_IndexStart, config_IndexEnd, config_confidenceInterval);
			resultsFilePrinter->PrintI(f, "  gd wl cp cPar Qin nn tn ra norm al  TDgam  TDalp  TDlam  ConfigID             ");
			for (int e = 0; e < config_max_num_timeSteps + 1; e++)
				resultsFilePrinter->PrintI(f, "  %8d", e);
			resultsFilePrinter->PrintI(f, "\n");
		}

		//---- execute batch of experiments ----//

		int num_repeats;
		double par_td_initVal;
		int config_walk_length;
		int maximum_plys;
		int par_num_simulated_actions;
		Player_AI_RL::TD_UPDATES::TYPE config_TDupdateType;
		Player_AI_RL::UPDATESTEP_ALPHA::TYPE config_alphaType;
		Game_Engine::TRANSPOSITIONS::TYPE config_transpositions;
		Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::TYPE config_rollout_assumption;
		int config_num_new_nodes_per_episode;
		//double par_td_alpha;
		//double par_td_lambda;
		char printLinePrefix[256];

		//index of current configuration
		int sInd = 0;

		//different control policy settings
		if (useUCB == 0){
			player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::EGREEDY;
		}
		else{
			player->config_control_policy = Player_AI_RL::CONTROL_POLICIES::UCB1;
		}
		for (int cpp = 0; cpp < 2; cpp++){
			if (cpp == 0){
				player->par_egreedy_e = 0.1;
				player->par_ucb_c = 1.0;
				player->config_ExplorationLinear_maxActions = 0;
			}
			else{
				player->par_egreedy_e = 0.1;
				player->par_ucb_c = 1.0;
				player->config_ExplorationLinear_maxActions = config_max_num_timeSteps;
			}
			double policyPar;
			if (player->config_control_policy == Player_AI_RL::CONTROL_POLICIES::EGREEDY)
				policyPar = player->par_egreedy_e;
			else if (player->config_control_policy == Player_AI_RL::CONTROL_POLICIES::UCB1)
				policyPar = player->par_ucb_c;

			//different game definitions (different reward functions)
			for (int gd = 1; gd < 2; gd++){
				if (gd == 0){
					game->param_score_win = 1.0;
					game->param_score_lose = 0.0;
					game->param_score_step = 0.0;
				}
				else if (gd == 1){
					game->param_score_win = 0.0;
					game->param_score_lose = -1.0;
					game->param_score_step = -1.0;
				}

				//different UCB normalization settings
				for (int ucbnorm = 0; ucbnorm < 8; ucbnorm++){
					if (ucbnorm == 0){
						//default: GLOBAL, KNOWN_RETURN, BRANCH_CURRENT_QVAL
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::GLOBAL;
						player->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::KNOWN_RETURN;
					}
					else if (ucbnorm == 1){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::GLOBAL;
						player->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::OBSERVED_RETURN;
					}
					else if (ucbnorm == 2){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL;
						player->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::BRANCH_CURRENT_QVAL;
					}
					else if (ucbnorm == 3){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL;
						player->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::CHILDREN_CURRENT_QVAL;
					}
					else if (ucbnorm == 4){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL;
						player->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::OBSERVED_RETURN;
					}
					else if (ucbnorm == 5){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL_THEN_GLOBAL;
						player->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::BRANCH_CURRENT_QVAL;
						player->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::OBSERVED_RETURN;
					}
					else if (ucbnorm == 6){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL_THEN_GLOBAL;
						player->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::CHILDREN_CURRENT_QVAL;
						player->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::OBSERVED_RETURN;
					}
					else if (ucbnorm == 7){
						player->config_ucb_norm_type = Player_AI_RL::UCB_NORMALIZATION_LOCALITY::LOCAL_THEN_GLOBAL;
						player->config_ucb_norm_local = Player_AI_RL::UCB_LOCAL_NORMALIZATIONS::OBSERVED_RETURN;
						player->config_ucb_norm_global = Player_AI_RL::UCB_GLOBAL_NORMALIZATIONS::OBSERVED_RETURN;
					}

					//different game sizes
					for (int wl = 0; wl < 5; wl++){
						if (wl == 0){
							config_walk_length = 5;
						}
						else if (wl == 1){
							config_walk_length = 7;
						}
						else if (wl == 2){
							config_walk_length = 11;
						}
						else if (wl == 3){
							config_walk_length = 15;
						}
						else{
							config_walk_length = 21;
						}
						par_num_simulated_actions = config_max_num_timeSteps;	//MUST NOT EXCEED config_max_num_episodes!
						num_repeats = config_max_num_repeats;
						maximum_plys = 10000;
						if (gd == 0){ //game type (random walk or shortest walk)
							game->maxScore = 1.0;
							game->minScore = 0.0;
						}
						else{
							game->maxScore = -(config_walk_length - 1) / 2;   //used as "known" bound for normalization, minimal length
							game->minScore = -(game->maximum_plys);           //used as "known" bound for normalization, time-step limit
						}

						//safety checks
						if (par_num_simulated_actions > config_max_num_timeSteps){
							gmp->Print("ERROR: %s: par_num_episodes > config_max_num_episodes\n", procedureName);
							return;
						}
						if (num_repeats > config_max_num_repeats){
							gmp->Print("ERROR: %s: num_repeats > config_max_num_repeats\n", procedureName);
							return;
						}

						//different initial values
						for (int qi = 0; qi < 2; qi++){
							if (qi == 0){
								par_td_initVal = 0.0;
							}
							else{
								par_td_initVal = game->maxScore - game->param_score_draw;
							}

							//different number of added nodes per episode (UCT behaviour)
							for (int nn = 0; nn < 4; nn++){
								int raMax;
								if (nn == 0){
									config_num_new_nodes_per_episode = -1;
									raMax = 1;
								}
								else if (nn == 1){
									config_num_new_nodes_per_episode = 1;
									raMax = 3;
								}
								else if (nn == 2){
									config_num_new_nodes_per_episode = 5;
									raMax = 3;
								}
								else{
									config_num_new_nodes_per_episode = 10;
									raMax = 3;
								}

								//with/without transpositions
								for (int tn = 0; tn < 2; tn++){
									if (tn == 0){
										config_transpositions = Game_Engine::TRANSPOSITIONS::STATES;
									}
									else{
										config_transpositions = Game_Engine::TRANSPOSITIONS::DISABLED;
										if (raMax > 2)
											raMax = 2;
									}

									//different rollout assumptions						
									for (int ra = 0; ra < raMax; ra++){
										if (ra == 0){
											config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_INITIAL;
										}
										else if (ra == 1){
											config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_ZERO;
										}
										else if (ra == 2){
											config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::EQUAL_LAST_MEMORIZED;
										}
										else if (ra == 3){
											config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_NEXT_MEMORIZED;
										}
										else{
											config_rollout_assumption = Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::CONVERGED_TO_LAST_MEMORIZED;
										}

										sprintf_s(printLinePrefix, "  %2d %2d %2d %4.2f %3.1f %2d %2s %2s %4d", gd, config_walk_length, cpp, policyPar, par_td_initVal, config_num_new_nodes_per_episode, Game_Engine::TRANSPOSITIONS::stringLabels2char[config_transpositions], Player_AI_RL::ROLLOUT_VALUE_ASSUMPTIONS::stringLabels2char[config_rollout_assumption], ucbnorm);

										//-//-// single set of different algorithms

										//--- Episodic
										config_TDupdateType = Player_AI_RL::TD_UPDATES::BATCH_EPISODIC;

										//-- Exponential step rate by state-visits
										config_alphaType = Player_AI_RL::UPDATESTEP_ALPHA::MONTE_CARLO;

										//- First-visit MC
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 0, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 1.00, Player_AI_RL::PRESET_ALGORITHMS::FIRSTVISIT_MC_ONPOLICY, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

										//- Episodic TD(lambda) with exponential alpha by state-visits
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.99, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.90, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.50, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.10, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);
										Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(&sInd, 1, num_repeats, config_walk_length, maximum_plys, -1, par_td_initVal, 0.00, 0.00, Player_AI_RL::PRESET_ALGORITHMS::TD_LAMBDA, config_TDupdateType, Player_AI_RL::ELIGIBILITY_TRACES::REPLACING, config_alphaType, config_transpositions, config_rollout_assumption, config_num_new_nodes_per_episode, game, player, procedureName, xAxisLabel, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults, resultsFilePrinter, printLinePrefix, config_IndexStart, config_IndexEnd);

										//-//-//
									}
								}
							}
						}
					}
				}
			}
		}

		//---- end of experiments ----//

		//-- clean up
		delete(resultsFilePrinter);
		delete[] gatheredResults;
		delete(player);
		delete(game);

	}

	// measuerements for Experiment4 : Tic Tac Toe, two-player adversary classic game
	//		- learning with self-play
	//		- building a minmax tree
	//		- planning
	//		- limited computation budged (number of timesteps)
	//		- retaining memorized values (tree) between external moves (so, tree is not deleted after each move)
	//	control variables : lambda, own_ucb_C, opponent ucb_C, computational budget of num timesteps (equal for both players)
	//	measured variables : average win rate against UCT player from a single game, where 50% of games played as player1 and 50% times as player2

	void Experiment_TicTacToe_perStep_BatchUCB(int startIndex, int endIndex)
	{

		//-- EXECUTION SETTINGS --//
		int config_IndexStart;
		int config_IndexEnd;

		//set here the starting/ending configuration serial ID to be computed -> useful if running the experiment on multiple tasks (compile multiple executables to shorten comuptation time)
		if ((startIndex == -1) && (endIndex == -1)){
			config_IndexStart = 0;	//with which index to start the experiments, -1 means from start
			config_IndexEnd = -1;	//with which to end the experiments (including the specified index), -1 means until end
		}
		else{
			config_IndexStart = startIndex;
			config_IndexEnd = endIndex;
		}

		//what will be the calculated confidence interval
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99;

		//output settings
		bool config_show_individual_final_output = 1;

		//-- END OF EXECUTION SETTINGS --//

		//---- common settings for this experiment ----//

		Game_TicTacToe* game = new Game_TicTacToe();
		Player_AI_RL* player1 = new Player_AI_RL(game);		//THIS IS THE EVALUATED PLAYER <- THE RESULTS APPLY FOR THIS PLAYER
		Player_AI_RL* player2 = new Player_AI_RL(game);		//THIS IS THE OPPONENT PLAYER
		Player_AI_RL* players[2] = { player1, player2 };
		player1->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::TTT_METRICS_PER_TIMESTEPS;
		player2->config_experiment = Player_AI_RL::EXPERIMENTAL_SETTINGS::TTT_METRICS_PER_TIMESTEPS;
		char* procedureName = "Experiment_TicTacToe_perStep_BatchUCB()";
		char* xAxisLabel = "tStp/mov";

		//CHANGE HERE IF YOU ADD/REMOVE SOME EXPERIMENTAL CONFIGURATIONS
		int total_number_configurations = 6;

		int config_max_num_repeats = 10000;	//a single repeat consists of two games, one from each starting position
			//1000   repeats ~ std. error 1.00%
			//10000  repeats ~ std. error 0.33%
			//20000  repeats ~ std. error 0.25%
			//100000 repeats ~ std. error 0.10%
			//1M	 repeats ~ std. error 0.03%

		int config_timeStepsPerMove_values[] = {
			1, 2, 3, 4, 5, 6, 7, 8, 9, 
			10, 20, 30, 40, 50, 60, 70, 80, 90, 
			100, 200, 300, 400, 500, 600, 700, 800, 900,
			1000
			};
		int config_num_timeStepsPerMove_values = 28;	//approximately 35 seconds of computation for 1000 repeats (year 2015)
		//int config_timeStepsPerMove_values[] = {
		//	100		//opponent optimal C=0.2
		//	//1000	//opponent optimal C=0.4
		//	};
		//int config_num_timeStepsPerMove_values = 1;	

		//-- game configuration

		//-- player configuration 

		//// for description and list of possible parameters see "Player_AI_RL.hpp"

		//// evaluated player settings (player1)
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
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			gatheredResults[c] = new Tool_Sample_Storage**[config_num_timeStepsPerMove_values];
			for (int m = 0; m < config_num_timeStepsPerMove_values; m++){
				gatheredResults[c][m] = new Tool_Sample_Storage*[results_num_metrics];
				for (int s = 0; s < results_num_metrics; s++){
					gatheredResults[c][m][s] = new Tool_Sample_Storage(0);	//do not store individual samples, but compute only descriptive statistics (online)
				}
			}
		}

		//-- prepare files
		int results_num_files = results_num_metrics;
		MultiPrinter* resultsFilePrinter = new MultiPrinter(results_num_files, true, "");
		for (int m = 0; m < results_num_metrics; m++){
			resultsFilePrinter->filenames[m + 0] = (executable_filename_str + program_start_time_output_str + "__metric_" + Player_AI_RL::experimentLabels[player1->config_experiment][m] + "_mean.txt");
		}

		if (resultsFilePrinter->Create_Output_Files() != 0){
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
		for (int f = 0; f < results_num_files; f++){
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

		////different UCB
		//for (int cucb = 0; cucb < 201; cucb++){
		//	player1->par_ucb_c = (double)cucb / 100.0;
		//	player2->par_ucb_c = (double)cucb / 100.0;
		//for (int cucb = 0; cucb < 101; cucb++){
		//	player1->par_ucb_c = (double)(cucb) / 100.0;
			//player2->par_ucb_c = 0.2;
			//player2->par_ucb_c = 0.4;
		for (int cucb = 0; cucb < 1; cucb++){
			if (cucb == 0){
				player1->par_ucb_c = 1.0;
				player2->par_ucb_c = 1.0;
				//player1->par_ucb_c = 0.1;
				//player2->par_ucb_c = 0.2;
			}
			else if (cucb == 1){
				player1->par_ucb_c = 2.0;
				player2->par_ucb_c = 2.0;
			}
			else if (cucb == 2){
				player1->par_ucb_c = 0.5;
				player2->par_ucb_c = 0.5;
			}
			else if (cucb == 3){
				player1->par_ucb_c = 0.25;
				player2->par_ucb_c = 0.25;
			}

			////different lambda for player1
			//for (int cl = 19; cl >= 0; cl--){
			//	if (cl < 10)
			//		player1->par_td_lambda = (double)(cl) / 10.0;				//from 0.0 to 0.9 with step 0.1
			//	else if (cl < 19)
			//		player1->par_td_lambda = 0.9 + (double)(cl - 9) / 100.0;	//from 0.91 to 0.99 with step 0.01
			//	else
			//		player1->par_td_lambda = 1.0;
			for (int cl = 0; cl < 6; cl++){
				if (cl == 0){
					player1->par_td_lambda = 1.0;
					//player1->par_td_lambda = 0.7;
				}
				else if (cl == 1){
					player1->par_td_lambda = 0.999;
				}
				else if (cl == 2){
					player1->par_td_lambda = 0.99;
				}
				else if (cl == 3){
					player1->par_td_lambda = 0.9;
				}
				else if (cl == 4){
					player1->par_td_lambda = 0.1;
				}
				else if (cl == 5){
					player1->par_td_lambda = 0.0;
				}
			//for (int cl = 0; cl < 101; cl++){
			//	player1->par_td_lambda = (double)(cl) / 100.0;

				// prepare output line string
				sprintf_s(printLinePrefix, "  %4.2f %4.2f %5.3f", player1->par_ucb_c, player2->par_ucb_c, player1->par_td_lambda);

				// increase external counter
				sInd++;
				int configurationSerialID = sInd - 1;

				//safety check
				if (configurationSerialID > total_number_configurations){
					gmp->Print("ERROR: Experiment_TicTacToe_perStep_BatchUCB(): configurationSerialID %d > total_number_configurations %d; ABORTING\n", configurationSerialID, total_number_configurations);
					return;
				}
				//consider the execution settings
				if (!((configurationSerialID < config_IndexStart) || (configurationSerialID > config_IndexEnd) || (config_IndexEnd < config_IndexStart))){

					//different number of simulated steps per external move
					for (int cnt_stpsPerMove = 0; cnt_stpsPerMove < config_num_timeStepsPerMove_values; cnt_stpsPerMove++){
						player1->par_num_simulatedActions_perMove = config_timeStepsPerMove_values[cnt_stpsPerMove];
						player2->par_num_simulatedActions_perMove = config_timeStepsPerMove_values[cnt_stpsPerMove];

						//compose string
						char experimentName[256];
						sprintf_s(experimentName, "//--  %s : configuration C%d steps%d --//", procedureName, configurationSerialID, config_timeStepsPerMove_values[cnt_stpsPerMove]);

						//execute experiment
						Experiment_SingleGame(game, players, experimentName, xAxisLabel, config_max_num_repeats, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults[configurationSerialID][cnt_stpsPerMove]);
					}

					//write results to files
					for (int m = 0; m < results_num_metrics; m++){
						resultsFilePrinter->PrintI(m + 0, "%s  %5.3f  %5.3f  C%04d_A%01d_a%03d_L%04d  ", printLinePrefix, players[0]->par_task_gamma, players[0]->par_td_alpha, configurationSerialID, 0, (int)(players[0]->par_td_alpha * 100), (int)(players[0]->par_td_lambda * 1000));
						for (int s = 0; s < config_num_timeStepsPerMove_values; s++){
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
		for (int c = config_IndexStart; c <= config_IndexEnd; c++){
			for (int s = 0; s < config_num_timeStepsPerMove_values; s++){
				for (int m = 0; m < results_num_metrics; m++){
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
		Tool_Sample_Storage** externalStorage
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
		for (int p = 0; p < game->number_players; p++){
			gmp->Print("\nPlayer %d",p+1);
			players[p]->Output_Settings();
		}

		//prepare storage
		int results_num_metrics = Player_AI_RL::experimentNumMetrics[players[0]->config_experiment];
		Tool_Sample_Storage** results;
		if (externalStorage == NULL){
			results = new Tool_Sample_Storage*[results_num_metrics];
			for (int j = 0; j < results_num_metrics; j++){
				results[j] = new Tool_Sample_Storage(0);		//do not store individual samples, but compute only descriptive statistics (online)
			}
		}
		else{
			results = externalStorage;
		}

		//prepare timers		
		double* times = new double[2];
		players[0]->experiment_timers = times;

		//experiment starting time
		times[0] = getCPUTime();

		//prepare temporary storage for function Evaluate_Players()
		double* lastWinCounts = new double[3];

		//Debug: test with UCT player (first implementation)
		Player_AI_UCT* UCTplayer = new Player_AI_UCT(game);
		UCTplayer->UCT_param_IterNum = players[1]->par_num_simulatedActions_perMove;
		UCTplayer->UCT_param_SimMoveNum = players[1]->par_num_simulatedActions_perMove;
		UCTplayer->UCT_param_C = players[1]->par_ucb_c / 2.0;

		//execute experiments (with initial positions)
		Player_Engine* positionedPlayers[2];
		game->players = positionedPlayers;
		positionedPlayers[0] = players[0];
		positionedPlayers[1] = players[1];
		//positionedPlayers[1] = UCTplayer;	//DEBUG
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
		for (int j = 0; j < results_num_metrics; j++){
			////the sum and mean should have already been calculated in Player_AI_RL->Get_Move()
			////results[j][i]->Calc_Sum();
			////results[j][i]->Calc_Mean();
			//results[j]->Calc_Confidence(config_confidenceInterval);
		}

		//final output
		if (show_final_output){
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
		if (externalStorage == NULL){
			for (int j = 0; j < results_num_metrics; j++){
				delete(results[j]);
			}
			delete[] results;
		}
		delete[] times;
		delete[] lastWinCounts;
	}



	// measuerements for Experiment5: two-player adversary games: Connect4, Hex, Gomoku
	//		- learning with self-play
	//		- building a minmax tree
	//		- planning
	//		- limited computation budged (number of timesteps)
	//		- retaining memorized values (tree) between external moves (so, tree is not deleted after each move)
	//	control variables : lambda, own_ucb_C, opponent ucb_C, computational budget of num timesteps (equal for both players)
	//	measured variables : average win rate against UCT player from a single game, where 50% of games played as player1 and 50% times as player2

	void Experiment5_perStep_BatchUCB(int experimentType, int input_repeats, Game_Engine* game, const int timeSteps, double opponentUCBC, double evaluatedUCBC, double evaluatedTDlam, int startIndex, int endIndex)
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

		if ((experimentType == 1) || (experimentType == 2))
		{
			total_number_configurations = 41;
			cucbMax = 41;
			clMax = 1;
		}
		else if ((experimentType == 3) || (experimentType == 4))
		{
			total_number_configurations = 21;
			cucbMax = 1;
			clMax = 21;
		}
		else if (experimentType == 5)
		{
			total_number_configurations = 41 * 21;
			cucbMax = 41;
			clMax = 21;
		}
		else if (experimentType == 6)
		{
			total_number_configurations = 1;
			cucbMax = 1;
			clMax = 1;
		}


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
				player1->par_ucb_c = (double)cucb / 20.0;
				player2->par_ucb_c = (double)cucb / 20.0;
			}
			else if ((experimentType == 2) || (experimentType == 5))
			{
				player1->par_ucb_c = (double)cucb / 20.0;
				player2->par_ucb_c = opponentUCBC;
			}
			else if ((experimentType == 3) || (experimentType == 4) || (experimentType == 6))
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
				else if ((experimentType == 3) || (experimentType == 4) || (experimentType == 5))
				{
					player1->par_td_lambda = (double)(cl) / 20.0;
					player2->par_td_lambda = 1.0;
				}
				else if (experimentType == 6)
				{
					player1->par_td_lambda = evaluatedTDlam;
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
				sprintf_s(printLinePrefix, "  %4.2f %4.2f %5.3f", player1->par_ucb_c, player2->par_ucb_c, player1->par_td_lambda);

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
						Experiment_SingleGame(game, players, experimentName, xAxisLabel, config_max_num_repeats, show_per_repeat_output, config_confidenceInterval, config_show_individual_final_output, gatheredResults[configurationSerialID][cnt_stpsPerMove]);
					}

					//write results to files
					for (int m = 0; m < results_num_metrics; m++) {
						resultsFilePrinter->PrintI(m + 0, "%s  %5.3f  %5.3f  C%04d_A%01d_a%03d_L%04d  ", printLinePrefix, players[0]->par_task_gamma, players[0]->par_td_alpha, configurationSerialID, 0, (int)(players[0]->par_td_alpha * 100), (int)(players[0]->par_td_lambda * 1000));
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
}