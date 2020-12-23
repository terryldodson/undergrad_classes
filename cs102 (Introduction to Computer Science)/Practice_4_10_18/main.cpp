#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

ifstream fin;
string sname;
int sgrade;

class Student{
//member variables
	string name;
	double grade;
public: 
//constructors
	Student();
	Student(string n, double g);
//member methods (functions)
	void printStudent();
	string getName() const;
	int getGrade() const;
};

//constructors
Student::Student(){
}

Student::Student(string n, double g){
	name = n;
	grade = g;
}

//prototype for function
void sortStudent(vector <Student>& myS);

int main(int argc, char **argv){
//create the vector
	vector <Student> myS;
//declare the temp variables needed for input and the file
	while(fin >> sname >> sgrade){
		Student temp(sname, sgrade);
		myS.push_back(temp);
	}
	
	for(int i = 0; i < myS.size(); i++){
		myS[i].printStudent();
	}
	
	//call the sortStudent function
	sortStudent(myS);
	mysteryA(myS);
}

//member methods (functions)
void Student::printStudent(){
	cout << left << setw(25) << name << setw(25) << right << grade << endl;
}

string Student::getName() const{
	return name;
}

int Student::getGrade() const{
	return grade;
}

void sortStudent(vector <Student>& myA){
	bool sorted = 0;
		Student temp;
		int i;
		while(!sorted){
			sorted = 1;  //assume the vector is sorted
			for (i = 1; i < myA.size(); i++){   //start i at 1, because we are comparing it with the previous item in the list
				if(myA[i-1].getGrade() < my=A[i].getGrade()){  //variable to sort around (grade)
					temp = myA[i-1];
					myA[i-1] = myA[i];
					myA[i] = temp;
					sorted = 0;
				}//end of if
			}//end of for
		}//end of while
}//end of function

//reverse the vector (make it backwards)
void mysteryA(vector <Student> & myA){
	Student temp;
	int i;
	int sizeA = myA.size();
	for(i = 0; i < sizeA/2; i++){
		temp = myA[i];
		myA[i] = myA[sizeA-1-i];
		myA[sizeA-1-i] = temp;
	}//end of for
}// of function


