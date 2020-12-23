#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

const int COOKIES_CALORIES = 210;

int main(){
	
	int weight, height, age, num_cookies;
	double BMR;
	char gender;
	
	cout << "Please provide your basic information " << endl;
	cout << "male or female (m or f)?";
	cin >> gender;
	
	cout << " age in years?";
	cin >> age;
	
	cout << " weight in kg?";
	cin >> weight;
	
	cout << " height in cm?";
	cin >> height;
	cout << endl;
	
	if ((age >= 65 && gender == 'm') || gender == 'f') {
		BMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
	}
	
	else if (gender == 'm') {
		BMR = 88.362 + (13.397 * weight) + ( 4.799 * height) - ( 5.677 * age);
	}
	
	num_cookies = BMR/COOKIES_CALORIES;
	
        if (gender == 'm') {
           cout << endl << "The BMR for a " << weight << " kg male who is " << age << " years old is " << fixed << setprecision(0) << BMR << ". "<< endl;
        }

        else if (gender == 'f') {
           cout << endl <<"The BMR for a " << weight << " kg female who is " << age << " years old is " << fixed << setprecision(0) << BMR << ". " << endl;
        }
	
	cout << "number of cookies eaten = " << num_cookies << endl;
}