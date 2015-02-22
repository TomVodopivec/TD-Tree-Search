//include header
#include "main.hpp"

//prototypes
void Main_Testing();


//---- WRITE OWN CODE IN THIS PROCEDURE ----
void Main_Testing()
{

	Tests_TDMCTS::main();



	//Tests_Old::Benchmark();
	//Tests_Old::TicTacToe_Testing();
	//Tests_Old::Gomoku_Testing();
	//Tests_Old::ConnectFour_Testing();
	//Tests_Old::FileRead_Test();
	//Tests_Old::Lotka_Testing();
	//Tests_Old::EEG_Testing();
	//Tests_Old::AMAF_Testing();
	//Tests_Old::Hex_Testing();

	//Tests_Old::FuncApp_test();
	//Tests_Old::LRP_test_basic();
	//Tests_Old::LRP_test_linearDW();
	//Tests_Old::LRP_test_exponentDW();
	//Tests_Old::LRP_test_linAB_exponentDW();

	//Tests_Old::LRP_test_wrapper();
	//Tests_Old::LRP_test_linAB_exponentDW_FunApp();

	//Tests_Old::LRP_test_linAB_exponentDW_FunApp_MulParams();
	//Tests_Old::Param_Impact_Testing_v06();

	//Tests_Old::TicTacToe_Implementation_Test1();
	//Tests_Old::Go_Testing();

	//Tests_TDUCT::Fixed_Play_Testing();				//evaluate fixed settings (no LRP)
	//Tests_TDUCT::LRP_improved_v1();				//single LRP run
	//Tests_TDUCT::LRP_test_wrapperMultiPar();		//multiple LRP repeats

	//Tests_TDUCT::Tom_Paper1_tests();
}

//-----------------------------------------


//main procedure
int main(int argc, char* argv[])
{
	//save program start time to global variable
#if ((_WIN32 || _WIN64) && _MSC_VER)
	__time64_t long_time;
	_time64( &long_time );								// Get time as 64-bit integer.
	program_start_time = new struct tm();
    _localtime64_s( program_start_time, &long_time );	// Convert to local time.
#else
	time_t long_time;
	time( &long_time );
    program_start_time = localtime( &long_time);					// Convert to local time.
#endif

	char tmpString[256];
	sprintf_s(tmpString, "__%4d-%d%d-%d%d-%d%d-%d%d-%d%d",
					program_start_time->tm_year+1900,
					(int)(program_start_time->tm_mon+1) / 10,
					(int)(program_start_time->tm_mon+1) % 10,
					(int)(program_start_time->tm_mday) / 10,
					(int)(program_start_time->tm_mday) % 10,
					(int)(program_start_time->tm_hour) / 10,
					(int)(program_start_time->tm_hour) % 10,
					(int)(program_start_time->tm_min) / 10,
					(int)(program_start_time->tm_min) % 10,
					(int)(program_start_time->tm_sec) / 10,
					(int)(program_start_time->tm_sec) % 10
				);
	program_start_time_output_str = string(tmpString);

	//set output filenames
	executable_filename_str = string(argv[0]);
	output_data_filename = (string)TOM_OUTPUT_DATA_FILE_TEXT_TAG + program_start_time_output_str + ".txt";
	output_conf_filename = (string)TOM_OUTPUT_CONF_FILE_TEXT_TAG + program_start_time_output_str + ".txt";

	//------------------------------------------------
	//PROGRAM EXECUTION settings

#if(TOM_OUTPUT_TO_MATLAB)
	//generate filename
	FILE* tmpStream;

	//create directory (if not already) and redirect standard output to ".\Runtime_Output\output.txt"
	if (CreateDirectoryA(".\\Runtime_Output", NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
		tmpStream = freopen((TOM_OUTPUT_FOLDER + output_data_filename).c_str() ,"w",stdout);
	}else{		// Failed to create directory.
		printf("WARNING: unable to create 'Runtime_Output' directory, stdout will not be redirected!");	
	}
#endif

	//init global (multi) printer object
#if(TOM_GLOBAL_ENABLE_MCTS_OUTPUT_LEVEL)
	gmp = new MultiPrinter(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS+1, true, "");
	for(int i = 0; i < TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS; i++){
		stringstream tmpStr1;
			
		if((i < 10)&&(TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS > 9))
			tmpStr1 << "__MCTSlvl0" << i;
		else
			tmpStr1 << "__MCTSlvl" << i;

		gmp->filenames[i] = (string(argv[0]) + string(tmpString) + tmpStr1.str() + ".txt");
	}
	gmp->filenames[TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS] = (string(argv[0]) + string(tmpString) + "__main.txt");
	gmp->selected_file = TOM_GLOBAL_MCTS_OUTPUT_NUM_LEVELS;	//set default duplicate output to file "__main.txt"
	if( gmp->Create_Output_Files() != 0 ){
		fprintf(stdout, "Program abort by Create_Output_Files()\n");
		fflush(stdout);
		cout << endl << "Press any key to exit.";
		cin.get();
		exit(EXIT_FAILURE);
	}
#else
#if(!TOM_GLOBAL_DUPLICATE_OUTPUT_TO_FILE)
	gmp = new MultiPrinter(1, false, string(argv[0]) + string(tmpString));
#else
	gmp = new MultiPrinter(1, true, string(argv[0]) + string(tmpString));
	//gmp->filenames[0] = (string(argv[0]) + string(tmpString) + ".txt");
	if( gmp->Create_Output_Files() != 0 ){
		fprintf(stdout, "Program abort by Create_Output_Files()\n");
		fflush(stdout);
		cout << endl << "Press any key to exit.";
		cin.get();
		exit(EXIT_FAILURE);
	}
	//if(argc > 0)
	//	gmp->Print("%s\n\n",gmp->filenames[0].c_str());
	//	printf("%s\n\n",gmp->filenames[0].c_str());
#endif
#endif

	unsigned int randomSeed;
#if(TOM_DEBUG == 1)
	randomSeed = 0;
#else
	randomSeed = (unsigned int)time(NULL);
#endif
	srand(randomSeed);
	gmp->Print("Program executed with random seed value %d\n\n", randomSeed);

	//------------------------------------------------
	//USER CODE
	Main_Testing();

	//------------------------------------------------
	//MAIN EXIT PROCEDURE

	gmp->Print("\n\n");
	//gmp->Close_Output_Files();
	delete(gmp);

#if(TOM_OUTPUT_TO_MATLAB)
	fclose(stdout);
	tmpStream = freopen("CONOUT$", "w", stdout);	//redirect standard output back to console
	//call Matlab script for results visualization
	system((extern_call_command + " " + output_data_filename + " " + output_conf_filename + " " + program_start_time_output_str).c_str());	
#else
	if((argc > 1)&&(argv[1][0] == '1')){
		//do not prompt for key-press
	}else{
		fflush(stdout);
		cout << endl << "Press any key to exit.";
		cin.get();
	}

#endif

}