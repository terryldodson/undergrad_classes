/*Assignment Name: Case 1
 *Name: Terryl Dodson
 * Description: This program will be able to count the number of steps and translate that
 * into how many miles and feet the user walked*/

#include <iostream>
using namespace std;

int main()
{
	//this section of the code declares each variable that will be used in this program
    int number_of_miles, steps_per_mile, total_steps, integer_miles, feet;
	double fractional_miles;
	
	//this section prompts the user to enter in the amount of steps walked and the 
	//number of steps required to walk a mile
    cout << "Press return after entering a number." << endl;
	cout << "Enter the total number of steps walked: ";
	cin >> total_steps;
	cout << "Enter the number of steps required to walk a mile: ";
    cin >> steps_per_mile;
	cout << endl;
	
	//this section takes the numbers the user entered into the console, and does the 
	//calculations based off those numbers and sets the final number in the variable
	//that is on the left side of the assignment
	fractional_miles = (total_steps * 1.0) / steps_per_mile;
	integer_miles = total_steps / steps_per_mile;
	feet = total_steps % steps_per_mile  * (5280.0 / steps_per_mile);

	//this section prints out to the user the amount of steps and miles they walked
    cout << "If you have walked " << total_steps << " steps " << endl;
    cout << "and it takes " << steps_per_mile << " steps to walk a mile, " << endl;
    cout << "then you have walked " << fractional_miles << " miles." << endl;
	
	//this section prints out to the user the amount of miles and feet he walked
	cout << endl;
	cout << "You also have walked " << integer_miles << " miles and " << feet << " feet.";
	cout << endl;
	
    return 0;
} 