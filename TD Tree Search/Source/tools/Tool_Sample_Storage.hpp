#ifndef _TOOL_SAMPLE_STORAGE_
#define _TOOL_SAMPLE_STORAGE_

//includes
#include <cmath>
#include "..\tools\Support_MultiPrint.hpp"
#include "..\tools\Support_get_median_torben.hpp"
#include "..\tools\Support_get_median_quickselect.hpp"

//external global variables
extern MultiPrinter * gmp;	//multiprinter object defined in main.hpp

// -----------------------------------------------------------//
// Measurements storage class -- header

class Tool_Sample_Storage
{
public:

	//global consts
	static const double CONFIDENCE_INTERVAL_T_80;
	static const double CONFIDENCE_INTERVAL_T_90;
	static const double CONFIDENCE_INTERVAL_T_95;
	static const double CONFIDENCE_INTERVAL_T_99;
	static const double CONFIDENCE_INTERVAL_T_999;

	//consts - default values - parameters
	static const bool SAMPLE_STORAGE_ADD_SAMPLE_CALC_SUM =		true;
	static const bool SAMPLE_STORAGE_ADD_SAMPLE_CALC_MEAN =		false;
	static const bool SAMPLE_STORAGE_CALC_MEDIAN_MODIFY =		false;
	static const bool SAMPLE_STORAGE_CALC_MEDIAN_BELOW_MIDDLE = false;

	//consts - debug and protection
	static const bool SAMPLE_STORAGE_ADD_SAMPLE_SAFETY_CHECK =	true;

	Tool_Sample_Storage(int new_max_samples);
	virtual ~Tool_Sample_Storage();

	void Delete_Samples();
	void Reset();
	void Reset(int new_max_samples);

	void Add_Sample(double value, const bool calculate_sum = SAMPLE_STORAGE_ADD_SAMPLE_CALC_SUM, const bool calculate_mean = SAMPLE_STORAGE_ADD_SAMPLE_CALC_MEAN, const bool safety_check = SAMPLE_STORAGE_ADD_SAMPLE_SAFETY_CHECK);

	double	Calc_All();
	double	Calc_AllExceptSum();

	double	Calc_Sum();
	double	Calc_MeanDev();
	double	Calc_Mean();
	double	Calc_Dev();

	double	Calc_Mean_On_Interval(int index_start, int index_end);
	double	Calc_MeanDev_On_Interval(int index_start, int index_end, double* output_mean, double* output_dev);	//returns average

	double	Calc_Confidence(double t_constant = CONFIDENCE_INTERVAL_T_95);

	double	Calc_Median(const bool allow_modify_array = SAMPLE_STORAGE_CALC_MEDIAN_MODIFY, const bool if_even_number_select_below_middle = SAMPLE_STORAGE_CALC_MEDIAN_BELOW_MIDDLE);

	int max_samples;	//maximum number of samples: array length
	double* samples;	//pointer to array of samples

	int n;				//current number of samples

	double sum;			//sum
	double mean;		//average value
	double dev;			//std. deviation
	double conf;		//confidence interval
	double median;		//median

private:
	void Init(int new_max_samples);

};

#endif