		.data
a		.word 5
b		.word 3
		.text
		push &a
		push &b
		call #Addition
		pop R4 ; retrieve the return from subroutine (a + b)
		push &a
		push &b
		call #Subtract
		pop R4 ; (a - b)
		push &a
		push &b
		call #Multiply
		pop R4 ; (a * b)
Add     pop R10 ; return address
		pop R13 ; b
		pop R14 ; a
		add R13, R14
		push R14 ; push the result (return value) of the subroutine to the stack
		push R10 ; push the return address for ret instruction to use
		ret
Subtract pop R10 ; return address 
		pop R13 ; b
		pop R14 ; a
		sub R13, R14
		push R14
		push R10
		ret
Multiply pop R9 ; return address 
		pop R4 ; b
		pop R5 ; a
		mov #0d, R6 ; R6 holds the result
mul_additionLoop cmp #0d, R5 ; multiplication as an addition loop
		jeq mul_return
		push R4
		push R6
		call #Add
		pop R6
		dec R5
		jmp mul_additionLoop
mul_return push R6 ; push the result
		push R9
		ret
Divide  pop R9 ; return address
		pop R4 ; b
		pop R5 ; a
		mov #0d, R6 ; R6 holds the result
div_subtractionLoop cmp R4, R5
		jn div_return
		inc R6
		push R5
		push R4
		call #Subtract
		pop R5
		jmp div_subtractionLoop
div_return push R6
		push R9
		ret