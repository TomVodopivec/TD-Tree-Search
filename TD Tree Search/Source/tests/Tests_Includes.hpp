#ifndef _TOM_TESTS_INCLUDES_
#define _TOM_TESTS_INCLUDES_

//include C libraries

#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>

//include other

#include "..\games\Game_RandomWalk.hpp"

#include "..\games\Game_ConnectFour.hpp"
#include "..\games\Game_Gomoku.hpp"
#include "..\games\Game_TicTacToe.hpp"
#include "..\games\Game_Hex.hpp"

#include "..\core\Player_Engine.hpp"

#include "..\players\Player_AI_Simple.hpp"
#include "..\players\Player_AI_UCT.hpp"
#include "..\players\Player_AI_UCT_Reinforce.hpp"
#include "..\players\Player_AI_UCT_AMAF.hpp"
#include "..\players\Player_AI_UCT_RAVE.hpp"
#include "..\players\Player_AI_UCT_TomTest.hpp"
#include "..\players\Player_AI_TDUCT.hpp"
#include "..\players\Player_AI_RL.hpp"

#include "..\optimizers\Tom_Lrp.hpp"

#include "..\tools\Tom_Sample_Storage.hpp"
#include "..\tools\Support_MultiPrint.hpp"
#include "..\tools\Support_InputFile.hpp"
#include "..\tools\Support_GetCPUTime.hpp"

#endif
