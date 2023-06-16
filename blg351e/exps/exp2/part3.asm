			bis.b	#ffh,&P1DIR
			bis.b	#00h,&P2DIR
			mov.w	#00h,&0200h  ; &0200h is the address of the count value in RAM
			mov.w	#1d,R14  ; R14 stores whether the button is locked (pressable or unpressable)
Check		bit.b	#00000010b,&P2IN
			jnz		Pressed
			mov.w	#1d,R14  ; unlock the button to be pressable if it is not pressed
			jmp		Check
Pressed		bis.b	#00h,R14  ; to get the z flag for R14
			jz		Check  ; don't continue further if the button is locked
			mov.w	#0d,R14  ; lock the button to be unpressable (to avoid switching when it is hold)
			inc		&0200h
			mov.w	&0200h,&P1OUT
			mov.w	&0200h,R15
			xor.b	#10h,R15  ; checks if the count is 16
			jz		Reset
			jmp		Check
Reset		mov.w	#00h,&0200h
			jmp 	Check