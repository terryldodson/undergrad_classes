//Terryl Dodson
//January 25, 2019
//CS140: Lab 1d

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

//function declarations
void encode(string&, int);
void decode(string&, int);

int main(int argc, char *argv[]) {
	string command;
	
	//checks the number of arguments
	if(argc != 3) {
		cerr << "wrong number of arguments, should be 3" << endl;
		return 0;
	} //end of if statement

	command = argv[1];
	int num = atoi(argv[2]);
	
	//checks the command input
	if(command != "-encode" && command != "-decode") {
		cerr << "Please enter a valid command" << endl;
		return 0;
	} //end of if statement

	//checks the number to see if it's within range
	if(num < 0 || num > 9) {
		cerr << "Please enter a number within the range 0-9" << endl;
		return 0;
	} //end of if statement

	//stores the phrase and checks the command in order to call the correct function
	string phrase;
    while(getline(cin, phrase)) {
		if(command == "-encode")
			encode(phrase, num);
		else
			decode(phrase, num);
	} //end of while loop

	return 0;
} //end of main

void encode(string& phrase, int num) {
	for(int i = 0; i < phrase.length(); i++) {
		if(isalpha(phrase[i])) { //checks each char to see if it's a letter
			if(isupper(phrase[i]) && (phrase[i] + num) > 'Z' || islower(phrase[i]) && (phrase[i] + num) > 'z') {
				phrase[i] = phrase[i] -26 + num;
			} //end of inner if statement
			else
				phrase[i] = phrase[i] + num;
		} //end of outer if statement
	} //end of for loop
	cout << phrase << endl;
} //end of encode function

void decode(string& phrase, int num) {
	for(int i = 0; i < phrase.length(); i++) {
		if(isalpha(phrase[i])) { //checks each char to see if it's a letter
			if(isupper(phrase[i]) && (phrase[i] - num) < 'A' || islower(phrase[i]) && (phrase[i] - num) < 'a') {
				phrase[i] = phrase[i] +26 - num;
			} //end of inner if statement
			else
				phrase[i] = phrase[i] - num;
		} //end of outer if statement
	} //end of for loop
	cout << phrase << endl;
} //end of decode function
