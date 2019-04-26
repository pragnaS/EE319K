; SysTick.s
; Module written by: **-UUU-*Anissa Chan and Pragna Subrahmanya***
; Date Created: 2/14/2017
; Last Modified: 8/29/2018 
; Brief Description: Initializes SysTick

NVIC_ST_CTRL_R        EQU 0xE000E010
NVIC_ST_RELOAD_R      EQU 0xE000E014
NVIC_ST_CURRENT_R     EQU 0xE000E018

        AREA    |.text|, CODE, READONLY, ALIGN=2
        THUMB
; -UUU- You add code here to export your routine(s) from SysTick.s to main.s
        EXPORT SysTick_Init
;------------SysTick_Init------------
; ;-UUU-Complete this subroutine
; Initialize SysTick running at bus clock.
; Make it so NVIC_ST_CURRENT_R can be used as a 24-bit time
; Input: none
; Output: none
; Modifies: ??
SysTick_Init
 ; **-UUU-**Implement this function****
 LDR R0, = NVIC_ST_CTRL_R	;disabling Systick for set up
 LDR R1, [R0]
 AND R1, #0x00
 STR R1, [R0]
 
 LDR R0, = NVIC_ST_RELOAD_R	;setting the reload to max reload to allow for the counter to simply be an indicator what count it is on
 LDR R1, [R0]
 AND R1, #0x00FFFFFF
 STR R1, [R0]
 
 LDR R0, = NVIC_ST_CURRENT_R	;this states that if you were to write to this then the value of current will clear and the count flag will clear to zero
 LDR R1, [R0]
 AND R1, #0x00
 STR R1, [R0]
 
 LDR R0, = NVIC_ST_CTRL_R	;enables the systick clock to the core clock so it will decrement correctly
 LDR R1, [R0]
 ORR R1, #0x00000005
 STR R1, [R0]
 BX  LR                          ; return


    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
