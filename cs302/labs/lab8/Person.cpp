#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "Person.h"

//PERSON CLASS MEMBER FUNCTION IMPLEMENTATION
person::person() {
	name = new string(" ");

}

bool person::operator<(const person &p) {
	/*compares name*/
	if(name != p.name)
		return name < p.name;
}

void person::set_name(string n) {
	name = n;
}

string person::get_name() {
	return name;
}


//FACULTY CLASS MEMBER FUNCTION IMPLEMENTATION

//STUDENT CLASS MEMBER FUNCTION IMPLEMENTATION
