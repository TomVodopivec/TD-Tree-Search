#ifndef _TOM_MAIN_
#define _TOM_MAIN_

//compiler warning ignores
//#define _CRT_SECURE_NO_WARNINGS

//includes
#include "tests\Tests_Includes.hpp"
#include "tests\Tests_Old.hpp"
#include "tests\Tests_TDUCT.hpp"
#include "tests\Tests_TDMCTS.hpp"
#include "tests\Tests_TDMCTSnew.hpp"
#include "tests\Tests_TDMCTSnew2.hpp"

using namespace std;


//defines
#define TOM_GLOBAL_DUPLICATE_OUTPUT_TO_FILE		1

#define TOM_OUTPUT_FOLDER				(".\\Runtime_Output\\")
#define TOM_OUTPUT_DATA_FILE_TEXT_TAG	("output_data")
#define TOM_OUTPUT_CONF_FILE_TEXT_TAG	("output_conf")

//compatiblity defines
// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif
// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif


//global variables
struct tm * program_start_time;
string program_start_time_output_str;
string executable_filename_str;
string output_data_filename;
string output_conf_filename;
string extern_call_command;

MultiPrinter * gmp;

#endif