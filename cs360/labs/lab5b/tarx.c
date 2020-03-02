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
	char filename[256];
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
	char name[256];
	long inode;
	int mode;
	long mod_time;

	long filesize;

	int serror, nerror, ierror, merror, moderror, berror, ferror, cerror;

	if(argc != 1) {
		fprintf(stderr, "usage: tarc directory\n");
		exit(1);
	} //end of if			

	inodes = make_jrb();

	while(1) {
		serror = fread(&size, sizeof(int), 1, stdin);
		if(serror != 1 && feof(stdin)) {
			exit(1);
		}
		printf("Size: %d\n", &size);
		
		nerror = fread(&name, size, 1, stdin);
		printf("Name: %s\n", &name);
		ierror = fread(&inode, sizeof(long), 1, stdin);
		printf("Inode: %ld\n", &inode);

		printf("%d %d %d", serror, nerror, ierror);
		if((nerror !=  1 || ierror != 1) && feof(stdin)) {
			fprintf(stderr, "1nothing to read\n");
			exit(1);
		}

		name[size] = '\0';

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
				d = (Dir*) malloc(sizeof(Dir));
				d -> mode = mode;
				d-> mod_time = mod_time;
				strcpy(d->filename, name);
				mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
				dll_append(directories, new_jval_v((void*) d));	
			} else {
				ferror = fread(&filesize, 8, 1, stdin);
				if(ferror != 1) {
					fprintf(stderr, "nothing to print\n");
					exit(1);
				}

				char* buffer; 
				buffer = (char*)malloc(filesize);	
				berror = fread(buffer, filesize, 1, stdin);
				
				f = fopen(name, "w");
				if(f == NULL) {
					fprintf(stderr, "can't open file %s\n", name);
				}
				
				fwrite(buffer, filesize, 1, f);
				//serror = fread(&size, 4, 1, stdin);
				//printf("Mode: %d\n", mode);
				//printf("Mod time %ld\n", mod_time);
				//printf("Name: %s\n", name);
				fclose(f);

				//sets the files mode
				chmod(name, mode);
				
				/*//updating mod_time
				struct timeval time_info[2];
				time_info[0].tv_sec = time(NULL);
				time_info[0].tv_usec = 0;
				time_info[1].tv_sec = mod_time;
				time_info[1].tv_usec = 0;

				cerror = utimes(name, time_info);
				if(cerror != 0) {
					fprintf(stderr, "couldn't complete utimes\n");
					exit(1);
				}*/
				//printf("pizza");
				/*printf("serror: %d berror: %d\n", serror, berror);
				//berror = 1;
				if(serror == 0 || berror == 0) {
					fprintf(stderr, "3nothing to read\n");
					exit(1);
				}*/
			}//end of if else	 
			//printf("%s", "Terryl");
		} //end of if

		//does some linking if the inodes are already in the tree
//		else{ 
//			link(&inode, inodes);				
//		}
//
		/*dll_traverse(tmp1, directories) {
			//set the mode
			//chmod(d->filename, mode);
			//setting mod_time
			//printf("pizza");
			//acces modification time
			d->ubuf = malloc(sizeof(struct utimbuf));
			d->ubuf->modtime = mod_time;
			//access time
			d->ubuf->actime = 0;
			utime(d->filename, d->ubuf);
			printf("Mode: %d\n", mode);
			//fwrite(&d->mode, sizeof(d->mode), 1, f);
			printf("Mod time %ld\n", mod_time);
			//fwrite(&d->ubuf->modtime, sizeof(d->ubuf->modtime), 1, f);
			printf("Name: %s\n", name);
			//fwrite(name, sizeof(char), strlen(name), f);
		} //end of traverse	
		printf("pizza");*/
	} //end of while
} //end of main
