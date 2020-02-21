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

void traverse_directories(char *dir, JRB inode, int slash_index);

int main(int argc, char *argv[]) {
	struct stat statbuf;
	char* dir;
	int i, last_slash;
	DIR *directory;
	int path_info;
	JRB inode;
	char* short_path;
	int length;

	//checks for number of arguments
	if(argc > 2) {
		fprintf(stderr, "Error: Too many arguments\n");
		exit(1);
	}

	else if(argc == 2) {
		dir = argv[1];	
	}

	//creates inode jrb
	inode = make_jrb();


	for(i = strlen(dir)-1; i >= 0; i--) {
		if(dir[i] == '/') {
			//	printf("Found at index: %d\n", i);
			last_slash = i+1;
			//	printf("%d\n", last_slash);
			//	break;
		}
	}

	//program is supposed to take a folder, not a file, and look at every file in that folder
	//put directory into dllist	

	//short_path contains the word after the last slash
	short_path = &dir[last_slash]; // + 1];

	//path_info = stat(argv[1], &statbuf);
	path_info = stat(dir, &statbuf);

	//use short_path when printing
	length = strlen(short_path);
	fwrite(&length, 4, 1, stdout);
	//fwrite(short_path, strlen(short_path), 1, stdout);
	printf("%s", short_path);
	fwrite(&statbuf.st_ino, 8, 1, stdout);
	fwrite(&statbuf.st_mode, 4, 1, stdout);
	fwrite(&statbuf.st_mtime, 8, 1, stdout);

	//use regular path when calling function
	if(path_info < 0) {
		fprintf(stderr, "Path doesn't exist");
		exit(1);
	} else {
		traverse_directories(dir, inode, last_slash);
	}

} //end of main 

void traverse_directories(char* dir, JRB inode, int slash_index) {
	int direxists = 0;
	Dllist directory = new_dllist();
	Dllist tmp = new_dllist();
	DIR *d;
	struct dirent *de;
	char *s;
	struct stat buf;
	int exists = 0;
	FILE *f;
	int i, last_slash;
	char* short_path;

	d = opendir(dir);

	if(d == NULL) {
		fprintf(stderr, "no directory");
		exit(1);
	}

	for (de = readdir(d); de != NULL; de = readdir(d)) {
		//de->d_name is directory name
		if (strcmp(de->d_name, ".") != 0 &&  strcmp(de->d_name, "..") != 0) {
			/* Look for fn/de->d_name */
			sprintf(s, "%s/%s", dir, de->d_name);

			/*for(i = strlen(dir)-1; i >= 0; i--) {
				if(dir[i] == '/') {
					//printf("Found at index: %d\n", i);
					last_slash = i+1;
					//printf("%d\n", last_slash);
					//break;
				}
			}*/

			short_path = &dir[slash_index];
			int length = strlen(short_path);

			stat(dir, &buf);
			fwrite(&length, 4, 1, stdout);
			//fwrite(short_path, strlen(short_path), 1, stdout);
			printf("%s", short_path);
			fwrite(&buf.st_ino, 8, 1, stdout);

			exists = stat(s, &buf);
			if (exists < 0) {
				fprintf(stderr, "Couldn't stat %s\n", s);
				exit(1);
			} else {
				if (jrb_find_int(inode, buf.st_ino) == NULL) {
					fwrite(&buf.st_mode, 4, 1, stdout);
					fwrite(&buf.st_mtime, 8, 1, stdout);
					jrb_insert_int(inode, buf.st_ino, new_jval_v(NULL));
				}
			}

			//if its a directory, append to directory dllist
			if (S_ISDIR(buf.st_mode)) {
				dll_append(directory, new_jval_s(strdup(dir)));	
			}

			//if its a file, open file and write contents
			else if(S_ISREG(buf.st_mode) == 1) {
				f = fopen(dir, "r");			
				fwrite(&buf.st_size, 4, 1, stdout);
				fwrite(f, buf.st_size, 1, stdout);
			}
		}
		//free(s);
	}

	closedir(d);

	traverse_directories(dir, inode, slash_index);
}

/*direxists = stat(dir, &statbuf);

  if(direxists < 0) {
  fprintf(stderr, "Directory doesn't exist");
  exit(1);
  } else {
  d = opendir(dir);

  traverse(tmp, directory) {

//statbuf.st_size refers to file size
fwrite(&statbuf.st_size, 4, 1, stdout);
fwrite(&strlen(dir), sizeof(dir), 1, stdout);
fwrite(&statbuf.st_ino, 8, 1, stdout);

fwrite(&statbuf.st_mode, 4, 1, stdout);
fwrite(&statbuf.st_mtime, 8, 1, stdout);

path_info = stat(dir, &statbuf);

if(path_info == 1)
traverse_directories(dir);
else {
fprintf(stderr, "Path doesn't exist\n");
exit(1);
} //end of else
} //end of traverse
} //end of else*/
//}//end of traverse_directories function

