			.data
; part 1 variables
p			.word 11
q			.word 13
seed		.word 5
; part 2 variables
x			.word 0
w			.word 0
;;;;;;;;;;;;;;;;;;;;
; part 1
BBS			push &p
			push &q
			call #Multiply
			pop R10
			push &seed
			push &seed
			call #Multiply
			push R10
			call #Modulus
			pop R11
			mov R11, &seed
			cmp &P2IFG, #0d
			jeq normal_ret
			jmp int_ret
normal_ret	ret
int_ret		reti
; part 2
MSWS		push &x
			push &x
			call #Multiply
			pop &x
			add &seed, &w
			add &w, &x
			mov &x, R11
			mov &x, R12
			mov #4d, R10
left_shift	cmp R10, #0d
			jeq loop_end1
			rlc	R11
			dec R10
			jmp left_shift
loop_end1	mov #4d, R10
right_shift	cmp R10, #0d
			jeq loop_end2
			rrc R12
			dec R10
			jmp right_shift
loop_end2	bis	R11, R12  ;R12 holds the generated random value
			reti
; part 3
GENERATE128 mov #128d, R10
			mov #1d, &p
			mov #7d, &q
generation	;;; TODO
; utility subroutines
Multiply 	pop R9 ; return address 
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
mul_return 	push R6 ; push the result
			push R9
			ret
			
Modulus		mov @SP(6),R10
			mov @SP(4), R11
			mov R11,R12
			mov R10,R13
			mov R10,R15
			rra R15
L1			cmp R15,R12
			jl L2
			jeq L2
			rla R12
			jmp L1
L2			cmp R13,R11
			jeq return
			jl return
			cmp R12,R13
			jge ST1
			jmp ST2
ST1			sub R12,R13
ST2			rra R12
			jmp L2
return		mov @SP(0), SP(6)
			add #6d, SP
			ret