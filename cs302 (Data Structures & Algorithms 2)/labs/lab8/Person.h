#ifndef __PERSON_H__ 
#define __PERSON_H__

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <cstring>

using namespace std;

enum type_enum { UNKNOWN=-1, FACULTY=0,  ASST_PROF=1, ASSOC_PROF=2, FULL_PROF=3,
                 STUDENT=10, FRESHMAN=11, SOPHOMORE=12, JUNIOR=13, SENIOR=14 };

type_enum str2type(const string &s);
string type2str(const type_enum &t);


//class person DEFINITION -- base class
class person {
	public:
		//constructor
		person();
		person(const string&, type_enum = UNKNOWN);

		//get functions
		bool operator<(const person &);
		void set_name(string);
		string &get_name();
		void set_type(type_enum);
		type_enum &get_type();
		void set_category(type_enum);
		type_enum get_category();

	private:
		map<string,float> courselist;
		

	protected:
		//generic data
		string name;
		type_enum type;
		type_enum category;

		//virtual functions (must be overloaded)
		virtual void print_personinfo(ostream &) = 0;
		virtual void print_courseinfo(ostream &) = 0;

	friend ostream &operator<<(ostream&, person&);
};	

//class faculty DEFINITION -- derived class
class faculty : public person {
	public:
		//constructor
		faculty();
		faculty(const string&, type_enum = UNKNOWN);

		bool operator<(const faculty &);
		void add_course(string &);

	private:
		set<string> courselist;
		void print_personinfo(ostream &);
		void print_courseinfo(ostream &);
};

//class student DEFINITION -- derived class
class student : public person {
	public:
		//constructor
		student();
		student(const string&, type_enum = UNKNOWN);

        bool operator<(const student &);
        void add_course(string&, float);

    private:
        map<string,float> courselist;
        void print_personinfo(ostream &);
        void print_courseinfo(ostream &);
};
#endif

