#ifndef __PERSON_H__ 
#define __PERSON_H__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum type_enum { UNKNOWN=-1, FACULTY=0,  ASST_PROF=1, ASSOC_PROF=2, FULL_PROF=3,
                 STUDENT=10, FRESHMAN=11, SOPHOMORE=12, JUNIOR=13, SENIOR=14 };

//class person DEFINITION -- base class
class person {
	public:
		//constructor
		person();
		person(const string&, type_enum = UNKNOWN);
		
		//get functions
		bool operator<(const person &);
		string &get_name();
		type_enum &get_type();
		type_enum &get_category();

	protected:
		//generic data
		string name;
		type_enum type;
		string category;

		//virtual functions (must be overloaded)
		virtual void print_personinfo() = 0;
		virtual void print_courseinfo() = 0;

	friend operator<<();
};	

//class faculty DEFINITION -- derived class
class faculty : public person {
	public:
		bool operator<();
		void add_course();

	private:
		vector<string> courselist;
		void print_personinfo();
		void print_courseinfo();
};

//class student DEFINITION -- derived class
class student : public person {
	public:
        bool operator<();
        void add_course();

    private:
        vector<string> courselist;
        void print_personinfo();
        void print_courseinfo();
	
};

#endif

