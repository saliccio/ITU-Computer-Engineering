;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
			.data
array			.byte 00111111b, 00000110b, 01011011b, 01001111b, 01100110b, 01101101b, 01111101b, 00000111b, 01111111b, 01101111b
lastElement
			.text
	
			clr R5
			mov.b #array,R10
			bis.b #07fh,&P1DIR
	
init_INT 		bis.b #040h,&P2IE
			and.b #0BFh,&P2SEL
			and.b #0BFh,&P2SEL2
			bis.b #040h,&P2IES
			clr &P2IFG
			eint
			
init			mov.b @R10,&P1OUT
			incd R10
			mov.w #00Ah,R14 ;Delay to R14
L2 			mov.w #07A00h,R15
L1 			dec.w R15 ;Decrement R15
			jnz L1
			dec.w R14
			jnz L2
			cmp #lastElement,R10
			jge zero
			jmp init
zero			mov #array,R10
			cmp #1d,R5
			jeq odd
			jmp init
odd			inc R10
			jmp init
			
ISR 			dint
			xor #1d,R5
			clr &P2IFG
			eint
			reti
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            .sect ".int03"
			.short ISR