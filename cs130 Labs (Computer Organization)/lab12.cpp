//NAME: Terryl Dodson
//COSC130
//DATE: 11/9/18
//DESCRIPTION: Decode each instruction and print out depending on register
//TAs: Leroy, Daniel
//STUDENTS: Tyler

#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

//declaration of functions
unsigned long int opcodeFunct(unsigned int);
unsigned long int rdFunct(unsigned int);
unsigned long int funct3Funct(unsigned int);
unsigned long int rs1Funct(unsigned int);
unsigned long int rs2Funct(unsigned int);
unsigned long int funct7Funct(unsigned int);
string commandFunction(unsigned int, unsigned int, unsigned int);
string registerFunction(int);
int immFunct(unsigned int, unsigned int);
unsigned long int shamtFunct(unsigned int);
string orderParams(unsigned int opcode, unsigned int rdNum, unsigned int extendedOC, unsigned int rs1Num, unsigned int rs2, unsigned int funct7Num, int imm, unsigned int shamt);
int sign_extend(int num, int msb);

//declaration of global variables
char abi;
int msb;

int main (int argc, char **argv) {
	//local variables
	FILE *f;
	FILE *p;
	const char *filepath;
	const char *inputpath;
	unsigned long int opcode;
	unsigned long int rdNum;
	unsigned long int extendedOC;
	unsigned long int rs1Num;
	unsigned long int rs2Num;
	unsigned long int funct7Num;
	int imm;
	unsigned long int shamt;
	string command;

	/* ./prog <filename> */

	//checks to see if 4 parameters was passed in
	if(argc == 4) {
		abi = argv[3][0];
	}
	else
		abi = 'a';

	//stores inputs in variables
	inputpath = argv[1];
	filepath = argv[2];

	//opens a write to passed file
	if(filepath[0] == '-') {
		f = stdout;
	} else {
		f = fopen(filepath, "w");
	}

	//open and read file
	//goes through file and storews values needed
	p = fopen(inputpath, "r");
	fseek(p, 0, SEEK_END);
	long int size = ftell(p);
	int chunks = size/4;
	fseek(p, 0, SEEK_SET);
	unsigned int *array = new unsigned int [chunks];

	//sets variable names to functions (returns that number/string from instruction) also prints output
	for(int i = 0; i < chunks; i++) {
        fread(array + i, 1, 4, p);
		opcode = opcodeFunct(array[i]);
		rdNum = rdFunct(array[i]);
		extendedOC = funct3Funct(array[i]);
		rs1Num = rs1Funct(array[i]);
		rs2Num = rs2Funct(array[i]);
		funct7Num = funct7Funct(array[i]);
		imm = immFunct(array[i], opcode);
		shamt = shamtFunct(array[i]);
		command = commandFunction(opcode, extendedOC, funct7Num);
        fprintf(f, "     %-6s %-18s // 0x%08x\n", command.c_str(), orderParams(opcode, rdNum, extendedOC, rs1Num, rs2Num, funct7Num, imm, shamt).c_str(), array[i]);
	}

	delete [] array;
	//close file
	if (filepath[0] != '-') {
        fclose(f);
    }

	return 0;
}//end of main

//function shifts instruction and returns opcode
unsigned long int opcodeFunct(unsigned int instruction) {
	unsigned long int opcodeNum;

	opcodeNum = (instruction << 25) >> 25;

	return opcodeNum;
}//end of opcodeFunct

//function shifts instruction and returns rdNum
unsigned long int rdFunct(unsigned int instruction) {
	unsigned long int rdNum;

	rdNum = (instruction >> 7);
	rdNum = rdNum & 0b11111;

	return rdNum;
}//end of rdFunct

