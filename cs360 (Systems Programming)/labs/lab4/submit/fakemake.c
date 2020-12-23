/*
Name: Terryl Dodson
Date: 2/17/20
Description: Wrote our own makefile
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

void algorithm(char* a) {
	struct stat statbuf;
	struct stat obuf;
	struct stat hbuf;
	Dllist cList = new_dllist();
	Dllist hList = new_dllist();
	Dllist lList = new_dllist();
	Dllist fList = new_dllist();
	Dllist eList = new_dllist();
	Dllist oList = new_dllist();
	Dllist tmp = new_dllist();
	Dllist f = new_dllist();
	Dllist tmp1 = new_dllist();
	Dllist tmp2 = new_dllist();
	Dllist tmp3 = new_dllist();
	Dllist tmp4 = new_dllist();
	Dllist tmp5 = new_dllist();
	Dllist tmp6 = new_dllist();
	char* exe;
	char oFile;
	int exist = 0;
	int eexists = 0;
	int oexists = 0;
	int sys;
	int cmp = 0, echk=0; //recompile
	int ctime=0, htime, ltime, etime, ftime, otime=0;
	int num, num1, num2, num3, i=0;
	IS is;

	is = new_inputstruct(a);

	//while it reads a line (stop when there's no more lines to read in)
	while(get_line(is) >= 0) {

		//checks for blanks
		if(is->NF == 0) {
			continue;
		} //end of if

		//C list files
		else if(strcmp(is->fields[0], "C") == 0) {
			for(i = 1; i < is->NF; i++) {
				dll_append(cList, new_jval_s(strdup(is->fields[i])));	
			}
		} //end of if

		//H list files
		else if(strcmp(is->fields[0], "H") == 0) {
			for(i = 1; i < is->NF; i++) {
				dll_append(hList, new_jval_s(strdup(is->fields[i])));
			}
		} //end of else if

		//libraries
		else if(strcmp(is->fields[0], "L") == 0) {
			for(i = 1; i < is->NF; i++) {
				dll_append(lList, new_jval_s(strdup(is->fields[i])));
			}
		} //end of else if

		//executable
		else if(strcmp(is->fields[0], "E") == 0) {
			exe = strchr(is->fields[0], 'E');
			for(i = 1; i < is->NF; i++) {
				dll_append(eList, new_jval_s(strdup(is->fields[i])));
				echk++;
			}
			if (echk > 1) {
				fprintf(stderr, "fmakefile (%d) cannot have more than one E line\n", is->line);
				exit(1);
			}

		} //end of else if

		//flags list
		else if(strcmp(is->fields[0], "F") == 0) {
			for(i = 1; i < is->NF; i++) {
				dll_append(fList, new_jval_s(strdup(is->fields[i])));
			}
		} //end of else if

		else if(exe != NULL) {
			exe = strdup(is->fields[i]);
			echk++;
			if (echk > 1) {
				fprintf(stderr, "fmakefile (%d) cannot have more than one E line\n", is->line);
				exit(1);
			}
		}

		//if it didn't detect either letter print error
		else {
			fprintf(stderr, "Error: Unprocessed line. First character of line must be C, H, E, F, or L\n");
			exit(1);
		}
	} //end of while

	//checking the number executable number
	if(echk == 0) {
		fprintf(stderr, "No executable specified\n");
		exit(1);
	}

	//traverse through and set time
	dll_traverse(tmp3, hList) {		    
		exist = stat(tmp3->val.s, &hbuf);
		if(exist < 0) {
			fprintf(stderr, "Error: File '%s' does not exist\n", tmp->val.s);
		} //end of if
		else {
			if(htime < hbuf.st_mtime) {
				htime = hbuf.st_mtime;
			}
		}//end of else
	} //end of hList traverse

	//traverse through cList and compile when it needs too
	dll_traverse(tmp, cList) {
		//check to see if file exists
		num1 = stat(tmp->val.s, &statbuf);
		if(num1 < 0) {
			fprintf(stderr, "fmakefile: %s: No such file or directory\n", tmp->val.s);
			exit(1);
		} //end of if

		//set up gccString otherwise
		else {
			char gccString[256] = "gcc -c ";
			char oFile[100];	

			ctime = statbuf.st_mtime;

			//took .c off of file and added .o
			strcpy(oFile, tmp->val.s);
			oFile[strlen(oFile)-1] = 'o';

			oexists = stat(oFile, &obuf);

			otime = obuf.st_mtime;

			//compile if these conidtions are met
			if (oexists < 0 || otime < ctime || otime < htime) {

				dll_traverse(f, fList) {
					strcat(gccString, f->val.s);
					strcat(gccString, " ");
				} //end of fList traverse

				strcat(gccString, tmp->val.s);
				printf("%s\n", gccString);

				sys = system(gccString);

				//print out system fail
				if(sys != 0) {
					fprintf(stderr, "Command failed.  Exiting\n");
					exit(1);
				}//end of if

				cmp++;
			}//end of if

			//else take care of the oFiles
			else {
				char oFile1[100];

				strcpy(oFile1, tmp->val.s);
				oFile1[strlen(oFile1)-1] = 'o';
				oexists = stat(oFile1, &obuf);
				if(obuf.st_mtime > otime)
					otime = obuf.st_mtime;
			}//end of inner else
		}//end of else
	} //end of cList traverse

	//for the executable list
	dll_traverse(tmp1, eList) {
		eexists = stat(tmp1->val.s, &statbuf);

		//if these conditions are met, create gcc -o string
		if(eexists < 0 || cmp != 0 || statbuf.st_mtime < otime) {
			char gccString1[256] = "gcc -o ";
			strcat(gccString1, tmp1->val.s);

			dll_traverse(f, fList) {
				strcat(gccString1, " ");
				strcat(gccString1, f->val.s);
			}

			dll_traverse(tmp4, cList) {
				//added .o	
				strcat(gccString1, " ");
				char oFile2[100];
				strcpy(oFile2, tmp4->val.s);
				oFile2[strlen(oFile2)-1] = 'o';

				strcat(gccString1, oFile2);
			}

			dll_traverse(tmp5, lList) {	
				strcat(gccString1, " ");
				strcat(gccString1, tmp5->val.s);
			}

			printf("%s\n", gccString1);
			sys = system(gccString1);

			if(sys != 0) {
				fprintf(stderr, "Command failed.  Fakemake exiting\n");
				exit(1);
			}
		}//end of if

		else{
			//prints up to date if file doesn't need to be compiled
			dll_traverse(tmp6, eList) {
				printf("%s up to date\n", tmp6->val.s);
				exit(1);
			}//end of eList traverse
		}//end of else
	}//end of eList traverse

	//free memory
	dll_delete_node(cList);
	dll_delete_node(hList);
	dll_delete_node(lList);
	dll_delete_node(fList);
	dll_delete_node(eList);
	dll_delete_node(oList);
	jettison_inputstruct(is);
	exit(0);
} //end of algorithm function

int main(int argc, char *argv[]) {
	FILE *f;

	//checks the number of arguments
	if(argc > 2){
		fprintf(stderr, "Error: Too many arguments\n");
		exit(1);
	}

	//if equal to 2 and not null, call algorithm and pass it argv[1]
	else if(argc == 2){
		if((f = fopen(argv[1], "r")) != NULL){
			algorithm(argv[1]);
		}
		else{
			fprintf(stderr, "Error: file does not exist\n");
			exit(1);
		}
	}

	//if its not equal to 2, automatically pass fmakefile to algorithm
	else {
		algorithm("fmakefile");
	}

	return 0;
}//end of main  

