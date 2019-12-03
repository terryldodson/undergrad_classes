#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

#include "Person.h"

type_enum str2type(const string &s) {
    const char *s_d = s.c_str();

    if (strcmp(s_d, "faculty") == 0) return FACULTY;
    if (strcmp(s_d, "Assistant Professor") == 0) return ASST_PROF;
    if (strcmp(s_d, "Associate Professor") == 0) return ASSOC_PROF;
    if (strcmp(s_d, "Full Professor") == 0) return FULL_PROF;
    if (strcmp(s_d, "Student") == 0) return STUDENT;
    if (strcmp(s_d, "Freshman") == 0) return FRESHMAN;
    if (strcmp(s_d, "Sophomore") == 0) return SOPHOMORE;
    if (strcmp(s_d, "Junior") == 0) return JUNIOR;
    if (strcmp(s_d, "Senior") == 0) return SENIOR;

    return UNKNOWN;
}

string type2str(const type_enum &t) {
    string res = "Unknown";

    switch(t) {
        case UNKNOWN:
        case FACULTY:   res = "faculty"; break;
        case ASST_PROF: res = "Assistant Professor"; break;
        case ASSOC_PROF:res = "Associate Professor"; break;
        case FULL_PROF: res = "Full Professor"; break;
        case STUDENT:   res = "Student"; break;
        case FRESHMAN:  res = "Freshman"; break;
        case SOPHOMORE: res = "Sophomore"; break;
        case JUNIOR:    res = "Junior"; break;
        case SENIOR:    res = "Senior"; break;
    }

	return res;
}

//PERSON CLASS MEMBER FUNCTION IMPLEMENTATION
person::person() {
	name = string(" ");
}

person::person(const string& n, type_enum T) {
	name = n;	
	type = T;
}

bool person::operator<(const person &p) {
	/*compares name*/
	if(type < 4 && p.type > 9) //faculty is before student
		return true;
	else if(type > 4 && p.type < 9) //student is before faculty
		return false;
	else
		return name < p.name;
}

ostream &operator<<(ostream &os, person &p) {
	p.print_personinfo(os);
	p.print_courseinfo(os);
	
	return os;
}

void person::set_name(string n) {
	name = n;
}

string &person::get_name() {
	return name;
}

void person::set_type(type_enum T) {
	type = T;
}

type_enum &person::get_type() {
	return type;
}

void person::set_category(type_enum C) {
	category = C;
}

type_enum person::get_category() {
	return category;
}


//FACULTY CLASS MEMBER FUNCTION IMPLEMENTATION
faculty::faculty() {
	name = string("");
}

bool faculty::operator<(const faculty &f) {
	/*compares name*/
	if(type == f.type)
		return name < f.name;
	else if(type < f.type)
		return true;
	else
		return false;
}

faculty::faculty(const string& n, type_enum T) {
	name = n;
	type = T;
}

void faculty::add_course(string &name) {
	courselist.insert(name);
}

void faculty::print_personinfo(ostream &os) {
	os << setw(12) << right << "Name: " << "Dr. " + name << endl;
	os << setw(12) << right << "Category: " << type2str(type) << endl;
}

void faculty::print_courseinfo(ostream &os) {
	set<string>::iterator it;

	for(it = courselist.begin(); it != courselist.end(); it++) {
		os << setw(12) << right << "Course: " << /*setw(25) << left <<*/ *it << endl;
	}
}

//STUDENT CLASS MEMBER FUNCTIONS
student::student() {
	name = string ("");
}

bool student::operator<(const student &s) {
	if(type == s.type)
		return name < s.name;
	else if(type < s.type)
		return true;
	else
		return false;
}

void student::add_course(string &name, float gpa) {
	courselist.insert(pair<string, float> (name, gpa));
}

void student::print_personinfo(ostream &os) {
	os << setw(12) << right << "Name: " << name << endl;
	os << setw(12) << right << "Category: " << type2str(type) << endl;
}

void student::print_courseinfo(ostream &os) {
	map<string,float>::iterator it;
	float gpa_sum;
	size_t i;

	i = 0;
	gpa_sum = 0.0f;

	for(it = courselist.begin(); it != courselist.end(); it++, i++) {
		os << setw(12) << right << "Course: " << setw(25) << left << it->first << " ";

		os << fixed << setprecision(2) << it->second << " "; // << endl;
		gpa_sum += it->second;
		os << fixed << setprecision(2) << (gpa_sum / (i+1));

		os << endl;
	}
}

