#include <vector>
#include <string>
#include <iostream>

using namespace std;

#include "Person.h"
#include "Sptrsort.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    //output error message
	return 0;
  }

  person *n_person;
  vector<person *> person_list;

  type_enum type = UNKNOWN;
  type_enum g = UNKNOWN;

  int line = 1;
  size_t iL, iR;
  string input;

//  CS307: CHECK CORRECTESS OF XML HEADER 

  while (getline(cin, input)) {
	++line;

	if ((iL = input.find('<')) == string::npos) {
	  continue;

    } else if (input.compare(iL,9,"<faculty>") == 0) {
	  set type 

	  course.clear();

	} else if (input.compare(iL,10,"</faculty>") == 0) {

  //    CS307: CHECK CORRECTESS OF XML DATA
	//  CODE FOR ADDING FACULTY PERSON TO DATABASE

	  check type 
	  set subtype

	  n_person = ?

	  person_list.push_back(n_person);

	  reset type
	  reset subtype

	  continue;

	} else if (input.compare(iL,9,"<student>") == 0) {
	  set type

	  course.clear();
	  gp.clear();

	} else if (input.compare(iL,10,"</student>") == 0) {

      //CS307: CHECK CORRECTESS OF XML DATA
	 // CODE FOR ADDING STUDENT PERSON TO DATABASE

	  check type 
	  set subtype

	  n_person = ?

	  person_list.push_back(n_person);

	  reset type
	  reset subtype

	  continue;

	} else if (input.compare(iL,5,"<name") == 0) {
	  iL = input.find("=\"", iL);
	  iR = input.find("\"/>", iL+2);

      //CS307: CHECK CORRECTESS OF XML DATA
	  //CODE FOR EXTRACTING NAME (using iL, iR)

	} else if (input.compare(iL,10,"<g=") == 0) {
	  iL = input.find("=\"", iL);
	  iR = input.find("\"/>", iL+2);

      //CS307: CHECK CORRECTESS OF XML DATA
	  //CODE FOR EXTRACTING CATEGORY (using iL, iR)

	} else if (input.compare(iL,7,"<course") == 0) {
	  iL = input.find("=\"", iL);
	  iR = input.find("\"", iL+2);

      //CS307: CHECK CORRECTESS OF XML DATA
	  //CODE FOR EXTRACTING COURSE (using iL, iR)

	  iL = iR;
	  if (type == FACULTY) {
	    iR = input.find("/>", iL+1);
	  } else if (type == STUDENT) {
	    iL = input.find("gp=\"", iL);
	    iR = input.find("\"/>", iL+4);

        //CS307: CHECK CORRECTESS OF XML DATA
	    //CODE FOR EXTRACTING GRADE (using iL, iR)
	  }
	}
  }

 // EXTRACT LIST OF POINTERS TO PERSON, FACULTY OR STUDENT
 // ENTRY, SORT USING SPTRSORT AND PRINT RESULT TO STDOUT

  //NOTE: PERSON, FACULTY AND STUDENT EACH HAVE THEIR OWN
  //OVERLOADED COMPARISON OPERATOR (--> DIFFERENT SORTING)

  //RELEASE ALL DYNAMICALLY ALLOCATED MEMORY
}
