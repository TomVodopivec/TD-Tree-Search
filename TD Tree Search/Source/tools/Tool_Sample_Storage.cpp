#include "Tool_Sample_Storage.hpp"

//TEMPORARILY MOVED HERE FROM HEADER: is already valid by the c++11 standard (in-header static const double initialization), but is not yet implemented in VS2013
const double Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_80 = 1.282;
const double Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_90 = 1.645;
const double Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_95 = 1.960;
const double Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_99 = 2.576;
const double Tool_Sample_Storage::CONFIDENCE_INTERVAL_T_999 = 3.291;

// Measurements storage class -- implementation

Tool_Sample_Storage::Tool_Sample_Storage(int new_max_samples)
{
	Init(new_max_samples);
}

Tool_Sample_Storage::~Tool_Sample_Storage()
{
	if (samples != NULL)
		delete[] samples;
}

void Tool_Sample_Storage::Init(int new_max_samples)
{
	this->max_samples = new_max_samples;
	samples = new double[max_samples];
	Reset();
}

void Tool_Sample_Storage::Reset()
{
	n = 0;
	sum = 0.0;
	mean = 0.0;
	dev = 0.0;
	conf = 0.0;
}

void Tool_Sample_Storage::Delete_Samples()
{
	delete[] samples;
	samples = NULL;
}

void Tool_Sample_Storage::Reset(int new_max_samples)
{
	delete[] samples;
	Init(new_max_samples);
}

void Tool_Sample_Storage::Add_Sample(double value, const bool calculate_sum, const bool calculate_mean, const bool safety_check)
{
	//check for index out of bounds
	if (safety_check){
		if ((n >= max_samples) || (n < 0)){
			gmp->Print("ERROR: Tool_Sample_Storage():Add_Sample(): index %d out of array, size %d\n", n, max_samples);
			return;
		}
	}

	//add sample
	samples[n] = value;
	n++;

	//calculate mean and sum
	if (calculate_sum){

		sum += value;
		if (calculate_mean)
			mean = (double)sum / n;

	}
	else if (calculate_mean){

		mean += (((double)value - mean) / n);

	}

}

/**
Calculates sum, average, deviation, confidence and median
Return average
*/
double Tool_Sample_Storage::Calc_All()
{
	Calc_Sum();
	Calc_AllExceptSum();
	return mean;
}

/**
Calculates sum, average, deviation, confidence and median
Return average
*/
double Tool_Sample_Storage::Calc_AllExceptSum()
{
	Calc_MeanDev();
	Calc_Confidence();
	Calc_Median();
	return mean;
}

/**
Calculates average and deviation
WARNING: sum must have already been calculated
Return average
*/
double Tool_Sample_Storage::Calc_MeanDev()
{
	Calc_Mean();
	Calc_Dev();
	return mean;
}

/**
Calculates and returns sum
*/
double Tool_Sample_Storage::Calc_Sum()
{
	sum = 0.0;
	for (int i = 0; i < n; i++)
		sum += samples[i];
	return sum;
}

/**
Calculates and returns average
WARNING: sum must have already been calculated
*/
double Tool_Sample_Storage::Calc_Mean()
{
	mean = (double)sum / n;
	return mean;
}

/**
Calculates and returns standard deviation
WARNING: mean must have already been calculated
*/
double Tool_Sample_Storage::Calc_Dev()
{
	double tmpSum = 0.0;
	for (int i = 0; i < n; i++)
		tmpSum += ((samples[i] - mean)*(samples[i] - mean));
	dev = sqrt(tmpSum / n);
	return dev;
}

/**
Calculates and returns the average on a given interval of samples
WARNING: index_end >= index_start
*/
double Tool_Sample_Storage::Calc_Mean_On_Interval(int index_start, int index_end)
{
	double tmp = 0.0;
	for (int i = index_start; i < index_end; i++)
		tmp += samples[i];
	return (tmp / (double)(index_end - index_start));
}

/**
Calculates the average and deviation on a given interval of samples
WARNING: index_end >= index_start
The values are returned through pointer parameters
*/
double Tool_Sample_Storage::Calc_MeanDev_On_Interval(int index_start, int index_end, double* output_mean, double* output_dev)
{
	double tmpMean = Calc_Mean_On_Interval(index_start, index_end);
	double tmpSum = 0.0;
	for (int i = index_start; i < index_end; i++)
		tmpSum += ((samples[i] - tmpMean)*(samples[i] - tmpMean));
	(*output_dev) = sqrt(tmpSum / (index_end - index_start));
	(*output_mean) = tmpMean;
	return tmpMean;
}

/**
Calculates and returns confidence interval from average value
WARNING: std. deviation must have already been calculated
*/
double Tool_Sample_Storage::Calc_Confidence(double t_constant)
{
	Calc_Dev();
	conf = t_constant * (dev / (sqrt(n)));
	return conf;
}

double Tool_Sample_Storage::Calc_Median(const bool allow_modify_array, const bool if_even_number_select_below_middle)
{
	//get median value, if number of elements is even then the first value below middle is returned 
	if (!allow_modify_array){
		median = torben<double>(samples, n);
	}
	else{
		median = quick_select<double>(samples, n);
	}

	//if number of elements is even the find 
	//CURRENTLY SLOW IMPLEMENTATION, FIND BETTER OR USE ONLY median below middle value for even numbers
	if (!SAMPLE_STORAGE_CALC_MEDIAN_BELOW_MIDDLE){
		if (n % 2 == 0){
			int countLarger = 0;
			double minDiff = DBL_MAX;
			double nextMedianValue = median;
			for (int i = 0; i < n; i++){
				if (samples[i] > median){
					if (samples[i] - median < minDiff){
						minDiff = samples[i] - median;
						nextMedianValue = samples[i];
					}
					countLarger++;
				}
			}
			//calculate average of the two values
			if (countLarger >= n / 2)
				median = (median + nextMedianValue) / 2.0;
		}
	}

	return median;
}