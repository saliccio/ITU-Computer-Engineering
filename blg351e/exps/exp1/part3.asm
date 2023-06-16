SetupP1 	bis.b #0ffh,&P1DIR ; P1.0-3 set output
SetupP2		bis.b #0ffh,&P2DIR ; P2.0-3 set output
Loop1		mov.b #010h,&P1OUT ; P1.0 set 1
			mov.b #008h,&P2OUT ; P1.0 set 1
			mov.w #010h,R14
			mov.w #008h,R13
			jmp Wait1
Mainloop1 	rla R14 ; Rotate P1 to left
			rra R13
			add R14,&P1OUT
			add R13,&P2OUT
Wait1 		mov.w #0500000,R15 ; Delay to R15
L1 			dec.w R15 ; Decrement R15
			jnz L1 ; Delay over?
			cmp.b #0f0h,&P1OUT; Check termination of loop
			jeq Loop2; Return first iteration
			jmp Mainloop1 ; Again
Loop2		mov.b #010h,&P2OUT
			mov.b #008h,&P1OUT
			mov.w #010h,R12
			mov.w #008h,R11
			jmp Wait2
Mainloop2 	rla R12
 ; Rotate P1 to left
			rra R11
			add R12,&P2OUT
			add R11,&P1OUT
Wait2 		mov.w #0500000,R15 ; Delay to R15
L2 			dec.w R15 ; Decrement R15
			jnz L2 ; Delay over?
			cmp.b #0f0h,&P2OUT; Check termination of loop
			jeq Loop1; Return first iteration
			jmp Mainloop2 ; Again