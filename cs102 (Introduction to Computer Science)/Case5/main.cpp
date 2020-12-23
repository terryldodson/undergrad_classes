#include <stdio.h>
#include <iostream>
//#include <string>
using namespace std;

//declared-initialized constant and function declarations
const int NUMBERS = 20; 
void fillArray(int array1[], int& numbers);
void printArray(int array1[], int numbers);
int Divisor(int array1[], int array2[], int numbers, int divisor);
int findMin(int array2[], int j);
int findMax(int array2[], int j);

//calls the functions and declares the arrays
int main(){
	int num, arraynum, divisor=0, j; 
	int array1[NUMBERS];
	int array2[NUMBERS];
	
	cout << "Please enter how many numbers " << endl;
	cin >> num;
	
	fillArray(array1, num);
	
	cout << "Please enter a divisor: " << endl;
	cin >> divisor;
	j= Divisor(array1, array2, num, divisor);
	printArray(array2, j);

	cout << "The min = " << findMin(array2, j) << endl;
	cout << "The max = " << findMax(array2, j) << endl;
}//end of main

//functions: fills the array with the number of elements, then 
//the other functions prints out one number a line
//Also determines if the number is 20 or greater. If greater than 20, it asks them to enter 20 numbers
void fillArray(int array1[], int& numbers){
	int i;
	//int arraynum;
	
	if(numbers > NUMBERS)
		numbers = NUMBERS;
		
	cout << "Enter " << numbers << " numbers";
		for(i = 0; i < numbers; i++){
			cin >> array1[i];
	}//end of for loop
	
	cout << endl;
}//end of fillArray

void printArray(int array1[], int numbers){
	int i;
	if(numbers == 0)
		return;

		cout << "The array is: " << endl;
		for(i = 0; i < numbers; i++){
			cout << array1[i] << endl;
		}//end of for loop
}//end of printArray

int Divisor(int array1[], int array2[], int numbers, int divisor){
	int i, j=0;
	if(divisor == 0)
		return 0;
	for(i = 0; i < numbers; i++){
		if((array1[i] % divisor) == 0){
			array2[j] = array1[i];
			j++;
		}//end of if
	}//end of for loop
	return j;
}//end of Divisor

int findMin(int array2[], int j){
	int min = 999;
	if(j == 0)
		return j;
	for(int i = 0; i < j; i++){
		if(array2[i] < min)
			min = array2[i];
	}//end of for loop
	return min;
}//end of findMin

int findMax(int array2[], int j){
	int max = -10000;
	if(j == 0)
		return 0;
	for(int i = 0; i < j; i++){
		if(array2[i] > max)
			max = array2[i];
	}//end of for loop
	return max;
}//end of findMax
