;****************** main.s ***************
; Program written by: ***Your Names**update this***
; Date Created: 2/4/2017
; Last Modified: 1/18/2019
; Brief description of the program
;   The LED toggles at 2 Hz and a varying duty-cycle
; Hardware connections (External: One button and one LED)
;  PE2 is Button input  (1 means pressed, 0 means not pressed)
;  PE3 is LED output (1 activates external LED on protoboard)
;  PF4 is builtin button SW1 on Launchpad (Internal) 
;        Negative Logic (0 means pressed, 1 means not pressed)
; Overall functionality of this system is to operate like this
;   1) Make PE3 an output and make PE2 and PF4 inputs.
;   2) The system starts with the the LED toggling at 2Hz,
;      which is 2 times per second with a duty-cycle of 30%.
;      Therefore, the LED is ON for 150ms and off for 350 ms.
;   3) When the button (PE1) is pressed-and-released increase
;      the duty cycle by 20% (modulo 100%). Therefore for each
;      press-and-release the duty cycle changes from 30% to 70% to 70%
;      to 90% to 10% to 30% so on
;   4) Implement a "breathing LED" when SW1 (PF4) on the Launchpad is pressed:
;      a) Be creative and play around with what "breathing" means.
;         An example of "breathing" is most computers power LED in sleep mode
;         (e.g., https://www.youtube.com/watch?v=ZT6siXyIjvQ).
;      b) When (PF4) is released while in breathing mode, resume blinking at 2Hz.
;         The duty cycle can either match the most recent duty-
;         cycle or reset to 30%.
;      TIP: debugging the breathing LED algorithm using the real board.
; PortE device registers
GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_AFSEL_R EQU 0x40024420
GPIO_PORTE_DEN_R   EQU 0x4002451C
; PortF device registers
GPIO_PORTF_DATA_R  EQU 0x400253FC
GPIO_PORTF_DIR_R   EQU 0x40025400
GPIO_PORTF_AFSEL_R EQU 0x40025420
GPIO_PORTF_PUR_R   EQU 0x40025510
GPIO_PORTF_DEN_R   EQU 0x4002551C
GPIO_PORTF_LOCK_R  EQU 0x40025520
GPIO_PORTF_CR_R    EQU 0x40025524
GPIO_LOCK_KEY      EQU 0x4C4F434B  ; Unlocks the GPIO_CR register
SYSCTL_RCGCGPIO_R  EQU 0x400FE608

       IMPORT  TExaS_Init
       THUMB
       AREA    DATA, ALIGN=2
;global variables go here


       AREA    |.text|, CODE, READONLY, ALIGN=2
		   
DelayArrayOn     DCD 0x2DC6C0, 0x4C4B40, 0x6ACFC0, 0x895440, 0xF4240
DelayArrayOff    DCD 0x6ACFC0, 0x4C4B40, 0x2DC6C0, 0xF4240, 0x895440

DelayBreatheOn	 DCD 0x2710, 0x4E20, 0x7530, 0x9C40, 0xEA60, 0x11170, 0x13880, 0x15F90, 0xC350, 0x186A0, 0x1ADB0, 0x1D4C0, 0x1FBD0, 0x222E0, 0x249F0, 0x27100, 0x29810, 0x2BF20, 0x2E630
DelayBreatheOff  DCD 0x2E630, 0x2BF20, 0x29810, 0x27100, 0x249F0, 0x222E0, 0x1FBD0, 0x1D4C0, 0x1ADB0, 0x186A0, 0x15F90, 0x13880, 0x11170, 0xEA60, 0xC350, 0x9C40, 0x7530, 0x4E20, 0x2710

       THUMB
       EXPORT  Start


Start
 ; TExaS_Init sets bus clock at 80 MHz
	  BL  TExaS_Init ; voltmeter, scope on PD3
 ; Initialization goes here
 
	 
	   LDR R1, =SYSCTL_RCGCGPIO_R
	   LDR R0, [R1]		;turn clock E and F on
	   ORR R0, #0x30
	   STR R0, [R1]
	
	   NOP	;waiting for clock to stabilize
	   NOP
	   NOP
	   NOP
	   
	   LDR R1, =GPIO_PORTE_DIR_R
	   LDR R0, [R1] 
	   AND R0, #0xF3	;preserve PE4 and PE5 bits
	   ORR R0, #0x08	;configuring PE3 as output and PE2 as input
	   STR R0, [R1]
	  
	   LDR R1, =GPIO_PORTE_DEN_R
	   LDRB R0, [R1]
	   ORR R0, #0x0C	;enabling PE3 and PE2
	   STRB R0, [R1]
	   
	   LDR R1, =GPIO_PORTF_LOCK_R
	   LDR R0, =GPIO_LOCK_KEY
	   STR R0, [R1]
	   
	   LDR R1, =GPIO_PORTF_CR_R
	   MOV R0, #0xFF
	   STR R0, [R1]

	   LDR R1, =GPIO_PORTF_DIR_R
	   ;LDRB R0, [R1]
	   AND R0, #0xFE
	   STRB R0, [R1]
	   
	   LDR R1, =GPIO_PORTF_PUR_R 	
	   ORR R0, #0x01
	   STR R0, [R1]
	   
	   LDR R1, =GPIO_PORTF_DEN_R
	   ;LDRB R0, [R1]
	   ORR R0, #0x01
	   STRB R0, [R1]
	   
	  
	   AND R2, #0  ;initializing R2 as previous state of switch (R2=0)
	   AND R3, #0  ;initializing R3 as index for array of duty-cycles
	   AND R4, #0	;no. of count cycles passed to delay subroutine
	   AND R5, #0
	   MOV R7, #1	;previous state of PF4 switch
	   ADD R8, #-4	;index for breathing delays
	   AND R6, #0  	;delay time for LED off
	  
	   
       CPSIE  I    ; TExaS voltmeter, scope runs on interrupts
