			.data
A			.word 0
B			.word 29
C			.word 0
D			.word 0
num			.word 150,190,002
hash		.space 58
			.text
			mov num,R14
			mov	hash,R12
			mov #3d,R13
Loop		mov @R14+,&A
			mov &B,&C
			mov &A,&D
			mov A,R15
			rra R15
L1			cmp R15,&C
			jl L2
			jeq L2
			rla &C
			jmp L1
L2			cmp &D,&B
			jeq res
			jl res
			cmp &C,&D
			jge ST1
			jmp ST2
ST1			sub &C,&D
ST2			rra &C
			jmp L2
res			rla &D
			add &D,R12
check		cmp #0d,0(R12)
			jeq map
			incd R12
			jmp check
map			mov &A,0(R12)
			mov hash,R12
			dec R13
			jnz	Loop