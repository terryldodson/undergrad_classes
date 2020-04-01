/*Name: Terryl Dodson
 * Date: 3/30/2020
 * Description: Had to create our own shell program by using functions
 * that are related to fork, wait, exec, dup and pipe*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "fields.h"
#include "jrb.h"

int main (int argc, char  *argv[]) {
	char* prompt;
	IS is;
	int i, n, fv, stat_loc, pid;
	JRB processes;
	JRB p;
	char **newargv;

	//checks for arguments
	if(argc != 2) {
		prompt = "jsh: ";
	} //end of if

	else if(argc == 2) {
		prompt = "";
	} //end of else if

	//sets inputstruct to NULL since we're reading in from standard input
	//creates jrb tree for fork values
	is = new_inputstruct(NULL);
	processes = make_jrb();

	//if the prompt doesn't equal a blank
	if(strcmp(prompt, " ") != 0) { 

//		printf("%s",prompt); 

		//as long as it continues to read a line
		while(get_line(is) >= 0) {
			int amp=0;

			newargv = (char **) malloc(sizeof(char *)*(is->NF+1));

			for(i = 0; i < is->NF; i++) {
				newargv[i] = is->fields[i];
			} //end of for

			newargv[is->NF] = NULL;

			if(strcmp(newargv[is->NF-1], "&") == 0) {
				amp = 1;
			} //end of if

			//fork and set equal to variable fv
			fv = fork();

			//if fv is set to 0 we call execvp and exit
			//when the & is not at the end of string we wait
			if (fv == 0) {
				if(strcmp(newargv[is->NF-1], "&") == 0) {
					newargv[is->NF-1] = NULL;
				} //end of if

				execvp(newargv[0], newargv);

				if(execvp(newargv[0], newargv) == -1) {
					perror(newargv[0]);
					exit(1);
				} //end of if
			} else {

				//insert value returned from fork into jrb tree
				jrb_insert_int(processes, fv, new_jval_i(fv));

				if(!amp) { 
					/*while loop to look through jrb tree until I find process I want which is fv*/
					/*keep calling wait until the fork (fv) is equal to what wait returns*/
					/*once I find one equal just break*/
					while(1) {		

						pid = wait(&stat_loc);

						JRB pid_num;
						pid_num = jrb_find_int(processes, pid);
						
						if(pid_num == NULL) {
						
						}

						jrb_delete_node(pid_num);

						if(pid == fv) {
							break;
						}//end of inner if
					} //end of while
				} //end of outer if
			} //end of else

			free(newargv);
//			printf("%s",prompt); 	
		} //end of while
	} //end of if

	/*traverse jrb tree and call wait*/
	jrb_traverse(p, processes) {
		wait(&stat_loc);
	} //end of jrb_traverse 

	//free jrb tree
	jrb_free_tree(processes);
} //end of main
