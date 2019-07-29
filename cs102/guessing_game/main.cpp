#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; 

int main(){
	int num, quit = 0, guess = rand() % 101;
	
	cout << "Welcome to the guessing game. Guess a number between 0 - 100: ";
	cin >> num;
	
	while (quit != 1){
		
		if (guess < num){
			cout << "Too high. Guess again: ";
			cin >> num;
			continue;
		}//end of if
		
		else if (guess > num){
			cout << "Too low. Guess again: ";
			cin >> num;
			continue;
		}//end of if
		
		else if (guess == num){
			cout << "Great choice!!! The number was " << guess << endl;
			
			cout << "Would you like to quit?? (1 for yes, 2 for no): ";
			cin >> quit;
		
			if (quit == 1)
				break;
			
			else 
				guess = rand() % 101;
				continue;
		}//end of if
	}//end of while     
}//end of main