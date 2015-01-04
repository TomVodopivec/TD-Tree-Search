#ifndef _TOM_TESTS_OLD_
#define _TOM_TESTS_OLD_

#include "..\tests\Tests_Includes.hpp"

namespace Tests_Old
{

	void ConnectFour_Testing();
	void Gomoku_Testing();
	void TicTacToe_Testing();
	void TicTacToe_Implementation_Test1();
	void Hex_Testing();
	void Go_Testing();
	void Benchmark();
	void FileRead_Test();
	void AMAF_Testing();
	void Param_Impact_Testing_v06();
	void AMAF_Testing_Extensive(Game_Engine* game, Player_Engine** players, int simulations, int repeats, int games, const bool disable_sim_set = false);

	void FuncApp_test();
	void LRP_test_basic();
	void LRP_test_linearDW();
	void LRP_test_exponentDW();
	void LRP_test_linAB_exponentDW(double* score_avg, double* score_avg_last10, double* output_param);

	void LRP_test_linAB_exponentDW_FunApp(double* score_avg = NULL, double* score_avg_last10 = NULL, double* last_param_val = NULL, bool force_setting_output = false);
	void LRP_test_linAB_exponentDW_FunApp_MulParams(double* score_avg = NULL, double* score_avg_last10 = NULL, double** last_param_val = NULL, bool force_setting_output = false, int num_output_params = 0);

	void Tom_Sample_Storage_Test();

}

#endif