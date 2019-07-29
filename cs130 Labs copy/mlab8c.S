.section .rodata
msg: .asciz "Enter min and max:"
format: .asciz "%d %d"
result: .asciz "%d\n"

.section .text
.global main

get_random:
	addi sp, sp, -16
sd ra, 0(sp)

	//save min and max
	sw a0, 8(sp)
	sw a1, 12(sp)

	//a0 = rand()
	call rand

	//load min and max
	lw t0, 8(sp) //min
	lw t1, 12(sp) //max

	//(rand() % (max +  1 - min)) + min
	//max + 1
	addi t1, t1, 1
	//max - min
	sub t1, t1, t0
	//rand() % max
	rem a0, a0, t1
	//a0 + min
	add a0, a0, t0

	ld ra, 0(sp)
	addi sp, sp, 16
	ret

main:
	addi sp, sp, -16
	sd ra, 0(sp)

	//a0 = time(0)
	mv a0, zero
	call time@plt
	
	//srand(a0); - srand seeds random number (if we didnt seed it, it will			give you same random number every time
	call srand@plt

	la a0, msg
	call printf@plt

	//			a0	a1	a2
	//scanf("%d %d", &a, &b);
	la a0, format
	addi a1, sp, 8
	addi a2, sp, 12
	call scanf

	lw a0, 8(sp)
	lw a1, 12(sp)
	call get_random

	mv a1, a0
	la a0, result
	call printf@plt

	ld ra,0(sp)
	addi sp, sp, 16
	ret
