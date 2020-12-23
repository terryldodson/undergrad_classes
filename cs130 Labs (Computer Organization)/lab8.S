//Lab 8:: Created a lab that will add, subtract, multiply, divide, and find the remainder (coded in assembly)
//CS130
//Date: 10/15/18
//TA's: Leroy, Daniel, Jacob

.section .rodata 
scan: .asciz "%d"
scanc: .asciz "%c"
output: .asciz "Result: %d %c  %d = %d\n"

.section .text
.global main

add: //calls add function
	call addf@plt
	j out

addf: //adds a0 and a1 and stores value in a0
    add a0, a0, a1
	ret

sub: // calls subract function
	call subf@plt
	j out

subf: //subtracts a0 and a1 and stores value in a0
	sub a0, a0, a1
	ret

mult: //calls multiply function
	call multf@plt
	j out

multf: //multiplies a0 and a1 and stores value in a0
	mul a0, a0, a1
	ret

div: //calls divide function 
	call divf@plt
	j out

divf: //divides a0 by a1 and stores value in a0 (if right operand is 0, it returns -1)
	div a0, a0, a1
	ret

rem: //calls remainder function
	call remf@plt
	j out

remf: //finds the remainder of a0 divided by a1 and stores it in a0 (if right operand is 0, it returns 0)
	beq a1, zero, skip

	rem a0, a0, a1
	j continue

skip:
	mv a0, zero
continue:
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
	lb t1, 20(sp) //loaded 20th (16-19) byte into t0 (which holds the operator)
	lw a1, 21(sp) //loaded 21st (20-25) byte into a1 (which holds the second operand)

	li t0, '+' //loaded '+' into t0
	beq t1, t0, add //calls add function if user entered '+'

	li t0, '-' //loaded '-' into t0
	beq t1, t0, sub //calls sub function if user entered '-'

	li t0, 'x' //loaded 'x' into t0
	beq t1, t0, mult //calls mult if user entered 'x'

	li t0, '/' //loaded '/' into t0
	beq t1, t0, div //calls div if user entered '/'

	li t0, '%' //loaded '%' into t0
	beq t1, t0, rem //calls rem if user entered '%'

out: //adjust arguments accordingly for the printf function
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
