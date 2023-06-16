bis.b	#ffh,&P1DIR
			bis.b	#00h,&P2DIR
Check		bit.b	#00010000b,&P2IN
			jnz		Pressed
			jmp		Check	
Pressed		bis.b	#00010000b,&P1OUT
Loop		jmp		Loop