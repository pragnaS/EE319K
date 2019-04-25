// Piano.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 3 keys, but you could have more
// Runs on LM4F120 or TM4C123
// Program written by: Anissa Chan, Pragna Subrahmanya
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// **************Piano_Init*********************
// Initialize piano key inputs, called once to initialize the digital ports
// Input: none 
// Output: none
void Piano_Init(void){ 

	volatile int delay;
    SYSCTL_RCGC2_R |= 0x10;    //turning on clock E
    delay=SYSCTL_RCGC2_R;         //stablising clock

    GPIO_PORTE_DIR_R &=~0x38;	 //setting PE3-5 as inputs
		GPIO_PORTE_AFSEL_R &= ~0x38;	//disabling alternate function on PE3-5
    GPIO_PORTE_DEN_R |= 0x38;   //enabling PE3-5
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
//   bit n is set if key n is pressed
uint32_t Piano_In(void){
  return ((GPIO_PORTE_DATA_R & 0x38)>>3); // Replace with your code			//mask switches
}
