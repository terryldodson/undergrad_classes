#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

int main(int argc, char *argv[]) {
	FILE* f;
	Dllist cList;
	Dllist hList;
	Dllist lList;
	Dllist fList;
	char* exe;
	char* file = "fmakefile";;
	IS is;

	if(argc == 1) {
		fprintf(stderr, "File doesn't exist\n");
		exit(1);
	} else{
		is = new_inputstruct(argv[1]);
	}

	while(get_line(is) >= 0) {

		if(is->fields[0] == "C") {
			dll_append(cList, new_jval_s(strdup(is->fields[0])));	
		}

		else if(is->fields[0] == "H") {
			dll_append(hList, new_jval_s(strdup(is->fields[0])));
		}

		else if(is->fields[0] == "L") {
			dll_append(lList, new_jval_s(strdup(is->fields[0])));
		}

		else if(is->fields[0] == "E") {
			exe = is->fields[1];
			printf("exe name: %s", exe);
		}

		else if(is->fields[0] == "F") {
			dll_append(fList, new_jval_s(strdup(is->fields[0])));
		}
	}
	
	//outisde while loop call the functions for each
	printf("%s\n", cList);
	printf("%s\n", hList);
	printf("%s\n", lList);
	printf("%s\n", fList);
}
