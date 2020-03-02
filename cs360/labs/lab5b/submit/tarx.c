/*Name: Terryl Dodson
 *  * Date: 3/2/20
 *   * Description: Goal is to write our own tarx program. Where we extract a tar file
 *    * back to its files or directories*/

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
#include <dirent.h>
#include <utime.h>
#include <time.h>

//create struct
typedef struct directory {
	char* filename;
	int mode;
	long mod_time;
	struct utimbuf* ubuf;
} Dir;

int main(int argc, char *argv[]) {
	//initializing variables
	char* tarfile;
	struct stat buf;
	JRB inodes, tmp, check;
	Dir* d;
	Dir *traverse;
	Dllist directories = new_dllist();
	Dllist tmp1;
	FILE *f;

	int size;
	char name[256];
	long inode;
	int mode;
	long mod_time;

	long filesize;

	int serror, nerror, ierror, merror, moderror, berror, ferror, cerror;

	//checking for arguments
	if(argc != 1) {
		fprintf(stderr, "usage: tarc directory\n");
		exit(1);
	} //end of if			

	//creates inode tree
	inodes = make_jrb();

	while(1) {
		d = malloc(sizeof(Dir));
		
		//read in size and if nothing is read then print out error
		serror = fread(&size, sizeof(int), 1, stdin);
		
		//print error if size is negative
		if(size < 0) {
			fprintf(stderr, "size is negative");
			exit(1);
		}//end of if

		//if serror isn't read in break
		if(serror != 1 && feof(stdin)) {
			break;
		}//end of if

		//read in name and inode and print out error if nothing is read
		nerror = fread(&name, size, 1, stdin);
		ierror = fread(&inode, sizeof(long), 1, stdin);

		if((nerror !=  1 || ierror != 1) && feof(stdin)) {
			fprintf(stderr, "1nothing to read\n");
			exit(1);
		}//end of if

		//sets null terminator
		name[size] = '\0';

		//check to see if inode is in tree, if not run if statement
		tmp = jrb_find_int(inodes, inode);
		if(tmp == NULL) {
			//read in mode and mod_time and print error if nothing is read
			merror = fread(&mode, 4, 1, stdin);
			moderror = fread(&mod_time, 8, 1, stdin);

			if(merror != 1 || moderror != 1) {
				fprintf(stderr, "2nothing to read\n");
				exit(1);
			}//end of if

			//insert inode into tree
			jrb_insert_int(inodes, inode, new_jval_s(strdup(name)));

			//checks if file is directory
			if(S_ISDIR(mode)) {
				//sets directory struct variables, create directory, and append to list
				//if its not a directory print error then exit
				d -> mode = mode;
				d-> mod_time = mod_time;
				d->ubuf = malloc(sizeof(struct utimbuf));
				d->ubuf->modtime = d->mod_time;
				d->filename = strdup(name);
				mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
				dll_append(directories, new_jval_v((void*) d));	
			} else {
				ferror = fread(&filesize, 8, 1, stdin);
				if(ferror != 1) {
					fprintf(stderr, "nothing to print\n");
					exit(1);
				}//end of if

				//create buffer and fread and print error and exit if buffer is empty
				char* buffer; 
				buffer = (char*)malloc(filesize);	
				berror = fread(buffer, filesize, 1, stdin);

				if(buffer == 0) {
					fprintf(stderr, "bad");
					exit(1);
				}//end of if

				//opens file, print error if it couldn't open
				f = fopen(name, "w");
				if(f == NULL) {
					fprintf(stderr, "can't open file %s\n", name);
					exit(1);
				}//end of if
				
				//check fwrite and print error if it couldn't write
				int fcheck;
				fcheck = fwrite(buffer, filesize, 1, f);
				if(fcheck == 0) {
					fprintf(stderr, "bad");
					exit(1);
				}//end of if

				//close file
				fclose(f);

				//allocate memory for ubuf and set modtime
				d->ubuf = malloc(sizeof(struct utimbuf));
				d->ubuf->modtime = mod_time;

				//free memory
				free(buffer);

				//sets the files mode
				chmod(name, mode);

				//set access time and modification time
				utime(name, d->ubuf);

				//check size and buffer
				if(serror == 0 || berror == 0) {
					fprintf(stderr, "3nothing to read\n");
					exit(1);
				}//end of if
			}//end of if else	 
		} //end of if

		//does some linking if the inodes are already in the tree
		else{ 
			check = jrb_find_int(inodes, inode); 	
			link(check->val.s, name);				
		}//end of else
		
		//free memory
		free(d->ubuf);
		free(d);
	} //end of while

	//traverse through directories
	dll_traverse(tmp1, directories) {
		//create traverse variable
		traverse = (Dir*) tmp1->val.v;

		//sets mode for each directory
		chmod(traverse->filename, traverse->mode);
		
		//access time amd modification time for each directory
		utime(traverse->filename, traverse->ubuf);
	} //end of traverse	
} //end of main
