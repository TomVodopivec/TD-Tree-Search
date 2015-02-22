#ifndef _TOM_TESTS_TDMCTS_
#define _TOM_TESTS_TDMCTS_

#include "..\tests\Tests_Includes.hpp"

extern string program_start_time_output_str;
extern string executable_filename_str;

namespace Tests_TDMCTS
{

	void main();

	void LRP_test_wrapper();
	void LRP_test_wrapperMultiPar();

	void LRP_improved_v1(double* score_avg = NULL, double* score_avg_last10 = NULL, double** last_param_val = NULL, bool force_setting_output = false, const int set_final_evaluations = 750, double* avg_num_games = NULL, double* final_eval_score = NULL);

	void Fixed_Play_Testing(double input_param1 = 0.0, double input_param2 = 0.0);
	
	void UnitTest_RandomWalk();
	void UnitTest_PlayerRL();
	void UnitTest_Two_PlayerRL();
	void UnitTest_PlayerRL_singleMove();

	void Experiment_RandomWalk_perEpisode();
	void Experiment_RandomWalk_perEpisode_CommonSettings(Game_RandomWalk* game, Player_AI_RL* player);
	void Experiment_RandomWalk_perTimeStep();
	void Experiment_RandomWalk_perTimeStep_CommonSettings(Game_RandomWalk* game, Player_AI_RL* player);

	void Experiment_SingleExternalMove(
		Game_RandomWalk* game,
		Player_AI_RL* player,
		char* procedureName,
		char* xAxisLabel,
		int num_repeats,
		int show_per_repeat_output,
		int results_num_steps,
		double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_95,
		bool show_final_output = true,
		Tool_Sample_Storage*** externalStorage = NULL
		);

	void Experiment_RandomWalk_perEpisode_Batch(int startIndex = -1, int endIndex = -1);
	void Experiment_RandomWalk_perEpisode_Batch_RunConfiguration(
		int* address_configurationSerialID,
		int algorithmSerialID,
		int config_walk_length,
		int maximum_plys,
		int par_num_episodes,
		int num_repeats,
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
		);

}

#endif