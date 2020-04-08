/*Name: Terryl Dodson
 * Date: 3/30/2020
 * Description: Had to create our own shell program by using functions
 * that are related to fork, wait, exec, dup and pipe*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "fields.h"
#include "jrb.h"

void pipe(JRB processes, IS is->fields);

int main (int argc, char  *argv[]) {
	char* prompt;
	IS is;
	int i, n, fv, stat_loc, pid;
	int fd1, fd2, fd3, index;
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

		//as long as it continues to read a line
		while(get_line(is) >= 0) {
			int amp=0, pipefd[2];

			newargv = (char **) malloc(sizeof(char *)*(is->NF+1));

			for(i = 0; i < is->NF; i++) {
				newargv[i] = is->fields[i];
			}//end of for

			//fork to create new process and set equal to variable fv
			fv = fork();

			//if we find "&" at the end, then set amp to 1
			if(strcmp(is->fields[is->NF-1], "&") == 0) {
				amp = 1;
				newargv[is->NF-1] = NULL;
			} //end of if

			//check to see if the fork variable is 0
			if (fv == 0) {
				//search through all of the arguments
				for(i = 0; i < is->NF; i++) {	
					//if < is found we read from file
					if(strcmp(is->fields[i], "<") == 0) {
						newargv[i] = NULL;
						newargv[i+1] = NULL;

						//open for read only
						fd1 = open(is->fields[i+1], O_RDONLY);

						//check to see if it can open it successful
						if(fd1 < 0) {
							perror(is->fields[i+1]);
							exit(1);
						} //end of if

						//check to see if it can read from file successfully
						//if not, print out an error
						if(dup2(fd1, 0) != 0) {
							perror(is->fields[i+1]);
							exit(1);
						} //end of if
						close(fd1);
					} //end of else if

					//if > is found we write to file 
					else if(strcmp(is->fields[i], ">") == 0) {
						newargv[i] = NULL;
						newargv[i+1] = NULL;

						//open for writing, truncation and creating
						fd2 = open(is->fields[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0644);

						//check to see if it was able to open successfully
						//if not, print error then exit
						if(fd2 < 0) {
							perror(is->fields[i+1]);
							exit(1);
						} //end of if

						//check to see if it can write to file successfully
						//if not, print error and exit
						if(dup2(fd2, 1) != 1) {
							perror(is->fields[i+1]);
							exit(1);
						} //end of if
						close(fd2);
					} //end of else if

					//if >> is found we write to file
					else if(strcmp(is->fields[i], ">>") == 0) {	
						newargv[i] = NULL;
						newargv[i+1] = NULL;

						//open for writing and appending 
						fd3 = open(is->fields[i+1], O_WRONLY | O_APPEND);

						//check to see if it was able to open successfully
						//if not, print error and exit
						if(fd3 < 0) {
							perror(is->fields[i+1]);
							exit(1);
						} //end of if

						//check to see if it can write to file successfully
						//if not, print error and exit
						if(dup2(fd3, 1) != 1) {
							perror(is->fields[i+1]);
							exit(1);
						} //end of if
						close(fd3);
					}//end of else if

					//if | is found then we pipe
					else if(strcmp(is->fields[i], "|") == 0) {


						//call pipe to set up two file descriptors
						i = pipe(pipefd);

						//if it is unable to create pipe for interprocess communication
						//print error and exit
						if(i < 0) {
							perror(is->fields[i+1]);
							exit(1);
						}//end of if

						//fork to create a new process and set to fv
						fv = fork();

						//insert into jrb
						jrb_insert_int(processes, fv, new_jval_i(fv));

						//check to see if fv is equal to 0
						if(fv == 0) {

							//check to see if it was successfully opened
							//if not, we check to see if it was able to read from file
							//if not, print error and exit
							//then close file
							//if(fd1 < 0) {
							if(dup2(pipefd[1], 1) != 1) {
								perror(is->fields[i+1]);
								exit(1);
							}//end of if
							close(pipefd[1]);
							close(pipefd[0]);
							execlp(newargv, newargv[0]);
							exit(1);
							//}//end of if

							//check to see if it was successfully opened
							//if not, check to see if it was able to write to file
							//if not, print error and exit
							//then close file
							//if(fd2 < 0) {
							if(dup2(pipefd[0], 0) != 0) {
								perror(is->fields[i+1]);
								exit(1);
							}//end of if
							close(pipefd[1]);
							close(pipefd[0]);
							execlp(newargv, newargv[0]);
							exit(1);
							//}//end of if

							//check to see if it was successfully opened
							//if not, check to see if it was able to write to file
							//if not, print error and exit
							//then close file
							if(fd3 < 0) {
								if(dup2(fd3, 1) != 1) {
									perror(is->fields[i+1]);
									exit(1);
								} //end of if
								close(fd3);
							} //end of if
						}//end of else if
					}//end of for

					newargv[is->NF] = NULL;

					execvp(newargv[0], newargv);

					perror(newargv[0]);
					exit(1);
				} else {

					//insert value returned from fork into jrb tree
					jrb_insert_int(processes, fv, new_jval_i(fv));

					if(!amp) { 
						/*while loop to look through jrb tree until I find process I want which is fv*/
						/*keep calling wait until the fork (fv) is equal to what wait returns*/
						/*once I find one equal just break*/
						while(1) {		

							pid = wait(&stat_loc);

							//once I find the pid value, search for it in the tree
							//set to pid_num 
							JRB pid_num;
							pid_num = jrb_find_int(processes, pid);

							//if I can't find pid_num in tree, don't do anything
							if(pid_num == NULL) {

							}//ends of if

							//if I do find pid_num, delete node
							jrb_delete_node(pid_num);

							//if pid is equal to fv then break
							if(pid == fv) {
								break;
							}//end of inner if
						} //end of while
					} //end of outer if
				} //end of else

				//free newargv
				free(newargv);
			} //end of while
		} //end of if

		/*traverse jrb tree and call wait*/
		jrb_traverse(p, processes) {
			wait(&stat_loc);
		} //end of jrb_traverse 

		//free jrb tree
		jrb_free_tree(processes);
	} //end of main

	/*void pipe(JRB process, IS is->fields) {

	//call pipe to set up two file descriptors
	i = pipe(pipefd);

	//if it is unable to create pipe for interprocess communication
	//print error and exit
	if(i < 0) {
	perror(is->fields[i+1]);
	exit(1);
	}//end of if

	//fork to create a new process and set to fv
	fv = fork();

	//insert into jrb
	jrb_insert_int(processes, fv, new_jval_i(fv));

	//check to see if fv is equal to 0
	if(fv == 0) {

	//check to see if it was successfully opened
	//if not, we check to see if it was able to read from file
	//if not, print error and exit
	//then close file
	//if(fd1 < 0) {
	if(dup2(pipefd[1], 1) != 1) {
	perror(is->fields[i+1]);
	exit(1);
	}//end of if
	close(pipefd[1]);
	close(pipefd[0]);
	execlp(newargv, newargv[0]);
	exit(1);
	//}//end of if

	//check to see if it was successfully opened
	//if not, check to see if it was able to write to file
	//if not, print error and exit
	//then close file
	//if(fd2 < 0) {
	if(dup2(pipefd[0], 0) != 0) {
	perror(is->fields[i+1]);
	exit(1);
	}//end of if
	close(pipefd[1]);
	close(pipefd[0]);
	execlp(newargv, newargv[0]);
	exit(1);
	//}//end of if

	//check to see if it was successfully opened
	//if not, check to see if it was able to write to file
	//if not, print error and exit
	//then close file
	if(fd3 < 0) {
	if(dup2(fd3, 1) != 1) {
	perror(is->fields[i+1]);
	exit(1);
	} //end of if
	close(fd3);
	} //end of if
	}//end of outer if*/
	//}
