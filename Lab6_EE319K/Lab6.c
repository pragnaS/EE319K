// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

//Period = 80000000/32/Freq = 2500000/Freq
uint32_t input;


int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
	Heartbeat_Init();
  Sound_Init();
	
// other initialization
 EnableInterrupts();
  while(1){ 
		
		
input = Piano_In();
                
	switch(input)
 {
    case 0: Sound_Play(0);
            break;
    case 1: Sound_Play(2389);   //note c
            break;                           
    case 2: Sound_Play(3792);  //note e
            break;                            
    case 4: Sound_Play(3189);   //note g
            break;
    default: Sound_Play(0);
  }
		
		
			
		}
  }



