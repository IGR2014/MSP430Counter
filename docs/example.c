#include "msp430.h"		

NAME main
PUBLIC main

ORG 0FFE8h
DW PORT1_isr

ORG 0FFFEh
DC16 init

RSEG CSTACK
RSEG CODE





init:   MOV     #SFE(CSTACK), SP

main:   NOP
        mov.w   #WDTPW+WDTHOLD, &WDTCTL
        
        BIS.W   #GIE, SR
        
        MOV.B   #2, P1IE
        MOV.B   #2, P1IES
        BIC.B   #2, P1IFG
        
        MOV.B   #0, P2OUT
        MOV.B   #255, P2DIR
        
        mov.w   #0, R5  ;licznik
        mov.w   #0, R6

loop:
        jmp $
        

PORT1_isr:
        BIT.B   #4, P1IN
        jnz decrement
        jmp increment
return:
        BIC.B   #2, P1IFG
        RETI
        
increment:
        cmp     #153, R5
        jz      return
        dadd     #1, R5
        mov.b   R5, P2OUT
        jmp return
            
decrement:
        cmp     #0, R5
        jz      return
        DEC     R5
        mov.w   R5, R6
        bic.b   #0F0h, R6
        cmp   #0Fh, R6
        jz     decrement_decimal
return2:
        mov.b   R5, P2OUT
        jmp return
        
decrement_decimal:
        bic.b     #6, R5
        jmp return2
        
  

        


wait:
        mov.w #0FFFFh, R15
wait_loop:
        dec.w R15
        jnz wait_loop
        jmp return


        
        END