//function shifts instruction and returns immediate
int immFunct(unsigned int instruction, unsigned int opcodeNum) {
	unsigned long int rdNum;
	unsigned long int imm;

	if(opcodeNum == 55) {
		rdNum = (instruction >> 7);
		rdNum = rdNum & 0b11111;
	
		imm = (instruction >> 12) << 12;

		msb = 31;
	}

	else if(opcodeNum == 111) {
		rdNum = (instruction >> 7);
		rdNum = rdNum & 0b11111;

		imm = (instruction >> 31) << 8;
		imm |= (instruction >> 12) & 0b11111111; //bit numbers 19-12
		imm <<= 1; //imm = imm << 1
		imm |= (instruction >> 20) & 0b1;
		imm <<= 10;
		imm |= (instruction >> 21) & 0b1111111111;
		imm <<= 1;

		msb = 20;
	}

	else if(opcodeNum == 103) {
		rdNum = (instruction >> 7) & 0b11111;
		imm = (instruction >> 20);
	
		msb = 11;
	}

	else if(opcodeNum == 3) {
		rdNum = (instruction >> 7) & 0b11111;
		imm = (instruction >> 20);

		msb = 11;
	}

	else if(opcodeNum == 35) {
		imm = (instruction >> 7) & 0b11111;
		imm |= ((instruction >> 25) & 0b1111111) << 7;

		msb = 12;
	}

	else if(opcodeNum == 27) {
		shamtFunct(instruction);
	}

	//else(opcodeNum == 19) 
	else {
		rdNum = (instruction >> 7) & 0b11111;
		imm = (instruction >> 20) & 0b111111111111;
		
		msb = 11;
	}

	int result = sign_extend(imm, msb);

	return result;
}//end of immFunct

//function does sign extension 
int sign_extend(int num, int msb) {
	if((num >> msb) & 0b1) { //num is imm (immediate)
		int temp = -1;
		temp <<= msb + 1;
		return num | temp;
	}
	return num;
}//end of sign_extend funct

//function shifts instruction and returns shamt (when shamt is needed)
unsigned long int shamtFunct(unsigned int instruction) {
    unsigned long int shamt;

	shamt = (instruction >> 20) & 0b111111;
	
	return shamt;
}//end of shamt funct

//function shifts instruction and returns funct3
unsigned long  int funct3Funct(unsigned int instruction) {
	unsigned long int funct3Num;

	funct3Num = (instruction >> 12);
	funct3Num = funct3Num & 0b111;
	return funct3Num;
}//end of funct3Funct

//function shifts instruction and returns rs1
unsigned long int rs1Funct(unsigned int instruction) {
	unsigned long int rs1Num;

	rs1Num = (instruction >> 15);
	rs1Num = rs1Num & 0b11111;

	return rs1Num;
}//end of rs1Funct

//function shifts instruction and returns rs2
unsigned long int rs2Funct(unsigned int instruction) {
	unsigned long int rs2Num;

	rs2Num = (instruction >> 20);
	rs2Num = rs2Num & 0b11111;

	return rs2Num;
}//end of rs2Funct

//function shifts instruction and returns funct7
unsigned long int funct7Funct(unsigned int instruction) {
	unsigned long int funct7Num;

	funct7Num = (instruction >> 25);
	funct7Num = funct7Num & 0b1111111;

	return funct7Num;
}//end of funct7Funct

