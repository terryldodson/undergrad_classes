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
	char* exe;
	char oFile;
	int exist = 0;
	int eexists = 0;
	int oexists = 0;
	int sys;
	int cmp = 0; //echk=0; //recompile
	//	char* gccString[100];
	int ctime=0, htime, ltime, etime, ftime, otime=0;
	int num, num1, num2, num3, i=0;
	//char* file = "fmakefile";;
	IS is;

	//if(argc == 1) {
	//	is = new_inputstruct(file);
	//	fprintf(stderr, "File doesn't exist\n");
	//	exit(1);
	//	} else{
	//		is = new_inputstruct(argv[1]);
	//	} //end of if else

	is = new_inputstruct(a);

	while(get_line(is) >= 0) {

		//checks for blanks
		if(is->NF == 0) {
			continue;
		} //end of if

		if(strcmp(is->fields[0], "C")) {
			for(i = 1; i < is->NF; i++) {
				dll_append(cList, new_jval_s(strdup(is->fields[i])));	
			}
		} //end of if

		else if(strcmp(is->fields[0], "H")) {
			for(i = 1; i < is->NF; i++) {
				dll_append(hList, new_jval_s(strdup(is->fields[i])));
			}
		} //end of else if

		else if(strcmp(is->fields[0], "L")) {
			for(i = 1; i < is->NF; i++) {
				dll_append(lList, new_jval_s(strdup(is->fields[i])));
			}
		} //end of else if

		else if(strcmp(is->fields[0], "E")) {
			for(i = 1; i < is->NF; i++) {
				dll_append(eList, new_jval_s(strdup(is->fields[i])));
				//	echk++;
			}

			//exe = is->fields[1];
			//printf("exe name: %s\n", exe);
		} //end of else if

		else if(strcmp(is->fields[0], "F")) {
			for(i = 1; i < is->NF; i++) {
				dll_append(fList, new_jval_s(strdup(is->fields[i])));
			}
		} //end of else if

		else {
			fprintf(stderr, "Error: Unprocessed line. First character of line must be C, H, E, F, or L\n");
			exit(1);
		}
		/*else if(!(strcmp(is->fields[0], "E"))) {
		  fprintf(stderr, "No E line\n");
		  exit(1);
		  } //end of else if*/
	} //end of while

	if(!(strcmp(is->fields[0], "E"))) {
		fprintf(stderr, "Error: No executable name given\n");
		exit(1);
	} //end of else if*/


	//	printf("cList: %s\n", cList->val.s);
	dll_traverse(tmp, cList) {
		//take the .c off of the file and add .o at the end of it
		num1 = stat(tmp->val.s, &statbuf);
		if(num1 < 0) {
			fprintf(stderr, " File doesn't exist\n");
			//			exit(1);
		} //end of if

		else {
			char gccString[100] = "gcc -c ";
			char oFile[sizeof(tmp->val.s)];	

			ctime = statbuf.st_mtime;

			strcpy(oFile, tmp->val.s);
			//printf("oFile: %s\n ", oFile);


			oFile[strlen(oFile)-2] = '\0';
			strcat(oFile, ".o");

			oexists = stat(oFile, &obuf);

			otime = obuf.st_mtime;

			//if(stat(oFile, &statbuf) == 0) {
			//	int length = strlen(oFile);

			//		oFile[length - 1] = 'c';
			//printf("%s\n", oFile);
			//	}

			if (oexists < 0 || otime < ctime || otime < htime) {
			//	printf("Remake .o file\n");

				dll_traverse(f, fList) {
					strcat(gccString, f->val.s);
					strcat(gccString, " ");
				}

				strcat(gccString, tmp->val.s);
				printf("%s\n", gccString);

				sys = system(gccString);

				if(sys < 0) {
					fprintf(stderr, "System Fail\n");
					exit(1);
				}

				cmp++;
				//remake file
				//	char gccString[100] = "gcc -c ";
				//strcpy(gccString, "gcc -c ");
				//	printf(oFile);
				//printf("\n");
				//strcat(gccString, oFile);
				//printf(gccString);
				//printf("\n");
			}
			//printf(gccString);
			//printf("\n");
		}

		char oFile1[sizeof(tmp->val.s)];

		strcpy(oFile1, tmp->val.s);
		oFile1[strlen(oFile1)-2] = '\0';
		strcat(oFile1, ".o");
		oexists = stat(oFile1, &obuf);
		if(obuf.st_mtime > otime)
			otime = obuf.st_mtime;

	} //end of cList traverse

	char gccString1[100] = "gcc -o ";
	dll_traverse(tmp1, eList) {
		eexists = stat(tmp->val.s, &statbuf);
		if(eexists < 0 || cmp > 0 || statbuf.st_mtime < otime) {
			strcat(gccString1, tmp->val.s);
			strcat(gccString1, " ");

			dll_traverse(f, fList) {
				strcat(gccString1, f->val.s);
				strcat(gccString1, " ");
			}

			dll_traverse(tmp1, cList) {
				char oFile2[sizeof(tmp1->val.s)];
				strcpy(oFile2, tmp->val.s);
				oFile2[strlen(oFile2)-2] = '\0';
				strcat(oFile2, ".o");
				strcat(gccString1, oFile2);
				strcat(gccString1, " ");
				//oexists = stat(oFile1, &obuf);
				//if(o.buf.st_mtime > otime)
				//	otime = o.buf.st_mtime;
			}

			dll_traverse(tmp2, lList) {
				strcat(gccString1, tmp2->val.s);
				if(tmp2 != (lList-1))
					strcat(gccString1, " ");
			}

			printf("%s\n", gccString1);
			sys = system(gccString1);

			if(sys < 0) {
				fprintf(stderr, "System Fail\n");
				exit(1);
			}
			//num2 = stat(tmp2->val.s, &statbuf);
			//set time
			//        ltime = statbuf.st_mtime;
			//                //printf("%s\n", tmp2->val.s);
			//                    } //end of lList traverse
			//

		}
	}//end of eList traverse

	dll_traverse(tmp3, hList) {		    
		exist = stat(tmp3->val.s, &hbuf);
		if(exist < 0) {
			fprintf(stderr, "Error: File '%s' does not exist\n", tmp->val.s);
		//exit(1);
		} //end of if
		else {
  			if(htime < hbuf.st_mtime) {
  				htime = hbuf.st_mtime;
  			}
		}//end of else
	} //end of hList traverse
} //end of algorithm function
 // else {
 // if(htime < hbuf.st_mtime) {
 // htime = hbuf.st_mtime;
 // }
 // } //end of else
//printf("%s\n", tmp1->val.s);
//} //end of hList traverse

/*dll_traverse(tmp2, lList) {
num2 = stat(tmp2->val.s, &statbuf);
//set time
ltime = statbuf.st_mtime;
//printf("%s\n", tmp2->val.s);
} //end of lList traverse

dll_traverse(tmp3, fList) {
num3 = stat(tmp3->val.s, &statbuf);
//set time
ftime = statbuf.st_mtime;
//printf("%s\n", tmp3->val.s);
} //end of fList traverse
}*/

int main(int argc, char *argv[]) {
	FILE *f;

	if(argc > 2){
		fprintf(stderr, "Error: Too many arguments\n");
		exit(1);
	}

	if(argv[1]){
		if((f = fopen(argv[1], "r")) != NULL){
			algorithm(argv[1]);
		}
		else{
			fprintf(stderr, "Error: file does not exist\n");
			exit(1);
		}
	}
	else if(argv[1] == NULL){
		algorithm("fmakefile.fm");
	}

	return 0;
}//end of main  