loop  
; main engine goes here

;check state of switch
;choose duty cycle (delay)
;output LED with chosed duty cycle

	BL LEDon
	BL LEDonTime
	BL Delay
	BL LEDoff
	BL LEDoffTime
	BL Delay
	
	BL checkSwitch
	BL checkBreathing
	B loop
	
	  
LEDon  LDR R1, =GPIO_PORTE_DATA_R		;loading Port E
	   LDR R0, [R1]
	   EOR R0, #0x08		;turning LED on
	   STR R0, [R1]
	   BX LR
	   
LEDonTime	   LDR R1, =DelayArrayOn
	   LDR R5, [R1, R3]	;obtaining the count for the respective duty cycle to keep LED on
	   MOV R4, R5	   ;storing the count in R4 (to later be used in delay subroutine)
	   BX LR

LEDoff LDR R1, =GPIO_PORTE_DATA_R
	   LDR R0, [R1]
	   EOR R0, #0x08				;turning LED off
	   STR R0, [R1]
	   BX LR
	   
LEDoffTime		   LDR R1, =DelayArrayOff
	   LDR R6, [R1, R3]	;obtaining the count for the respecive duty cycle to keep LED off
	   MOV R4, R6			;storing the count in R4 (to later be used in delay subroutine)
	   BX LR
	   
	   
checkSwitch LDR R1, =GPIO_PORTE_DATA_R			;detecting the rising edge of the switch (change from 0 to 1)
	   LDR R0, [R1]
	   LSR R0, #2
	   CMP R2, #0   ;if (R2==0)					;if previous state of switch is 0  (if switch was not pressed)
	   BNE skiptoggle	;if not, do not change duty cycle	
	   CMP R0, #1 	;if(R0==1)					;if current state of switch is 1 ((if switch is now pressed)
	   BNE skiptoggle	;if not, do not change duty cycle	
	   MOV R2, R0		;storing current state of switch as previous state for next iteration
	   
	   
toggleDutyCycle ADD R3, R3, #4		;incrementing index of array 
			    CMP R3, #16				;if index reaches its limit, reset to zero 
				BEQ reset		
				BX LR 

reset AND R3, #0
	  BX LR
	  
skiptoggle  MOV R2, R0	 ;Save current state to be used as previous state for next iteration
			BX LR
			
	  
	  
Delay
;implements a delay
dloop  SUBS R4, #1
	   BNE dloop
	   BX LR

checkBreathing
	   LDR R1, =GPIO_PORTF_DATA_R
	   LDR R0, [R1]
	   ;AND R0, #1
	   LSR R0, #4
	   CMP R0, #0		;if (R0==0) ((if switch is pressed now)
	   BNE skipBreathe
	   ;CMP R7, #1		;if(R5==1)  (if switch was not pressed previously)
	   ;BNE skipBreathe 
	   ;MOV R7, R0
	   
breathe
	   LDR R9, =DelayBreatheOn
	   LDR R10, =DelayBreatheOff
	   ADD R11, #20	
	   
breatheonLoop	   ADD R8, R8, #4   ;increment the pointer


dutycycleiterateON   LDR R4, [R9, R8]	;load delay into R4
				   BL LEDon
				   BL Delay
				   LDR R4, [R10, R8]
				   BL LEDoff
				   BL Delay
				   
				   ADD R11, #-1
				   CMP R11, #0
				   BNE dutycycleiterateON
				   
				   MOV R11, #20
				   
				   CMP R8, #40
				   BNE breatheonLoop
				   
				 ADD R11, #20		;reset iteration count
				 ADD R8, R8, #4
				  
breatheoffLoop	  ADD R8, R8, #-4	;decrement pointer (move from higher duty cycle to lower duty cycle)
				  
dutycycleiterateOFF				  LDR R4, [R9, R8]	;load delay into R4
				  BL LEDon
				  BL Delay
				  LDR R4, [R10, R8]	;load delay into R4
				  BL LEDoff
				  BL Delay
				  
				  ADD R11, #-1
				  CMP R11, #0
				  BNE dutycycleiterateOFF
				  
				  MOV R11, #20
				  CMP R8, #0
				  BNE breatheoffLoop
				  
				  B loop
				   
	   
skipBreathe  BX LR
	   
	   
	   

    	
      ALIGN      ; make sure the end of this section is aligned
      END        ; end of file
