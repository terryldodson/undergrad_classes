#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#include "Slist.h"

// modify the data class and the associated input 
// and output operators to store, set and print a 
// line number identifier called ID

class data {
  public:
    // add operator< using lastname, firstname, phone number

    friend istream & operator>>(istream &, data &);
    friend ostream & operator<<(ostream &, const data &);

    bool operator<(const data &) const;

  private:
    string firstname;
    string lastname;
    string phonenum;
	int ID;
};

istream & operator>>(istream &in, data &r) {
  // write this to read data object data
  in >> r.firstname >> r.lastname >> r.phonenum;
  static int id;
  r.ID = ++id;
  return in;
}

ostream & operator<<(ostream &out, const data &r) {
  // write this to write data object data
  out << " " << setw(24) << left << r.lastname + " "  + r.firstname << r.phonenum << setw(9) << right << r.ID << "\n";
  return out;
}

bool data::operator<(const data &rhs) const {
    /*compare last name*/
    if(lastname != rhs.lastname)
        return lastname < rhs.lastname;

    /*compare first name*/
    if(firstname != rhs.firstname)
        return firstname < rhs.firstname;

    /*compare phone number*/
    return phonenum < rhs.phonenum;
}

template <typename T>
void printlist(T i, T p) {
  // template based iterator code for printing data to stdout
  while(i != p) {
    cout << *i;
    ++i;
  }
  return;
}

int main(int argc, char *argv[]) {
  // copy command-line check from QsortB.cpp,
	if(argc != 2) { 
		cerr << "usage: ./Slist_usage -quicksort|mergesort < file.txt" << endl;
        return 1;	
	}
		
	if(strcmp(argv[1], "-quicksort") != 0 && strcmp(argv[1], "-mergesort") != 0) {
    	cerr << "usage: ./Slist_usage -quicksort|mergesort < file.txt" << endl;
    	return 1;
    }
  // then modify to apply to this assignment

  slist<data> A;

  data din;
  while (cin >> din)
    A.push_back(din);

 // A.sort(command line mode option);
 // used sort from Slist.h
	if(strcmp(argv[1], "-quicksort") == 0)
		A.sort("quicksort");
	else
		A.sort("mergesort");

  printlist(A.begin(), A.end());
}
