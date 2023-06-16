			.data
A			.word 151
B			.word 8
C			.word 0
D			.word 0
			.text
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
res			jmp res