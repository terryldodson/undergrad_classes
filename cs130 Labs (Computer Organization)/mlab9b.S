.section .rodata
scan: .asciz "%d"
scanc: .asciz "%c"
output: .asciz "Result: %d %c  %d = %d\n"

.section .text
.global CalculateASM

CalculateASM:
	//int Calculate(int a[], int size);
	//a0  Calculate(a0, a1)
	li t1, 0 //int
	li t2, 0 //sum
	li t3, '+' 
	li t4, '-' 
1:
	beq t3, t0, 1f

	lw t5, 0(a0)
	add t2, t2, t5
	addi a0, a0, 4
	addi t1, t1, 1
	j 1b
1:
	
	div a0, t2, a1
	ret


main:
	addi sp, sp, -25 //created 25 bytes of space on stack
    sd a1, 8(sp) //stored a1 on 8th byte
    sd ra, 0(sp) //stored return address

    ld a0, 8(a1) //created 8 more bytes on top of the 8 for a0
    la a1, scan //scanned first operand and stored it in a1
    addi a2, sp, 16 //specifying the address for the first operand
    call sscanf@plt

	ld a0, 8(sp) // went to 8th spot in stack and loaded value into a0 (loaded pointer to argv[0])
    ld a0, 16(a0) // derefencing address of argv[0] + 16 (basically getting argv[2])
    la a1, scanc // scanned operator
    //char c
    //sscanf(argv[2], "%c", &c) 
    addi a2, sp, 20 //speicifying address to c
    call sscanf@plt

	ld a0, 8(sp) // went to 8th spot on stack
    ld a0, 24(a0) //assign a0 to store argv[3]
    la a1, scan
    addi a2, sp, 21 //add 21 to stack to store second integer
    call sscanf@plt

	lw a0, 16(sp) //loaded 16th(8-15) byte into a0 (which holds the first operand)
    lb t0, 20(sp) //loaded 20th (16-19) byte into t0 (which holds the operator)
    lw a1, 21(sp) //loaded 21st (20-25) byte into a1 (which holds the second operand)

	call CalculateASM@plt

    lw a1, 16(sp) //stores first operand in a1
    mv a4, a0 //move a0 into a4 (holds result) - a0 from functions (stored result in a0 in operator functins)
    lw a2, 20(sp) //stores operator in a2
    lw a3, 21(sp) //stores second operand in a3
    la a0, output //puts output format into a0
    call printf@plt

    //deleted the 25 bytes off stack
    ld ra, 0(sp)
    addi sp, sp, 25

    ret
