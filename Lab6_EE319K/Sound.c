// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none

//make your wave array
uint32_t sineWave[] = {8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7}; //32 numbers
int wave_index;
	
void Sound_Init(void){
	
	DAC_Init();				//setting PortB as DAC
	wave_index=0;
	
	NVIC_ST_CTRL_R=0; //disable systick for set up
  NVIC_ST_RELOAD_R=0xFFFFFF; //unsure about this value
  NVIC_ST_CURRENT_R=0; //any write to current clears it
  NVIC_SYS_PRI3_R= NVIC_SYS_PRI3_R&0x00FFFFFF; //priority zero
  NVIC_ST_CTRL_R =0x07; //enables core clock with interrupts
	
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){ 	//interrupts systic at rate specified by period
	
	if(period)
	{
		NVIC_ST_RELOAD_R = period-1; 
		//NVIC_ST_CURRENT_R=0;
		NVIC_ST_CTRL_R |=0x02;
	}
	else
	{
	NVIC_ST_CTRL_R= NVIC_ST_CTRL_R & ~0x02;
	DAC_Out(0);
	}
}

void SysTick_Handler(void)
{
	GPIO_PORTF_DATA_R &= 0x04; 		//toggling LED for heartbeat
  DAC_Out(sineWave[wave_index]);
	wave_index++;
	wave_index = wave_index%0x1F; //masking index (5 bits to account for 32 elements)
}

