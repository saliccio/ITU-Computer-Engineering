			.data
array		.byte 00111111b, 00000110b, 01011011b, 01001111b, 01100110b, 01101101b, 01111101b, 00000111b, 01111111b, 01101111b
lastElement
			.text
			
			mov.b #array,R10
			bis.b #07fh,&P1DIR
init		mov.b @R10+,&P1OUT
			mov.w #00Ah,R14 ;Delay to R14
L2 			mov.w #07A00h,R15
L1 			dec.w R15 ;Decrement R15
			jnz L1
			dec.w R14
			jnz L2
			cmp #lastElement,R10
			jeq zero
			jmp init
zero		mov #array,R10
			jmp init