#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;


int main(){
	int size = 0, i;
	double numbers, average, total = 0;

        do {
            cout << "Please enter the size of the data set (1-10 elements or 0 to quit): " << endl;
	    cin >> size;

             while (size < 0 || size > 11){
                 cout << endl;
                 cout << "Please enter the size of the data set (1-10 elements or 0 to quit): " << endl;
	         cin >> size;

             }//end of while

             if (size == 0) {
               break;
             }//end of if

            cout << "Please enter your data: " << endl; 

            for (i = 0; i < size; i++) {
		cin >> numbers;
		total += numbers;
	    }//end of for
        
	average = total/size;
	
	cout << "average = " << fixed << setprecision(3) << average << endl;	
        cout << endl;
   }//end of do

   while (size != 0);
}//end of main