//function returns command based on instruction components
string commandFunction(unsigned int opcode, unsigned int extendedOC, unsigned int funct7Num) {
	string command; 
	
	if(opcode == 27 && extendedOC == 0) {
		command = "inv";
	}

	else if(opcode == 51 && extendedOC == 0 && funct7Num == 0) {
		command = "add";
	}

	else if(opcode == 51 && extendedOC == 0 && funct7Num == 32) {
		command = "sub";
	}

	else if(opcode == 51 && extendedOC == 1 && funct7Num == 0) {
		command = "sll";
	}

	else if(opcode == 51 && extendedOC == 4 && funct7Num == 0) {
		command = "xor";
	}

	else if(opcode == 51 && extendedOC == 5 && funct7Num == 0) {
		command = "srl";
	}

	else if(opcode == 51 && extendedOC == 5 && funct7Num == 32) { 
		command = "sra";
	}

	else if(opcode == 51 && extendedOC == 6 && funct7Num == 0) {
		command = "or";
	}

	else if(opcode == 51 && extendedOC == 7 && funct7Num == 0) {
		command = "and";
	}

	else if(opcode == 55) {
		command = "lui";
	}

	else if(opcode == 111) {
		command = "jal";
	}

	else if(opcode == 103) {
		command = "jalr";
	}

	else if(opcode == 3 && extendedOC == 0) {
		command = "lb";
	}

	else if(opcode == 3 && extendedOC == 1) {
		command = "lh";
	}

	else if(opcode == 3 && extendedOC == 2) {
		command = "lw";
	}

	else if(opcode == 35 && extendedOC == 0) {
		command = "sb";
	}

	else if(opcode == 35 && extendedOC == 1) {
		command = "sh";
	}

	else if(opcode == 35 && extendedOC == 2) {
		command = "sw";
	}

	else if(opcode == 19 && extendedOC == 0) {
		command = "addi";
	}

	else if(opcode == 19 && extendedOC == 4) {
		command = "xori";
	}

	else if(opcode == 19 && extendedOC == 6) {
		command = "ori";
	}

	else if(opcode == 19 && extendedOC == 7) {
		command = "andi";
	}

	else if(opcode == 3 && extendedOC == 6) {
		command = "lwu";
	}

	else if(opcode == 3 && extendedOC == 3) {
		command = "ld";
	}

	else if(opcode == 35 && extendedOC == 3) {
		command = "sd";
	}

	else if(opcode == 19 && extendedOC == 1) {
		command = "slli";
	}

	else if(opcode == 19 && extendedOC == 5 && funct7Num == 0) {
        command = "srli";
    }

	else if(opcode == 27 && extendedOC == 1 && funct7Num == 0) {
		command = "slliw";
	}

	else if(opcode == 27 && extendedOC == 5 && funct7Num == 0) {
		command = "srliw";
	}

	else if(opcode == 27 && extendedOC == 5 && funct7Num == 32) {
		command = "sraiw";
	}

	//else if(opcode == 19 & extendedOC == 5 & funct7Num == 32) 
    else {
		command = "srai";
    }	
	
	return command;
}//end of commandFunction

//function orders parameters per command based on instruction components
string orderParams(unsigned int opcode, unsigned int rdNum, unsigned int extendedOC, unsigned int rs1Num, unsigned int rs2, unsigned int funct7Num, int imm, unsigned  int shamt) {
    string params;

	if(opcode == 27 && extendedOC == 0) {
		params = "invalid";
	}

	else if(opcode == 51 && extendedOC == 0 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2); 
    }

	else if(opcode == 51 && extendedOC == 0 && funct7Num == 32) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
    }

	else if(opcode == 51 && extendedOC == 1 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
	}

	else if(opcode == 51 && extendedOC == 4 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
    }

	else if(opcode == 51 && extendedOC == 5 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
    }

	else if(opcode == 51 && extendedOC == 5 && funct7Num == 32) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
	}

	else if(opcode == 51 && extendedOC == 6 && funct7Num == 0) {
    	params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
    }

	else if(opcode == 51 && extendedOC == 7 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(rs2);
    }

	else if(opcode == 55) {
        params = registerFunction(rdNum) + ", " + to_string(imm);                
    }

	else if(opcode == 111) {
        params = registerFunction(rdNum) + ", " + to_string(imm);        
    }

	else if(opcode == 103) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(imm);        
    }

	else if(opcode == 3 && extendedOC == 0) {
        params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 3 && extendedOC == 1) {
        params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 3 && extendedOC == 2) {
    	params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 35 && extendedOC == 0) {
        params = registerFunction(rs2) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 35 && extendedOC == 1) {
        params = registerFunction(rs2) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 35 && extendedOC == 2) {
        params = registerFunction(rs2) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 19 && extendedOC == 0) {
    	params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(imm);
	}

	else if(opcode == 19 && extendedOC == 4) {
        params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
	}

	else if(opcode == 19 && extendedOC == 6) {
        params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
	}

	else if(opcode == 19 && extendedOC == 7) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(shamt);
    }

	else if(opcode == 19 && extendedOC == 5) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(shamt);
    }

	else if(opcode == 3 && extendedOC == 6) {
        params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
	}

	else if(opcode == 3 && extendedOC == 3) {
        params = registerFunction(rdNum) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 35 && extendedOC == 3) {
        params = registerFunction(rs2) + ", " + to_string(imm) + "(" + registerFunction(rs1Num) + ")";
    }

	else if(opcode == 19 && extendedOC == 1) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(shamt);
    }

	else if(opcode == 27 && extendedOC == 1 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(shamt);
	}

	else if(opcode == 27 && extendedOC == 5 && funct7Num == 0) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(shamt);
	}

	else if(opcode == 27 && extendedOC == 5 && funct7Num == 32) {
        params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + to_string(shamt);
	}

	//else(opcode == 19 & extendedOC == 5 & funct7Num == 32)
    else {
		params = registerFunction(rdNum) + ", " + registerFunction(rs1Num) + ", " + registerFunction(imm);
    }
	
	return params;
}//end of orderParams

