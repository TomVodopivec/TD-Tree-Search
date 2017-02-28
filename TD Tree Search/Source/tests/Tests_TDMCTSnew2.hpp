#ifndef _TOM_TESTS_TDMCTSNEW_
#define _TOM_TESTS_TDMCTSNEW__TOM_TESTS_TDMCTS_

#include "..\tests\Tests_Includes.hpp"

extern string program_start_time_output_str;
extern string executable_filename_str;

// 2017.02.05
namespace Tests_TDMCTSnew2
{

  void main();

  void Experiment_SingleGame(
    Game_Engine* game,
    Player_AI_RL** players,
    char* procedureName,
    char* xAxisLabel,
    int num_repeats,
    int show_per_repeat_output,
    double config_confidenceInterval = Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_95,
    bool show_final_output = true,
    Tool_Sample_Storage** externalStorage = NULL,
    double additionalPar = 0.0
    );

  void Experiment5_perStep_BatchUCB(int experimentType, int input_repeats, Game_Engine* game, const int timeSteps, double opponentUCBC, double evaluatedUCBC, double evaluatedTDlam = NULL, int startIndex = -1, int endIndex = -1, double additionalPar = 0.0);

}

#endif