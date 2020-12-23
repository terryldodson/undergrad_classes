//Lab 1A
//COSC130
//Lab synopsis:
//	Implement code for 4 functions, that converts char to int, int to char, string to int, and int to string. 
//	These functions will assist in adding, subtracting, multiplying, and dividing numbers
//Your Name: Terryl Dodson
//Date: 8/24/18
//List any TAs/students that you worked with here: Daniel, Leroy
#include <iostream>nclude <string>
using namespace std;

//Prototypes for the functions that you will write
int  CharToInt(char v);
char IntToChar(int v);
int StringToInt(string val);
string IntToString(int val);

//function converts char to int
int  CharToInt(char v){
	return v - '0';
}

//function converts int to char
char IntToChar(int v){
	return v + '0';
}

//function converts string to int
int StringToInt(string val){
	int num = 1;
	char v;
	int let = 0;
	bool sign = false;
	
	//checks to see if number is a negative
	//if so, deletes negative sign and set sign to true
	if(val[0] == '-'){
		sign = true;
		val[0] = '0';
	}
	
	//goes over every char, converts it to a int and multiplies it by its assigned place (ones, tens, etc.)
	for(int i = val.length()-1; i >= 0; i--){
 		 v = val[i];
		 let += CharToInt(v)*num;
	     num *= 10;
	}
	
	//if number was negative, it makes it negative again
	if(sign){
		let = let * -1;
	}
	return let;
}

//function converts int to string
string IntToString(int val){
	string a;
	bool sign = false;

	//if number is a negative, makes it positive and assigns sign to true
	if(val < 0){
		sign = true;
		val = val * -1;
	}

	//as long as number doesn't equal 0, converts int to char and divides int by its place (ones, tens, etc.)
	do{
		a =  IntToChar(val%10) + a; 
		val /= 10;
	}while(val != 0);

	//assgins string to negative if it was negative
	if(sign){
		a = '-' + a;
	}

	return a;
}

int main(int argc, char *argv[])
{
        string sresult;
        int left;
        int right;
        char op;

        if (4 != argc) {
                printf("Usage: %s <left> <op> <right>\n", argv[0]);
                return -1;
        }
        //Notice that this calls your StringToInt. So, make sure you debug
        //StringToInt() to make sure that left and right get a proper
        //value.
        left = StringToInt(argv[1]);
        right = StringToInt(argv[3]);
        op = argv[2][0];
        //Calculate based on the op. Notice that this calls IntToString,
        //so debug your IntToString() function to make sure that sresult
        //is given the proper result. This assumes your StringToInt already
        //works.
        switch (op)
        {
                case 'x':
                        sresult = IntToString(left * right);
                        break;
                case '/':
                        sresult = IntToString(left / right);
                        break;
                case '+':
                        sresult = IntToString(left + right);
                        break;
                case '-':
                        sresult = IntToString(left - right);
                        break;
                case '%':
                        sresult = IntToString(left % right);
                        break;
                default:
                        sresult = IntToString(left);
                        break;
        }

        //Remember, printf is the only output function you may use for this lab!
        //The format string is %d %c %d = %s. This means that the first argument
        //is %d (decimal / integer), %c (character), %d (decimal /integer),
        //%s (string). Notice that because printf() is a C-style function, you
        //must pass strings as character arrays. We can convert a C++ string
        //to a character array (C-style string) by using the c_str() member function.
        printf("%d %c %d = %s\n", left, op, right, sresult.c_str());
        return 0;
}
