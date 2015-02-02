#ifndef _TOM_TESTS_TDMCTS_
#define _TOM_TESTS_TDMCTS_

#include "..\tests\Tests_Includes.hpp"


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
}

#endif