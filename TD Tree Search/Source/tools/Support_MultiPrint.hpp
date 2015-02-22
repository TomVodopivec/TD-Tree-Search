/**
Class with functions for printing simultaneously to multiple outputs (e.g. file and stdout)

*/

#ifndef _TOM_SUPPORT_MULTIPRINT_
#define _TOM_SUPPORT_MULTIPRINT_

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdarg>
#include <varargs.h>

#ifdef _MSC_VER
#define va_copy(d,s) ((d) = (s))
#endif

using namespace std;

class MultiPrinter
{

public:
	
	int num_files;

	bool print_also_to_file;
	int  selected_file;
	string * filenames;

	MultiPrinter(const int set_num_files = 0, bool set_print_to_file = false, string base_filename = "");
	~MultiPrinter();

	virtual int  Create_Output_Files(int num_files_to_create = 0);	//0 means that all files will be created (num_files)
	virtual void Flush(const bool only_stdout = false);
	virtual void Close_Output_Files();

	virtual void Print(const char* format, ...);
	virtual void Print(FILE * output1, const char* format, ...);
	virtual void Print(int id_file1, const char* format, ...);
	
	virtual void PrintI(FILE * output1, const char* format, ...);					//ignores print_also_to_file
	virtual void PrintI(int id_file1, const char* format, ...);						//ignores print_also_to_file

	virtual void Print(FILE * output1, FILE * output2, const char* format, ...);	//ignores print_also_to_file
	virtual void Print(int id_file1, int id_file2, const char* format, ...);		//ignores print_also_to_file
	virtual void Print(FILE * output1, int id_file2, const char* format, ...);		//ignores print_also_to_file
	virtual void Print(int id_file1, FILE * output2, const char* format, ...);		//ignores print_also_to_file


private:

	FILE ** output_files;

};

//// EXAMPLE HOW TO PRINT OUT A VARIABLE NAME AND ITS VALUE
////
////#include <stdio.h>
////
////#define PRINTER(name) printer(#name, (name))
////
////void printer(char *name, int value) {
////	printf("name: %s\tvalue: %d\n", name, value);
////}
////
////int main(int argc, char* argv[]) {
////	int foo = 0;
////	int bar = 1;
////
////	PRINTER(foo);
////	PRINTER(bar);
////
////	return 0;
////}
////
////
////name: foo   value : 0
////name : bar   value : 1

//////EXAMPLE HOW TO USE BOOST TO DEFINE ENUMS WITH STRINGS
////
////#include <boost/preprocessor.hpp>
////
////#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem)    \
////    case elem: return BOOST_PP_STRINGIZE(elem);
////
////#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)                \
////enum name {
////\
////	BOOST_PP_SEQ_ENUM(enumerators)                                        \
////};                                                                        \
////	\
////	inline const char* ToString(name v)                                       \
////{                                                                         \
////	switch (v)                                                            \
////{                                                                     \
////	BOOST_PP_SEQ_FOR_EACH(\
////	X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE, \
////	name, \
////	enumerators                                                   \
////	)                                                                 \
////	default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         \
////}                                                                     \
////}
/////
/////DEFINE_ENUM_WITH_STRING_CONVERSIONS(OS_type, (Linux)(Apple)(Windows))
////#include <iostream>
////
////int main()
////{
////	OS_type t = Windows;
////	std::cout << ToString(t) << " " << ToString(Apple) << std::endl;
////}


#endif