//function returns correct registers due to argv[3]
string registerFunction(int a) {
	string rName;

	if(abi == 'a') {
		if(a == 0)
        	rName = "zero";
        else if(a == 1)
            rName = "ra";
        else if(a == 2)
            rName = "sp";
         else if(a == 3)
            rName = "gp";
         else if(a == 4)
            rName = "tp";
         else if(a == 5)
            rName = "t0";
         else if(a == 6)
            rName = "t1";
         else if(a == 7)
            rName = "t2";
         else if(a == 8)
            rName = "s0";
          else if(a == 9)
            rName = "s1";
          else if(a == 10)
            rName = "a0";
          else if(a == 11)
			rName = "a1";
          else if(a == 12)
            rName = "a2";
          else if(a == 13)
            rName = "a3";
          else if(a == 14)
            rName = "a4";
          else if(a == 15)
            rName = "a5";
          else if(a == 16)
            rName = "a6";
          else if(a == 17)
        	rName = "a7";
          else if(a == 18)
            rName ="s2";
          else if(a == 19)
            rName = "s3";
          else if(a == 20)
            rName = "s4";
          else if(a == 21)
            rName = "s5";
          else if(a == 22)
            rName = "s6";
          else if(a == 23)
            rName = "s7";
          else if(a == 24)
            rName = "s8";
          else if(a == 25)
            rName = "s9";
          else if(a == 26)
            rName = "s10";
          else if(a == 27)
            rName = "s11";
          else if(a == 28)
            rName = "t3";
          else if(a == 29)
            rName = "t4";
          else if(a == 30)
            rName = "t5";
          //else if(a == 31)
		else  
			rName = "t6";
	}//end of if 

	else {
		if(a == 0)
			rName = "x0";
		else if(a == 1)
            rName = "x1";
        else if(a == 2)
            rName = "x2";
        else if(a == 3)
            rName = "x3";
        else if(a == 4)
            rName = "x4";
        else if(a == 5)
            rName = "x5";
        else if(a == 6)
            rName = "x6";
        else if(a == 7)
            rName = "x7";
        else if(a == 8)
            rName = "x8";
    	else if(a == 9)
            rName = "x9";
        else if(a == 10)
            rName = "x10";
        else if(a == 11)
            rName = "x11";
        else if(a == 12)
            rName = "x12";
        else if(a == 13)
            rName = "x13";
        else if(a == 14)
            rName = "x14";
        else if(a == 15)
            rName = "x15";
        else if(a == 16)
            rName = "x16";
        else if(a == 17)
            rName = "x17";
        else if(a == 18)
            rName ="x18";
        else if(a == 19)
            rName = "x19";
        else if(a == 20)
            rName = "x20";
        else if(a == 21)
            rName = "x21";
        else if(a == 22)
            rName = "x22";
        else if(a == 23)
            rName = "x23";
        else if(a == 24)
            rName = "x24";
        else if(a == 25)
            rName = "x25";
        else if(a == 26)
            rName = "x26";
        else if(a == 27)
            rName = "x27";
 		else if(a == 28)
            rName = "x28";
        else if(a == 29)
            rName = "x29";
        else if(a == 30)
            rName = "x30";
          //else if(a == 31)
        else
            rName = "x31";
	} //end of else
	return rName;
}//end of registerFunction
