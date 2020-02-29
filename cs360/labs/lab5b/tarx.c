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

typedef struct directory {
	char* filename;
	int mode;
	long mod_time;
	struct utimbuf* ubuf;
} Dir;

int main(int argc, char *argv[]) {
	char* tarfile;
	struct stat buf;
	JRB inodes;
	JRB tmp;
	Dir* d = malloc(sizeof(Dir));
	Dllist directories = new_dllist();
	Dllist tmp1;
	FILE *f;

	int size;
	char name[258];
	long inode;
	int mode;
	long mod_time;

	int serror, nerror, ierror, merror, moderror, berror;

	if(argc != 1) {
		fprintf(stderr, "usage: tarc directory\n");
		exit(1);
	} //end of if			

	inodes = make_jrb();

	while(1) {
		serror = fread(&size, 4, 1, stdin);
		nerror = fread(&name, sizeof(char), 1, stdin);
		ierror = fread(&inode, 8, 1, stdin);

//		printf("%d %d %d", serror, nerror, ierror);
		if(serror != 1 || nerror != 1 || ierror != 1) {
			fprintf(stderr, "1nothing to read\n");
			exit(1);
		}

		tmp = jrb_find_int(inodes, inode);
		if(tmp == NULL) {
			merror = fread(&mode, 4, 1, stdin);
			moderror = fread(&mod_time, 8, 1, stdin);

			if(merror != 1 || moderror != 1) {
				fprintf(stderr, "2nothing to read\n");
				exit(1);
			}

			jrb_insert_int(inodes, inode, new_jval_s(strdup(name)));

			if(S_ISDIR(mode)) {
				mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
				dll_append(directories, new_jval_v((void*) d));	
			} else {
				f = fopen(name, "w");
				char* buffer[size]; 
				//serror = fread(&size, 4, 1, stdin);
				berror = fwrite(&buffer, 1, 1, f);
				//printf("Mode: %d\n", mode);
				//printf("Mod time %ld\n", mod_time);
				//printf("Name: %s\n", name);
				fclose(f);

				//printf("pizza");
				printf("serror: %d berror: %d\n", serror, berror);
				//berror = 1;
				if(serror != 1 || berror != 1) {
					fprintf(stderr, "3nothing to read\n");
					exit(1);
				}
			}//end of if else	 
			//printf("%s", "Terryl");
		} //end of if	

		dll_traverse(tmp1, directories) {
			//set the mode
			chmod(d->filename, mode);
			//setting mod_time
			//printf("pizza");
			//acces modification time
			d->ubuf = malloc(sizeof(struct utimbuf));
			d->ubuf->modtime = mod_time;
			//access time
			d->ubuf->actime = 0;
			utime(d->filename, d->ubuf);
			printf("Mode: %d\n", mode);
			printf("Mod time %ld\n", mod_time);
			printf("Name: %s\n", name);
		} //end of traverse	
		printf("pizza");
	} //end of while
} //end of main
