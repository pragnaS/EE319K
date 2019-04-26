// IO.c
// This software configures the switch and LED
// You are allowed to use any switch and any LED, 
// although the Lab suggests the SW1 switch PF4 and Red LED PF1
// Runs on LM4F120 or TM4C123
// Program written by: Anissa Chan and Pragna Subrahmanya
// Date Created: March 30, 2018
// Last Modified:  change this or look silly
// Lab number: 7


#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>

//------------IO_Init------------
// Initialize GPIO Port for a switch and an LED
// Input: none
// Output: none
void IO_Init(void) {
 // --UUU-- Code to initialize PF4 and PF2
  SYSCTL_RCGCGPIO_R |=0x20;
  volatile int delay;
  delay++;
  delay++;
  GPIO_PORTF_DIR_R |=0x04; //PF2 outputs with the LED 
  GPIO_PORTF_DIR_R &=0xEF; //PF4 is input for switch
  GPIO_PORTF_PUR_R |= 0x10;
  GPIO_PORTF_DEN_R |=0x14;
}


//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void) {
 // --UUU-- PF2 is heartbeat
  GPIO_PORTF_DATA_R ^=0x04;
}


//------------IO_Touch------------
// wait for release and press of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void) {
 // --UUU-- wait for release; delay for 20ms; and then wait for press

int count=20000;
        int delay=20;
        int release=1;
        int press=0;

        while(release>0)
        {
                release =(GPIO_PORTF_DATA_R>>4)& 0x01;
        }
        
        while(delay>0)                        //delaying for 20ms
        {
                while(count>0)
                {
                        count--;
                }
                delay--;
        }  
        
        while(press==0)
        {
                press = (GPIO_PORTF_DATA_R >>4)& 0x01;
        }
        
}
