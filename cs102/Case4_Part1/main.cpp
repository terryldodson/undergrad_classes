#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

//function declarations-
void menu();
int SimpleSum(int x, int y);
double SimpleDivision(double a, double b);
double ComplexDivision(double a, double b, double c, double d);
int Max(int a, int b, int c);
double Hypothenuse(double a, double b);
double CubicEquation(double a, double b, double c, double d, double e);
void MinMax(int x, int y, int z, int& min, int& max0);
void Modulus(int x1, int y, int& quotient, int& remainder);

int main()
{
	int sum1, sum2, sum, cdivision1, cdivision2, cdivision3, cdivision4, max1, max2, max3, max4, max, minmax1, minmax2, minmax3, min, max0, x1, y, quotient, remainder;
	double sdivision1, sdivision2, simdivision, compdivision, hyp1, hyp2, hypothenuse, cub1, cub2, cub3, cub4, x, cubicequation;
	int selection, num;
	
	while(selection != 9){
		menu();
		cout << endl;
		cout << "Enter the number of the operation you wish to perform: ";
		cin >> selection;
		
		//switch finds which one to call due to the selection input
		switch(selection){
			case 1:
				cout << "Please enter two integers: " << endl;
				cin >> sum1 >> sum2;
				sum = SimpleSum(sum1,sum2);
				cout << "sum = " << sum << endl << endl;
				break;
			case 2:
				cout << "Please enter two integers: " << endl;
				cin >> sdivision1 >> sdivision2;
				simdivision = SimpleDivision(sdivision1, sdivision2);
				cout << "quotient = " << simdivision << endl << endl;
				break;
			case 3:
				cout << "Please enter four integers: " << endl;
				cin >> cdivision1 >> cdivision2 >> cdivision3 >> cdivision4;
				compdivision = ComplexDivision(cdivision1, cdivision2, cdivision3, cdivision4);
				cout << "quotient = " << compdivision << endl << endl;
				break;
			case 4: 
				cout << "Please enter three integers: " << endl;
				cin >> max1 >> max2 >> max3;
				max = Max(max1, max2, max3);
				cout << "maximum = " << max << endl << endl;
				break;
			case 5:
				cout << "Please enter the two side lengths: " << endl;
				cin >> hyp1 >> hyp2;
				hypothenuse = Hypothenuse(hyp1, hyp2);
				cout << "hypotenuse = " << hypothenuse << endl << endl;
				break;
			case 6: 
				cout << "Please enter four coefficients and x: " << endl;
				cin >> cub1 >> cub2 >> cub3 >> cub4 >> x;
				cubicequation = CubicEquation(cub1, cub2, cub3, cub4, x);
				cout << "cubic result = " << cubicequation << endl << endl;
				break;
			case 7: 
				min=0;
				max0=0;
				cout << "Please enter three integers: " << endl;
				cin >> minmax1 >> minmax2 >> minmax3;
				MinMax(minmax1, minmax2, minmax3, min, max0);
				cout << "min = " << min << endl;
				cout << "max = " << max0 << endl << endl;
				break;
			case 8: 
				cout << "Please enter two integers: " << endl;
				cin >> x1 >> y;;
				Modulus(x1, y, quotient, remainder);
				cout << "quotient = " << quotient << endl;
				cout << "remainder = " << remainder << endl << endl;
				break;
			case 9:
				break;
		}//end of switch
	}//end of while
}//end of main

//menu is a function that only prints out the menu
void menu(){
	cout << "Please make a selection from the following menu " << endl;
	cout << endl;
	cout << "1. Simple Sum " << endl;
	cout << "2. Simple Division " << endl;
	cout << "3. Complex Division " << endl;
	cout << "4. Max " << endl;
	cout << "5. Hypotenuse " <<  endl;
	cout << "6. Cubic Equation " << endl;
	cout << "7. MinMax " << endl;
	cout << "8. Modulus " << endl;
	cout << "9. Quit " << endl;
}

//starts the different types of functions for the different math options
int SimpleSum(int x, int y){
	int sum;
	sum = x + y;
	return sum;
}//end of SimpleSum function

double SimpleDivision(double a, double b){
	double sdivision;
	sdivision = (a/b);
	return sdivision;
}//end of SimpleDivision function

double ComplexDivision(double a, double b, double c, double d){
	double cdivision;
	cdivision = (a + b + c)/d;
	return cdivision;
}//end of ComplexDivision function

int Max(int a, int b, int c){
	int max = 0;
	if (a >= b && a >= c)
		max = a;
	else if (b >= a && b >= c)
		max = b;
	else if ( c >= a && c >= b)
		max = c;
	return max;
}//end of Max function

double Hypothenuse(double a, double b){
	double hyp;
	hyp = sqrt(pow(a,2) + pow(b,2));
	return hyp;
}//end of Hypothenuse function

double CubicEquation(double a, double b, double c, double d, double e){
	double cubeq;
	cubeq = (a * pow(e,3)) + (b * pow(e,2)) + (c * e) + d;
	return cubeq;
}//end of CubicEquation function

void MinMax(int x, int y, int z, int& min, int& max0){
	int minmax;
	if (x > y && x > z)
		max0 = x;
	else if (y > x && y > z)
		max0 = y;
	else if (z > x && z > y)
		max0 = z;
		
	if (x < y && x < z)
		min = x;
	else if (y < x && y < z)
		min = y;
	else if (z < x && z < y)
		min = z;
}//end of MinMax function

void Modulus(int x1, int y, int& quotient, int& remainder){
	quotient = x1/y;
	remainder = x1 % y;
}//end of Modulus function

