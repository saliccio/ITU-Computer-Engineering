		.data
array_A	.word 15, 3, 7, 5
array_B	.word 2, -1, 7, 3
		.text
Main	push #4d
		push #array_A
		push #array_B
		push #0d
		call #Dot
		pop R15
Dot		cmp 2(SP), 8(SP) ; if i == n		Note that @SP = return address, 2(SP) = i, 4(SP) = b, 6(SP) = a, 8(SP) = n
		jeq dot_break
		mov 2(SP), R6
		mov 4(SP), R7
		mov 6(SP), R8
		push 8(SP)
		inc R8
		push R8
		inc R7
		push R7
		inc R6
		push R6
		call #Dot
		pop R15
		mov 4(SP), R9
		mov 6(SP), R10
		mov @R9, R11
		mov @R10, R12
		push R11
		push R12
		call #Multiply ; stack's top is (&A * &B)
		pop R12
		add R12, R15
		call #ClearStack
		push R15
		push &0270h
		ret
dot_break call #ClearStack
		push #0d
		push &0270h
		ret
Multiply pop R9 ; return address 
		pop R4 ; b
		pop R5 ; a
		mov #0d, R6 ; R6 holds the result
mul_additionLoop cmp #0d, R5 ; multiplication as an addition loop
		jeq mul_return
		add R4, R6
		dec R5
		jmp mul_additionLoop
mul_return push R6 ; push the result
		push R9
		ret
ClearStack pop &0272h
		pop &0270h ; this subroutine is intended to clear the arguments a, b, i, n and move the return address to a constant memory address temporarily
		add #8d, SP
		push &0272h
		ret