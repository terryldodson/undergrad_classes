//MiniLab 8 Part C
//Name: Terryl Dodson
//Date: 10/11/18
//Description: program adds two numbers together
//TA: Daniel

.section .rodata
prompt: .asciz "Enter left and right operands:\n" //creates prompt
scanner: .asciz "%d %d" //creates scanner
output: .asciz "%d + %d = %d\n" //creates output scanner

.section .text
.global main

main:
	addi sp, sp, -16 //i need 16 bytes on this stack (8 for return address - we need return address for any function(anytime we use call), 4 for left and right operands)
	sd ra, 0(sp)
	
	//loads prompt into a0 and prints it
	la a0, [prompt]
	call printf@plt
	
	addi a1, sp, 8 //pointer arithmetic (add 8 bytes to stack pointer and storing it into a1)
	addi a2, sp, 12 //pointer arithmetic (add 12 bytes to stack pointer and storing it into a2)
	
	//loads first scanner into  a0 and scans numbers
	la a0, [scanner]
	call scanf@plt
	
	//loads the two numbers into word(int)
	lw a1, 8(sp)
	lw a2, 12(sp)
	
	//loads second scanner into print (output scanner)
	la a0, [output]
	
	//adds a1 and a2 and set the answer to a3
	add a3, a2, a1
	call printf@plt
	
	//deletes the space on stack for prompt, a1 and a2
	ld ra, 0(sp)
	addi sp, sp, 16
	
	ret
