//Lab 2A
//COSC130
//Lab synopsis: Lab creates a vector and allows the user to change the value of a given bit, and lets the user change the bit value. It also allows them to clear all bits, and return the number of sets.   Lastly, it can print out the set as a binary number and check the value of a given bit.
//it allows them to view the set as a binary
//Your Name: Terryl Dodson
//Date: 9/5/18
//List any TAs/students that you worked with here: Daniel, Grace, Jacob, Leroy, Camille
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//function prototypes
class BITSET {
	vector<int> bitset;
	
	public: 
		BITSET();
		bool Test(int);
		void Set(int);
		void Clear(int);
		int GetNumSets();
		int getBitset(int);
};

string ToBinary (int, int); 

int main () {
	BITSET bit;
	char input;
	int num, spaces = 4;
	
	//code that interacts with the user (switch statment to receive input, and call a function based off that input)
	do{
		printf("%s\n", "Please type a command");
		scanf("%c%*c", &input);
			switch(input) {
				case 't':
					scanf("%d%*c", &num);
					if(bit.Test(num) == true)
						printf("%d\n", 1);
					else
						printf("%d\n", 0);
				break;
				case 's':		
					scanf("%d%*c", &num);
					bit.Set(num);
				break;
				case 'c':
					scanf("%d%*c", &num);
					bit.Clear(num);
				break;
				case 'n':
					printf("%d\n", bit.GetNumSets());
				break;
				case 'g':
					scanf("%d%*c", &num);
					printf("%s\n", ToBinary(bit.getBitset(num), spaces).c_str());
				break;
				case 'q':
					return 0;
				break;
		}//end of switch
	} while(input != 'q');//end of do-while		
}//end of main

//sets the vector size back to 1
BITSET::BITSET(){
	bitset.resize(1);
}//end of BITSET constructor

//returns the bit at the index for the ToBinary function
int BITSET::getBitset(int index) {
	return bitset[index];
}//end of getBitset function

//checks the bitset at the given number, returns true if 1, false if 0
bool BITSET::Test(int num) {
	bool result;
	
	int set_index = num / 32;
	int bit = num % 32;
	
	if((bitset[set_index] >> bit & 1) == 1)
		result = true;
	else
		result = false;

	return result;
}//end of Test function

//sets the assigned number to the value 1
void BITSET::Set(int num) {
    unsigned set_index = num / 32;
	int bit = num % 32;

	if(set_index > bitset.size()-1)
		bitset.resize(set_index + 1);

	bitset[set_index] = bitset[set_index] |(1 << bit);
}//end of Set function

//sets the assigned number back to 0
void BITSET::Clear(int num) {
	int set_index = num / 32; 
	int bit = num % 32; 

	bitset[set_index] = bitset[set_index] & ~(1 << bit);

	while(bitset[bitset.size()-1] == 0)
		bitset.pop_back();
}//end of Clear function

//returns the size of the vector
int BITSET::GetNumSets() {
	return bitset.size();
}//end of GetNumSets function

//returns the set as a binary with a space after the given spaces
string ToBinary (int val, int spaces) {
    string a;
	int iter = 0;

	char num = val + '0';
	a = a + num;

    do{
		char v = ((val >> 1) & 1) + '0';
		a = v + a;
		
		iter++;
		
		if(iter == spaces){
			a = " " + a;
			iter = 0;
		}

        val = val >> 1;
    }while(val != 0);

    return a;
}//end of ToBinary function


