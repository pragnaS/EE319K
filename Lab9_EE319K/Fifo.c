// Fifo.c
// Runs on LM4F120/TM4C123
// Provide functions that implement the Software FiFo Buffer
// Last Modified: November 14, 2018
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#define FIFO_SIZE 7

// --UUU-- Declare state variables for Fifo
//        buffer, put and get indexes

	int32_t static PutI; //Index to put new
	int32_t static GetI; //Index of oldest 
	int32_t static Fifo[FIFO_SIZE]; 


// *********** Fifo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void Fifo_Init(){
// --UUU-- Complete this
	PutI=GetI=0;

}

// *********** Fifo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t Fifo_Put(char data){
// --UUU-- Complete this routine
	if( ((PutI+1)%FIFO_SIZE)== GetI){ 			//full FIFO check
		return(0);
	}
	Fifo[PutI] = data; 
	PutI = (PutI+1)%FIFO_SIZE; 	
  return(1); 
}

// *********** FiFo_Get**********
// Gets an element from the FIFO
// Input: Pointer to a character that will get the character read from the buffer
// Output: 1 for success and 0 for failure
//         failure is when the buffer is empty
uint32_t Fifo_Get(char *datapt){ 
//--UUU-- Complete this routine
	if(GetI==PutI){ 	//empty fifo check

		return(0);
	}
	*datapt = Fifo[GetI];
	GetI = (GetI+1)%FIFO_SIZE;

  return(1); 
}

