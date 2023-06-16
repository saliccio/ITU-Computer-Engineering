; Furkan Salik 150200056

SYST_CSR				EQU	0xE000E010	;SYST_CSR -> SysTick Control and Status Register
SYST_RVR				EQU	0xE000E014	;SYST_RVR -> SysTick Reload Value Register
SYST_CVR				EQU	0xE000E018	;SYST_CVR -> SysTick Current Value Register

SysTickReloadValue		EQU 11999999  ; Reload value is calculated using the formula: [Period=(1 + ReloadValue)/ClockFrequency], [1=(1+ReloadValue)/12*10^6], hence ReloadValue=11999999

			AREA dta, data, readwrite
			ALIGN					
PortB					EQU 0x20001000
bcd 		DCD 0x0000003F,0x00000006,0x0000005B,0x0000004F,0x00000066,0x0000006D,0x0000007D,0x00000007,0x0000007F,0x0000006F		;Allocate memory for given values contiguously
bcd_end

						AREA part1, code, readonly		; Start read-only code section named 'q1'
						ENTRY						; Entry point of the program
						THUMB						; Enable Thumb mode for next instructions
						ALIGN						; Align the section

__main 					PROC								
						EXPORT __main
						NOP
						ENDP
; SYSTICK INIT START
						LDR r1,=SYST_CSR	; r1=Address of SysTick Status Register
						MOVS r2, #0		; r2=0
						STR r2, [r1]	; Reset SysTick Status Register
						LDR r3,=SysTickReloadValue	; r3=Reload value for SysTick
						STR r3, [r1, #4]	; Load r3 into Reload Value Register
						MOVS r4, #0		; r4=0
						STR r4, [r1, #8]	; Load r4 into Current Value Register
						MOVS r5, #7		; r5=0
						LDR r6, [r1]	; r6=Value of Status Register
						ORRS r6, r6, r5		; r6=Status Register value with enable and tickint bits set
						STR r6, [r1]	; Store new Status Register value
; SYSTICK INIT END

SysTick_Handler			PROC
						EXPORT SysTick_Handler
						ADDS r1, #1
						CMP r1, #10
						BEQ	Clear
						BX LR
Clear					MOVS r1, #0
						LDR r4,=bcd
						LDR r5,=PortB
						LDR r3, [r4, r1]
						STR r3, [r5]
						BX LR
						ENDP
						END