SetupP1 	bis.b #00fh,&P1DIR ; P1.0-3 set output
SetupP2		bis.b #00fh,&P2DIR ; P2.0-3 set output
Initialize	mov.b #001h,&P1OUT ; P1.0 set 1
			mov.b #001h,&P2OUT ; P2.0 set 1
			jmp Wait
Mainloop 	rla.b &P1OUT ; Rotate P1 to left
			rla.b &P2OUT ; Rotate P2 to left
			jmp Wait
Wait 		mov.w #050000,R15 ; Delay to R15
L1 			dec.w R15 ; Decrement R15
			jnz L1 ; Delay over?
			cmp.b #008h,&P1OUT; Check termination of loop
			jeq Initialize; Return first iteration
			jmp Mainloop ; Again