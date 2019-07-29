//C++ Version:
//int main(int argc, char *argv[]) {
	//const unint8_t VPN_SHAMT[] = {12, 21, 30};
	//const unint64_t MASK_9 = 0x1ff;
	//const unint64_t MASK_12 = 0xfff;
	//if(argc < 2) {
		//printf("Usage: %s <address>\n", argv[0]);
		//return -1;
	//}

	//uint64_t vaddr;
	//uint64_t vpn;
	//uint64_t offset;

	//sscanf(argv[1], "%lx", &vaddr);
	//printf("Address: 0x%016lx\n", vaddr);

	//for(int i = 2; i >= 0; i--) {
		//vpn = (vaddr >> VPN_SHAMT[i]) & MASK_9;
		//printf("VPN[%d] = %u\n", i, vpn);
	//}

	//offset = vaddr & MASK_12;
	//printf("POFF = %03x (%u)\n", offset, offset);

	//return 0;
//}


//Description: Create a program in RISCV assembly that prints out vpn2, vpn1, vpn0, and po (page offset)
//In order to obtain those components, we have to break up the passed address into the components listed above
//DATE: 11/7/18
//COSC130
//TAs: Daniel, Jacob

.section .rodata //scanner and print statements
output: .asciz "Usage: %s 0x<address> \n" //prints the usage line 
output1: .asciz "Level     Index Byte Offset \n" //prints title for each column
output2: .asciz "VPN[%03d] = %u  (%d)\n" //outputs VPN and numbers
output3: .asciz "PO       = %x\n" //prints hexadecimal 
scan: .asciz "%lx" //scans hexadecimal

.section .text
.global main

main:
	addi sp, sp, -40 //created 40 bytes of space on the stack
	sd ra, 0(sp) //save ra onto the stack (return address)
	sd s0, 8(sp) //stored s0 8 bytes up on the stack
	sd s1, 16(sp) //stored s1 16 bytes on the stack
	sd s2, 24(sp) //stores s2 24 bytes on stack

	li t0, 2 //stores 2 in temporary register 

	beq a0, t0, 1f //checks to see if the user entered 2 arguments, if not prints usage line
	la a0, output
	ld a1, 0(a1) //stores "/.lab11" into a1
	call printf@plt
	j cleanup 

	1:
	
		ld a0, 8(a1) //have to go 8 bytes up to get to argv[1]
		la a1, scan //
		addi a2, sp, 32 //next offset avaible is 32 (contains passed address)

		call sscanf@plt //scans
		
		ld s0, 32(sp) //stores the passed address into s0

		li s1, 30 //stores 30 in saved register
		li s2, 2 //stores 2 in saved register

		la a0, output1 //inserts output1 in a0 to be printed out
		call printf@plt

		2:
			li t0, 0 //stores 0 in temporary
			li t2, 0x1ff //stores 0x1ff in temporary register (number to and vpn's by)
			li t3, 8 //stores 8 in temporary register

			blt s2, t0, 2f //less than

			srl t1, s0, s1 //t1 holds vpn
			and t1, t1, t2 //t1 now holds vpn number
			mul t4, t1, t3 //t4 holds byte offset

			la a0, output2
			mv a1, s2 //move s2 into a1
			mv a2, t1 //move t1 into a2
			mv a3, t4 //move t4 into a3
			call printf@plt //prints out level, index, and byte offset

			addi s1, s1, -9 //decrements s1 (number to shift by)

			addi s2, s2, -1 //decrements s2 (this is i in for loop)
			j 2b
		2:

		li t5, 0xfff //stores 0xfff into temporary value (number to and page offset by)
		and t6, s0, t5 //and the first 8 bits by 0xfff

		la a0, output3 //sends output3 to a0
		mv a1, t6 //move t6 to a1
		call printf@plt //prints out page offset number
	
	cleanup:
		ld ra, 0(sp) //loaded ra back on the stack
		ld s0, 8(sp) //loaded saved register back on the stack
		ld s1, 16(sp) //loaded saved register back on the stack
		ld s2, 24(sp) //loaded saved register back on the stack
		addi sp, sp, 40 //deleted 40 bytes of space off the stack

	ret
