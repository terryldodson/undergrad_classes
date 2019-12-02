#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <iomanip>

typedef enum ARG_MODE {
	MODE_NULL = -1, MODE_PERSON, MODE_FACULTY, MODE_STUDENT
} arg_mode;

using namespace std;

#include "Person.h"
#include "Sptrsort.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    //output error message
	return 0;
  }

  ARG_MODE mode = MODE_NULL;
  if(strcmp(argv[1], "-person") == 0) mode = MODE_PERSON;
  if(strcmp(argv[1], "-faculty") == 0) mode = MODE_FACULTY;
  if(strcmp(argv[1], "-student") == 0) mode = MODE_STUDENT;
	
  if(mode == MODE_NULL) {
	cout << "ERROR\n";
	return 0;
  }
  
  person *n_person;
  vector<person *> person_list;
  vector<faculty *> faculty_list;
  vector<student *> student_list;

  type_enum type = UNKNOWN;
  //type_enum g = UNKNOWN;

  int line = 1;
  size_t iL, iR;
  string input;
  faculty *fperson;
  student *sperson;
  float gp;
  string course;

//  CS307: CHECK CORRECTESS OF XML HEADER 
  while (getline(cin, input)) {
	++line;

	if ((iL = input.find('<')) == string::npos) {
	  continue;

    } else if (input.compare(iL,9,"<faculty>") == 0) {
		type = FACULTY;
		n_person = new faculty();
		fperson = static_cast<faculty*>(n_person);
		course.clear();

	} else if (input.compare(iL,10,"</faculty>") == 0) {

  //    CS307: CHECK CORRECTESS OF XML DATA
	//  CODE FOR ADDING FACULTY PERSON TO DATABASE

	  //check type
	  if(type != FACULTY) {
		cout << "ERROR\n";
		return 1;
	  }
	  
	  //set subtype
	  person_list.push_back(n_person);

	  //reset type
	  type = UNKNOWN;
	
	  continue;

	} else if (input.compare(iL,9,"<student>") == 0) {
	  //set type
	  type = STUDENT;
	  n_person = new student();
	  sperson = static_cast<student*>(n_person);
	  course.clear();
	  //gp.clear();

	} else if (input.compare(iL,10,"</student>") == 0) {

      //CS307: CHECK CORRECTESS OF XML DATA
	 // CODE FOR ADDING STUDENT PERSON TO DATABASE

	  //check type
	  if(type != STUDENT) {
		cout << "ERROR\n";
		return 1;
	  }
		
	  person_list.push_back(n_person);

	  //reset type
	  type = UNKNOWN;

	  continue;

	} else if (input.compare(iL,5,"<name") == 0) {
	  iL = input.find("=\"", iL);
	  iR = input.find("\"/>", iL+2);
	  n_person->set_name(input.substr(iL+2, (iR-iL)-2));


      //CS307: CHECK CORRECTESS OF XML DATA
	  //CODE FOR EXTRACTING NAME (using iL, iR)

	} else if (input.compare(iL,10,"<category=") == 0) {
	  iL = input.find("=\"", iL);
	  iR = input.find("\"/>", iL+2);
	  n_person->get_type() = str2type(input.substr(iL+2, iR-2-iL));

      //CS307: CHECK CORRECTESS OF XML DATA
	  //CODE FOR EXTRACTING CATEGORY (using iL, iR)

	} else if (input.compare(iL,7,"<course") == 0) {
	  iL = input.find("=\"", iL);
	  iR = input.find("\"", iL+2);

      //CS307: CHECK CORRECTESS OF XML DATA
	  //CODE FOR EXTRACTING COURSE (using iL, iR)

//	  iL = iR;
	  if (type == FACULTY) {
		course = input.substr(iL+2, iR-2-iL);
		fperson -> add_course(course);
		iL = iR;
	    iR = input.find("/>", iL+1);
	  } else if (type == STUDENT) {
			course = input.substr(iL+2, iR-2-iL);
			iL = iR;
			iL = input.find("gp=\"", iL);
			iR = input.find("\"/>", iL+4);
				
			gp = atof(input.substr(iL+4, iR-iL-4).c_str());
			sperson -> add_course(course, gp);

        //CS307: CHECK CORRECTESS OF XML DATA
	    //CODE FOR EXTRACTING GRADE (using iL, iR)
	  }
	}
  }

 // EXTRACT LIST OF POINTERS TO PERSON, FACULTY OR STUDENT
 // ENTRY, SORT USING SPTRSORT AND PRINT RESULT TO STDOUT
//	cout << mode << endl;
	switch(mode) {
		case MODE_PERSON:
			//SORT BY PERSON
			sptrsort(person_list);

			//Print out every possible person
			for(int i = 0; i < person_list.size(); i++)
				cout << *person_list[i] << endl;
			break;

		case MODE_FACULTY:
			//construct a "faculty" vector
			for(int i = 0; i < person_list.size(); i++) {
				if((*person_list[i]).get_type() < STUDENT) {
					faculty_list.push_back(static_cast<faculty *>(person_list[i]));
				}
			}

			//sort it
			sptrsort(faculty_list);

			//print it
			for(int i = 0; i < faculty_list.size(); i++)
				cout << *faculty_list[i] << endl;
			break;

		case MODE_STUDENT:
			//construct a "student" vector
			for(int i = 0; i < person_list.size(); i++) {
				if((*person_list[i]).get_type() >= STUDENT) {
					student_list.push_back(static_cast<student *>(person_list[i]));
				}
			}

			//sort it
			sptrsort(student_list);

			//print it
			for(int i = 0; i < student_list.size(); i++)
				cout << *student_list[i] << endl;
			break;
	}	
  //NOTE: PERSON, FACULTY AND STUDENT EACH HAVE THEIR OWN
  //OVERLOADED COMPARISON OPERATOR (--> DIFFERENT SORTING)

  //RELEASE ALL DYNAMICALLY ALLOCATED MEMORY
}
