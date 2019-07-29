#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

const double WEIGHT = 2.2;
const double HEIGHT = 2.54;
 
int main(){
	//initializes variables
	int age, calories, num_food;
        double weight1, weight, height;
	double BMR;
	char gender, alevel, ans, y; //alevel - activity level
	string food;
	
	ans = 'y'; //sets variable answer to equal 'y' so while loop can run

	while (ans != 'n') { //start of while loop - prompts user for general information then does calculations based on that information
		cout << "Please provide your basic information " << endl;
		cout << "male or female (m or f)?";
		cin >> gender;
	
		cout << " age in years?";
		cin >> age;
	
		cout << " weight in pounds?";
		cin >> weight1;
	
		cout << " height in inches?";
		cin >> height;
		cout << endl;

		weight = weight1 / WEIGHT;
		height = height * HEIGHT;
	
		cout << "How active are you?" << endl;
		cout << "\ts - sedentary" << endl;
		cout << "\tc - casual exerciser--exercise occasionally" << endl; 
		cout << "\ta - active exerciser--exercise 3-4 days per week" << endl; 
		cout << "\td - devoted exerciser--exercise every day" << endl;
		cout << "Enter the letter association your activity level: ";
		cin >> alevel;
	
		cout << "\nWhat type of food do you want to eat? " << endl;
		cout << "Please use _ between words to create a single word.";
		cin >> food;
		cout << " How many calories per item? " << endl;
		cin >> calories;
                
		//uses the char they entereed in for how active they are to determine which case to go into
		//calculations differ by cases
		switch (alevel) {
		case 's':
			if ((age >= 65 && gender == 'm') || gender == 'f') {
				BMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
			}//end of if 
	
			else if (gender == 'm') {
				BMR = 88.362 + (13.397 * weight) + ( 4.799 * height) - ( 5.677 * age);
			}//end of else if
			BMR *= 0.95;
			break;
		case 'c':
			if ((age >= 65 && gender == 'm') || gender == 'f') {
				BMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
			}//end of if
	
			else if (gender == 'm') {
				BMR = 88.362 + (13.397 * weight) + ( 4.799 * height) - ( 5.677 * age);
			}//end of else if
			BMR *= 1.3;
			break;
		case 'a':
			if ((age >= 65 && gender == 'm') || gender == 'f') {
				BMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
			}//end of if
	
			else if (gender == 'm') {
				BMR = 88.362 + (13.397 * weight) + ( 4.799 * height) - ( 5.677 * age);
			}//end of else if
			BMR *= 1.4;
			break;
		case 'd':
			if ((age >= 65 && gender == 'm') || gender == 'f') {
				BMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
			}//end of if
	
			else if (gender == 'm') {
				BMR = 88.362 + (13.397 * weight) + ( 4.799 * height) - ( 5.677 * age);
			}//end of else if
			BMR *= 1.5;
			break;
		}//end of swtich 
	
		num_food = BMR/calories; //calculates amount of food they can eat
	
        if (gender == 'm') {
           cout << "The BMR for a " << weight1 << " pound male who is " << age << " years old is " << fixed << setprecision(0) << BMR << ". "<< endl;
        }//end of if - prints bmr

        else if (gender == 'f') {
           cout <<"The BMR for a " << weight1 << " pound female who is " << age << " years old is " << fixed << setprecision(0) << BMR << ". " << endl;
        }//end of else if - prints bmr
	   
		cout << "number of " << food << " eaten = " << num_food << endl;
	        cout << endl;
		cout << "Repeat the BMR calculation (y/n)? " << endl;
		cin >> ans;
	} //end of while loop - ask user if they want to continue and sets that variable into ans. if ans = y then the loop will continue
	return 0;
} //end of main