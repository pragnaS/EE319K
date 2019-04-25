****************** main.s ***************
; Program initially written by: Yerraballi and Valvano
; Author: Pragna Subrahmanya
; Date Created: 1/15/2018 
; Last Modified: 1/18/2019 
; Brief description of the program: Spring 2019 Lab1
; The objective of this system is to implement odd-bit counting system
; Hardware connections: 
;  Output is positive logic, 1 turns on the LED, 0 turns off the LED
;  Inputs are negative logic, meaning switch not pressed is 1, pressed is 0
;    PE0 is an input 
;    PE1 is an input 
;    PE2 is an input 
;    PE3 is the output
; Overall goal: 
;   Make the output 1 if there is an odd number of 1's at the inputs, 
;     otherwise make the output 0
; The specific operation of this system 
;   Initialize Port E to make PE0,PE1,PE2 inputs and PE3 an output
;   Over and over, read the inputs, calculate the result and set the output

; NOTE: Do not use any conditional branches in your solution. 
;       We want you to think of the solution in terms of logical and shift operations

GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_DEN_R   EQU 0x4002451C
SYSCTL_RCGCGPIO_R  EQU 0x400FE608

      THUMB
      AREA    DATA, ALIGN=2
;global variables go here
      ALIGN
      AREA    |.text|, CODE, READONLY, ALIGN=2
      EXPORT  Start
Start
	  LDR R1, =SYSCTL_RCGCGPIO_R
	  LDRB R0, [R1]		;turn clock E on
	  ORR R0, #0x10
	  STRB R0, [R1]
	
	  NOP	;waiting for clock to stabilize
	  NOP
	
	  LDR R1, =GPIO_PORTE_DIR_R
	  LDRB R0, [R1] 
	  AND R0, #0xF8	;preserve PE4 and PE5 bits
	  ORR R0, #0x08	;configuring PE3 as output, and PE0, PE1, PE2 as input
	 	
	  STRB R0, [R1]
	
	  LDR R1, =GPIO_PORTE_DEN_R
	  LDRB R0, [R1]
	  ORR R0, #0x0F
	  STRB R0, [R1]
	
	
	
	
; code to execute once at start goes here
loop

	  LDR R0, =GPIO_PORTE_DATA_R
	  LDRB R1, [R0]
	
	  AND R2, #0 ;clearing register R2
	  AND R3, #0 ;clearing register R3
	  AND R4, #0 ;clearing register R4
	
	  AND R2, R1, #0x04	;isolating PE2 input
	  AND R3, R1, #0x02	;isolating PE1 input
	  AND R4, R1, #0x01	;isolating PE0 input 
	
	  LSR R2, #2	;shift bits to least significant pos
	  LSR R3, #1	;shift bits to least significant pos
	
	  EOR R3, R2	;checking if no. of 1's is odd or even; if it's even, output will be 0; if it's odd, output will be 1
	  EOR R1, R4, R3
	 
	  LSL R1, #3 	;shift bit to output pin
	
	  STRB R1, [R0]
	
	

; code that runs over and over goes here
      B    loop

      ALIGN        ; make sure the end of this section is aligned
      END          ; end of file
          