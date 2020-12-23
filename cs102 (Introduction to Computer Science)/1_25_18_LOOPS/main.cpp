#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
	char gender;
	int fcount=0, mcount=0;
	
	cout << "Enter the gender: ";
	cin >> gender;
	
	if (gender == 'F')
		fcount++; //done only on true
	else 
		mcount++; //done only on false
		
	cout << "The number of females " << fcount << " and males " << mcount << endl;
	return 0;
}