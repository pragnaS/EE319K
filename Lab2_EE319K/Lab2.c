// ****************** Lab2.c ***************
// Program written by: put your names here
// Date Created: 1/18/2017 
// Last Modified: 1/18/2019 
// Brief description of the Lab: 

// An embedded system is capturing temperature data from a
// sensor and performing analysis on the captured data.
// The controller part of the system is periodically capturing size
// readings of the temperature sensor. Your task is to write three
// analysis routines to help the controller perform its function
//   The three analysis subroutines are:
//    1. Calculate the mean of the temperature readings 
//       rounded down to the nearest integer
//    2. Convert from Farenheit to Centigrate using integer math 
//    3. Check if the captured readings are a non-decreasing monotonic series
//       This simply means that the readings are sorted in non-decreasing order.
//       We do not say "increasing" because it is possible for consecutive values
//       to be the same, hence the term "non-decreasing". The controller performs 
//       some remedial operation and the desired effect of the operation is to 
//       raise the the temperature of the sensed system. This routine helps 
//       verify whether this has indeed happened
#include <stdint.h>
#define True 1
#define False 0

// Return the computed Mean
// Inputs: Readings is an array of 16-bit temperature measurements
//         N is the number of elements in the array
// Output: Average of the data
// Notes: you do not need to implement rounding
int16_t Find_Mean(int16_t const Readings[], int32_t const N){
	
	int16_t i = 0;
	int16_t sum = 0 ;
	int16_t avg = 0;
	
	for( i=0; i<N; i++)
	{
		sum = sum + Readings[i];		//calculating sum of all readings
	}
	
	avg = sum/N;									//calculating average
	
	return avg;
	
// Replace this following line with your solution
  
}

// Convert temperature in Farenheit to temperature in Centigrade
// Inputs: temperature in Farenheit 
// Output: temperature in Centigrade
// Notes: you do not need to implement rounding
int16_t FtoC(int16_t const TinF){
// Replace this following line with your solution
	
	int16_t TinC =0;
	
	TinC= TinF - 32;							//converting to centigrade temperatures 
	
	TinC *=5;
	TinC /=9;
	
	return TinC;

}

// Return True of False based on whether the readings
// are an increasing monotonic series
// Inputs: Readings is an array of 16-bit temperature measurements
//         N is the number of elements in the array
// Output: true if monotonic increasing, false if nonmonotonic
int IsMonotonic(int16_t const Readings[],int32_t const N){
// Replace this following line with your solution
  
	int16_t i = 0;
	int16_t increasing = 1;
	
	for(i=0; i<N-1; i++)
		{
			if(Readings[i]>Readings[i+1])			//checking if current value is greater than the next value
			{
				increasing=0;										//if above condition is true, then series is not increasing 
			}
	  }
	
	return increasing;										//return state of increasing 
	}




