#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	/*char i, j;
	
	for (char j = 'a'; j <= 'e'; j++) {
			cout << j;
		for (char i='a'; i='e'; i++)
			cout << i << endl;
	}//end of for loop*/
	
	int id, examScore;
	int a, b, c;
	
	cin >> id;
	
	while (id != -1) {
		int sum = 0;
		for (int exam = 1; exam <= 3; exam++) {
			cin >> examScore;
			sum += examScore;
		}
		cout << "student id = " << id << "\t";
		cout << "average score = " << sum/3.0 << endl;
		cin >> id;
	}
}//end of main
