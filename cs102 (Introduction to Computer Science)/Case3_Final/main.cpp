/* Name: Terryl Dodson 
 * Lab: Case 3 Final
 * Date: Febraury 12, 2018
 * Description: This program calculates the average of a certain set of data and finds the
 * overall average disregarding the maximum and minumum averages*/

#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;


int main(){
	int size = 0, i, a=0;
	double numbers, average, total = 0, totalAverage, overall, max, min;
	bool b=1;

		//this loop makes sure user puts valid number and stops if they do not
        do {
            cout << "Please enter the size of the data set (1-10 elements or 0 to quit): " << endl;
			 cin >> size;

			if(size == 0){
				break;
			}//end of if
			else if(size < 0 || size > 10){
				cout << endl;
				continue;
			}//end of else if
			
            cout << "Please enter your data: " << endl; 
			total = 0;
            for (i = 0; i < size; i++) {
				cin >> numbers;
				total += numbers;
			}//end of for
        
		average = total/size;
		
		if(b == 1) {
			min = average;
			max = average;
			b=0;
		}//end of if
		
		else if (max < average) {
			max = average;
		}//ende of else if
		
		else if (min > average) {
			min = average;
		}//end of else if
		
		totalAverage += average;
		a++;
	
		cout << "average = " << fixed << setprecision(3) << average << endl;	
		cout << endl;
   }//end of do
	while (size != 0);
	
	overall = totalAverage - min - max;
	
	cout << "\nfinal average = " << overall/(a-2);
	
	return 0;
}//end of main