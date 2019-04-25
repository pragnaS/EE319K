// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// January 18, 2019

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  PF1 PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE50      (*((volatile unsigned long *)0x400240FC))

#define Home 0
#define W2 1
#define W4 2
#define W8 3
#define W16 4
#define WW1 5
#define WW2 6
#define WW4 7
#define WW8 8
#define WW16 9
#define CW8 10
#define CW4 11
#define CW2 12
#define CW1 13
#define CWW16 14
#define CWW8 15
#define CWW4 16
#define CWW2 17
#define S2 18
#define S4 19
#define S8 20
#define S16 21
#define SS1 22
#define SS2 23
#define SS4 24
#define SS8 25
#define SS16 26
#define CS8 27
#define CS4 28
#define CS2 39
#define CSS1 30
#define CSS16 31
#define CSS8 32
#define CSS4 33
#define CSS2 34
volatile int i=4;        //stablizing the clock




void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE50;
}

struct State{
	uint8_t next[4];
	uint8_t output;
	uint16_t delay;
};

typedef struct State stype_t;


stype_t FSM[35] = {{{Home,W2,S2,Home}, 0x01, 5}, 
                  {{W4,W4,W4,Home}, 0x02, 5}, {{W8,W8,W8,Home},0x04,5},
                  {{W16,W16,W16,Home},0x08, 5}, {{WW1,WW1,WW1,Home}, 0x10, 5},
                  {{WW2,WW2,WW2,Home},0x01, 5}, {{WW4,WW4,WW4,Home},0x02, 5},
                  {{WW8,WW8,WW8,Home},0x04, 5}, {{WW16,WW16,WW16,Home},0x08, 5},
                  {{CW8,CW8,CW8,Home},0x10, 5}, {{CW4,CW4,CW4,Home},0x08, 5},
                  {{CW2,CW2,CW2,Home},0x04, 5}, {{CW1,CW1,CW1,Home},0x02, 5},
                {{CWW16,CWW16,CWW16,Home},0x01, 5},{{CWW8,CWW8,CWW8,Home}, 0x10, 5},
                  {{CWW4,CWW4,CWW4,Home},0x08, 5}, {{CWW2,CWW2,CWW2,Home},0x04,5},
                  {{Home,Home,Home,Home},0x02, 5}, {{S4,S4,S4,Home},0x22, 5},
                  {{S8,S8,S8,Home},0x04, 5}, {{S16,S16,S16,Home},0x28, 5},
                  {{SS1,SS1,SS1,Home},0x10, 5}, {{SS2,SS2,SS2,Home},0x21, 5},
                  {{SS4,SS4,SS4,Home},0x02, 5}, {{SS8,SS8,SS8,Home},0x24, 5},
                  {{SS16,SS16,SS16,Home},0x08, 5}, {{CS8,CS8,CS8,Home},0x30, 5},
                  {{CS4,CS4,CS4,Home},0x08, 5}, {{CS2,CS2,CS2,Home},0x24, 5},
              {{CSS1,CSS1,CSS1,Home},0x02, 5}, {{CSS16,CSS16,CSS16,Home},0x21, 5},
                  {{CSS8,CSS8,CSS8,Home},0x10, 5}, {{CSS4,CSS4,CSS4,Home},0x28, 5},
                  {{CSS2,CSS2,CSS2,Home},0x04, 5}, {{Home,Home,Home,Home},0x21, 5}};


int main(void){ 
	
	uint32_t CS=0;
  uint8_t input=0;
	
  TExaS_Init(&SendDataToLogicAnalyzer);    // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init();   
// you initialize your system here
	
  SYSCTL_RCGCGPIO_R |=0x11; //initializes the ports A,B,E,F
  i++;
  i++;
  GPIO_PORTA_DIR_R &=0xCF;        //establishing inputs and outputs
  GPIO_PORTE_DIR_R |=0x3F;
  GPIO_PORTA_DEN_R |=0x30;
  GPIO_PORTE_DEN_R |=0x3F;
  GPIO_PORTE_PDR_R |=0x20; //enables internal pull down + logic switch
  
	
  CS=Home;
  EnableInterrupts();   
  while(1){
		GPIO_PORTE_DATA_R=FSM[CS].output; //goes to the current state and takes the output
		SysTick_Wait10ms(FSM[CS].delay); //wait
		input=(GPIO_PORTA_DATA_R & 0x30)>>4; //getting the input and shifting it to the end
		CS=FSM[CS].next[input]; //next state becomes current state
		
// output
// wait
// input
// next		
  }
}


