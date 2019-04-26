// Uart.c
// Runs on LM4F120/TM4C123
// Use UART1 to implement bidirectional data transfer to and from 
// another microcontroller in Lab 9.  This time, interrupts and FIFOs
// are used.
// Daniel Valvano
// November 14, 2018
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* Lab solution, Do not post
 http://users.ece.utexas.edu/~valvano/
*/

// This U0Rx PC4 (in) is connected to other LaunchPad PC5 (out)
// This U0Tx PC5 (out) is connected to other LaunchPad PC4 (in)
// This ground is connected to other LaunchPad ground

#include <stdint.h>
#include "Fifo.h"
#include "Uart.h"
#include "../inc/tm4c123gh6pm.h"

int RxCounter=0;

uint32_t DataLost; 
// Initialize UART1
// Baud rate is 115200 bits/sec
// Make sure to turn ON UART1 Receiver Interrupt (Interrupt 6 in NVIC)
// Write UART1_Handler
void Uart_Init(void){
   // --UUU-- complete with your code
	volatile int delay;
	//Fifo_Init();
	SYSCTL_RCGCUART_R |=0x0002; //activates UART0
	delay++;
	delay++;
	delay++;
	delay++;
	SYSCTL_RCGCGPIO_R |=0x0004; //activate port c
	delay++;
	delay++;
	delay++;
	delay++;
	UART1_CTL_R &=~0x0001;	//disables uart
	UART1_IBRD_R =43; //80MHz
	//IBRD=int(80000000/(16*115,200)) = int(43.1267)
	UART1_FBRD_R = 26;	//80MHZ
	//FRBD= round(.1267*64)=8;
	UART1_LCRH_R=0x0070; //enables FIFO
	UART1_CTL_R= 0x301; //TXE AND UART
	GPIO_PORTC_AFSEL_R |=0x30; //alt function for port 4 and 5
	GPIO_PORTC_PCTL_R =(GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00220000;
	GPIO_PORTC_DEN_R |= 0x30; //digital I/O on PC4,5
	GPIO_PORTC_AMSEL_R &=~0x30; //no analog on port 4 and 5
	GPIO_PORTC_DIR_R |= 0x20; //setting PC5 as output
	NVIC_EN0_R |=0x40; 	//turns on the 16th bit of the NVIC
	UART1_IFLS_R &=~0x38; 		//clears bit 3,4,5 of register
	UART1_IFLS_R |=0x10;		//sets 0x2 so that the interrupt will occur 
	UART1_IM_R |= 0x10;
	DataLost=0; 
}

// input ASCII character from UART
// spin if RxFifo is empty
// Receiver is interrupt driven
char Uart_InChar(void){
	//wait for new input, then return ASCII code
	while((UART1_FR_R & 0x0010) !=0); //wait until RXFE is 0
	uint8_t datapt = UART1_DR_R & 0xFF;
	return (datapt);  // --UUU-- remove this, replace with real code
}

//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until ETX is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
// THIS FUNCTION IS OPTIONAL
void UART1_InMessage(char *bufPt){
	
}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
// Transmitter is busywait
void Uart_OutChar(char data){
	//wait for buffer to be not full, then output
	while((UART1_FR_R & 0x0020) !=0); 
	//waiting for TXFF to be 0
	UART1_DR_R = data&0xFF;
	
  // --UUU-- complete with your code
	
}

// hardware RX FIFO goes from 7 to 8 or more items
// UART receiver Interrupt is triggered; This is the ISR
void UART1_Handler(void){
  // --UUU-- complete with your code
	
	GPIO_PORTF_DATA_R ^=0x04;
	GPIO_PORTF_DATA_R ^=0x04;
	
	while((UART1_FR_R & 0x10)==0){
		Fifo_Put(UART1_DR_R&0xFF);
	}
	RxCounter++; 
	
	UART1_ICR_R =0x10; //clears bit 4 (RXRIS) in the RIS register
	
	GPIO_PORTF_DATA_R ^=0x04;
}
