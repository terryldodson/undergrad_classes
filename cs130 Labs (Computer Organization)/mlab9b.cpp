#include <cstdio>
using namespace std;

//created struct that holds info
struct MyStruct {
    int result;
    int *opr_left;
    int *opr_right;
};

//function prototype
void Calculate(MyStruct &s, char op);

//function definition
void Calculate(MyStruct &s, char op) {
    if(op == '+') { //if passed char is '+', add two numbers
        s.result = *(s.opr_left) + *(s.opr_right);
    }

    if(op == '-') { //if passed char is '-', subtract two numbers
        s.result = *(s.opr_left) - *(s.opr_right);
    }

    if(op != '+' && op != '-') { //if user doesn't pass either '+' or '-', return -1
        s.result = -1;
    }
}

extern "C" {
    void CalculateASM(MyStruct &s, char op);
}

int main() {
    MyStruct a; //creates an object of struct
    char b; //creates a char for operator

    a.opr_left = new int; //dynamic memory for opr_left
    a.opr_right = new int; //dynamic memory for opr_right

    printf("Enter left <op> right operands:"); //prompts user for left and right operand, and for operator
    scanf("%d %c %d", a.opr_left, &b, a.opr_right); //scans all three

    Calculate(a, b); //call function with passed values

    printf("C++: %d %c %d = %d\n", *(a.opr_left), b, *(a.opr_right), a.result); //prints out results
	printf("ASM: %d %c %d = %d\n", *(a.opr_left), b, *(a.opr_right), a.result); //prints out results

    return 0;
}  
