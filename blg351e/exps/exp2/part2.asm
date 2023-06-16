			bis.b	#00h,&P1DIR
			bis.b	#ffh,&P2DIR
			bis.b	#00000100b,&P2OUT
			mov.w	#1d,R14  ; R14 stores whether the button is locked (pressable or unpressable)
			mov.w	#00h,R15
Check		bit.b	#00100000b,&P1IN
			jnz		Pressed
			mov.w	#1d,R14  ; unlock the button to be pressable if it is not pressed
			jmp		Check
Pressed		bis.b	#00h,R14  ; to get the z flag for R14
			jz		Check  ; don't continue further if the button is locked
			mov.w	#0d,R14  ; lock the button to be unpressable (to avoid switching when it is hold)
			xor.w	#01h,R15
			jnz		TurnOn3
			jz		TurnOn2
TurnOn2		mov.b	#00000100b,&P2OUT
			jmp		Check
TurnOn3		mov.b	#00001000b,&P2OUT
			jmp		Check