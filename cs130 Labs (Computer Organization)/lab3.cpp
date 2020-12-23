//lab3.cpp
//COSC130
//Students I worked with: Daniel, Brent
//TAs I worked with: Daniel, Leroy
//<YOUR NAME>: Terryl Dodson
//<THE DATE>: September 7, 2018
//Lab Synopsis: Created a floating pointing calculator by using bitwise operations. Implemented add, multiply, decode, encode, and normalize function. Also added three additional functions for binary 
//addition, binary multiply, and twos complement

#include <cstdio>
struct Real
{
     //sign bit
     int sign;
     //UNBIASED exponent
     long exponent;
     //Fraction including implied 1 at bit index 23
     unsigned long fraction;
};

//function prototype
Real Decode(int float_value);
int Encode(Real real_value);
Real Normalize(Real value);
Real Multiply(Real left, Real right);
Real Add(Real left, Real right);
unsigned long BinaryAddition(unsigned long, unsigned long);
long TwoComplement(long);

int main(int argc, char *argv[]) {	
     int left, right;
     char op;
     int value;
     Real rLeft, rRight, result;
     if (argc < 4) {
          printf("Usage: %s <left> <op> <right>\n", argv[0]);
          return -1;
     }
     sscanf(argv[1], "%f", (float *)&left);
     sscanf(argv[2], "%c", &op);
     sscanf(argv[3], "%f", (float *)&right);
     rLeft = Decode(left);
     rRight = Decode(right);
     if (op == 'x') {
          result = Multiply(rLeft, rRight);
     }
     else if (op == '+') {
          result = Add(rLeft, rRight);
     }
     else {
          printf("Unknown operator '%c'\n", op);
          return -2;
     }
     value = Encode(result);
     printf("%.3f %c %.3f = %.3f (0x%08x)\n",
            *((float*)&left),
            op,
            *((float*)&right),
            *((float*)&value),
            value
            );
     return 0;
}
//Implement the following functions

Real Decode(int float_value){
	Real transform;
	
	//fraction
	transform.fraction = (float_value & 0x7fffff) | (1 << 23);

	//exponent
	transform.exponent = ((float_value & 0x7f800000) >> 23) - 127;

	//sign		
	transform.sign = (float_value >> 31) & 1;

	return transform;
}

int Encode(Real real_value){
	int num = 0;
	int num1 = 1;
	
	//fraction
	num1 = num1 << 23;
	real_value.fraction &= ~num1;
	num |= real_value.fraction;

	//exponent
	num |= (real_value.exponent + 127) << 23;

	//sign
	num |= (real_value.sign << 31);

	return num;
}

Real Normalize(Real value) {
	long exponent = value.exponent;
	unsigned long fraction = value.fraction;
	Real finalResult;
	
	int i = 63;

	//finds where the 1 is and breaks when it finds it
	while(i) {
		if((fraction >> i) & 1) {
			break;
		}
		else {
			i--;
		}
	}

	//shifts the exponent and fraction according to the bit number
	if(23 > i) {
		fraction <<= 23 - i;
		exponent -= 23 - i;
	}

	else {
		fraction >>= i - 23;
		exponent += i - 23;
	}
	
	//set values of finalResult
	finalResult.sign = value.sign;
	finalResult.exponent = exponent;
	finalResult.fraction = fraction;

	return finalResult;
}

Real Multiply(Real left, Real right){
	Real sum;
	unsigned int num = 0b1;

	sum.sign = left.sign ^ right.sign;

	sum.exponent = BinaryAddition(left.exponent, right.exponent);
	
	//as long as left.fraction doesn't equal 0, we add the sum and right fraction
	//then we shift one to the right and the other to the left so we can do the same thing but with the next column
	while(left.fraction) {
		if((left.fraction & num) == 0b1) 
			sum.fraction = BinaryAddition(sum.fraction, right.fraction); 
		else
			right.fraction = 0;

		left.fraction >>= 1;
		right.fraction <<= 1;
	}

	return Normalize(sum);
}

Real Add(Real left, Real right){
	Real largest; //greater exponent
	Real smallest; //smaller exponenet
	Real sum;
	
	//sets exponent, fraction and sign depending on which exponent is the largest
	if(left.exponent > right.exponent) {
		largest.exponent = left.exponent;
		smallest.exponent = right.exponent;
		largest.fraction = left.fraction;
		smallest.fraction = right.fraction;
		largest.sign = left.sign;
		smallest.sign = right.sign;
		sum.sign = largest.sign;
	}

	else {
		largest.exponent = right.exponent;
		smallest.exponent = left.exponent;
		largest.fraction = right.fraction;
		smallest.fraction = left.fraction;
		largest.sign = right.sign;
		smallest.sign = left.sign;
		sum.sign = largest.sign;
	}
	
	//as long as the exponents don't equal, we shift the fraction and increment the exponent
	while(smallest.exponent != largest.exponent) {
		smallest.fraction = smallest.fraction >> 1;
		smallest.exponent = smallest.exponent + 1;
	}

	//set the exponent
	sum.exponent = smallest.exponent;

	//add two fraction in order to obtain sum fraction
	sum.fraction = BinaryAddition(largest.fraction, smallest.fraction);

	return Normalize(sum);
}

unsigned long BinaryAddition(unsigned long num1, unsigned long num2) { //Leroy told me to add this extra add function
	int carry;
	
	//as long as num2 doesn't equal 0, we keep adding and shifting to the left 1 every iteration
	while(num2 != 0) {
		carry = num1 & num2;
		num1 = num1 ^ num2;
		num2 = carry << 1;
	}
	return num1;
}

long TwoComplement(long negative) { //added inverse of binary plus 1 which is twos complement
	return BinaryAddition( ~negative, 1);
}


