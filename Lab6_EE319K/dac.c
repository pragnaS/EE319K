// dac.c
// This software configures DAC output
// Lab 6 requires a minimum of 4 bits for the DAC, but you could have 5 or 6 bits
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	volatile int delay;
	
	SYSCTL_RCGC2_R |= 0x02;		//turning on clock B
	delay =SYSCTL_RCGC2_R; 
	GPIO_PORTB_DIR_R |= 0x0F; //setting PB0-3 as outputs
	GPIO_PORTB_AFSEL_R &= ~0x0F;  //disabling the alt function on PB0-3
	GPIO_PORTB_DEN_R |= 0x0F; //enabing PB0-3 
	
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data){
	
	GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x0F) | (data & 0xF);
	
}

void Heartbeat_Init()
{
	volatile int delay;
	SYSCTL_RCGC2_R |= 0x30; 	//turning on clock F
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_DEN_R |= 0x04;
	
}

