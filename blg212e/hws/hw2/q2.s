; Furkan Salik 150200056

SIZE 			EQU 50		;Global variable for array capacity
ARR_MEMORY_SIZE		EQU SIZE * 4	;Global variable for array size in RAM

			AREA arr_0, data, readwrite
			ALIGN					
array 		SPACE ARR_MEMORY_SIZE				
array_end										

			AREA part2, code, readonly
			ENTRY
			THUMB
			ALIGN
__main		PROC
			EXPORT __main
			LDR r0,=array
			MOVS r1,#ARR_MEMORY_SIZE
			BL defineNumbers
			SUBS r2, r1, #4
			MOVS r1, #0
			BL quickSort
inf			B inf	;while(1)
			

defineNumbers		;Parameters: R0=arr, R1=ARR_MEMORY_SIZE
			PUSH {r4,r5,r6}	;Save r4,r5,r6 to restore later
			MOVS r2, #0		;r2=temp
			MOVS r3, #0		;r3=i in iteration
			MOVS r4, #0		;r4=array element address
dn_loop		CMP r4, r1
			BEQ dn_endloop
			MOVS r6, #0
			ADDS r6, #15
			ADDS r2, r2, r6
			LSLS r5, r2, #5
			EORS r2, r2, r5
			LSRS r5, r2, #4
			EORS r2, r2, r5
			LSLS r5, r2, #1
			EORS r2, r2, r5
			STR r2, [r0, r4]
			ADDS r3, #1		;increase iterator i
			ADDS r4, #4		;increase array element address
			B dn_loop
dn_endloop	POP {r4,r5,r6}
			BX LR
			
quickSort		;Parameters: r0=arr, r1=l, r2=h
			PUSH {r1,r2,r3,LR}	;Save LR since this subroutine calls another one
			CMP r1, r2	;Compare l and h
			BGE	qs_end	;If l<h, jump to qs_cond
qs_cond		BL partition
			MOVS r3, r0		;r3=p_index
			PUSH {r2}
			SUBS r2, r3, #4		;r2=p_index-1
			BL quickSort
			POP {r2}
			PUSH {r1}
			ADDS r1, r3, #4
			BL quickSort
			POP {r1}
qs_end		POP {r1,r2,r3,PC}

partition		;Parameters: r0=arr, r1=l, r2=h		Returns with r0
			PUSH {r3,r4,r5,r6,LR}
			LDR r3, [r0, r2]	;r3=pivot value
			SUBS r4, r1, #4		;r4=i=l-1
			MOVS r5, r1			;r5=iterator j
prt_loop	CMP r5, r2
			BEQ prt_endloop
			LDR r6, [r0,r5]		;r6=arr[j]
			CMP r6, r3
			BGE prt_contloop
prt_loop_condition	ADDS r4, #4		;increase i
			PUSH {r1,r0}
			ADDS r1, r0, r5
			ADDS r0, r0, r4
			BL swapElements
			POP {r1,r0}
prt_contloop ADDS r5, #4		;increase j
			B prt_loop
prt_endloop	ADDS r4, #4
			ADDS r1, r0, r4
			ADDS r0, r0, r2
			BL swapElements
			MOVS r0, r4		;set return value to r0
			POP {r3,r4,r5,r6,PC}
			
swapElements	;Parameters: r0=first element's address, r1=second element's address
			PUSH {r3, r2}
			LDR r2, [r0]	;r2=first element's value
			LDR r3, [r1]	;r3=second element's value
			STR r2, [r1]	;store second element's value in first element's address
			STR r3, [r0]	;store first element's value in second element's address
			POP {r3,r2}
			BX LR
			ENDP
			END