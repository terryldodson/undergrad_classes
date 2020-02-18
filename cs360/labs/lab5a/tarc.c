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

int main(int argc, char *argv[]) {
	struct stat statbuf;
	char* dir;
	int i, last_slash;
	FILE *f;
	char* filename;
	int file_info;
	typedef unsigned long inode;

	if(argc > 2) {
		fprintf(stderr, "Error: Too many arguments\n");
		exit(1);
	}

	else if(argc == 2) {
		dir = argv[1];	
	}

	for(i = strlen(dir)-1; i >= 0; i--) {
		if(dir[i] == '/') {
			//printf("Found at index: %d\n", i);
			last_slash = i;
			//printf("%d\n", last_slash);
			break;
		}
	}

	//program is supposed to take a folder, not a file, and look at every file in that folder
	//put directory into dllist	
	
	filename = &dir[last_slash + 1];
	
	file_info = stat(filename, &statbuf);

	fwrite(&statbuf.st_size, 4, 1, stdout);
	printf("\n");
	fwrite(filename, sizeof(filename), 1, stdout);
	printf("\n");
	fwrite(&statbuf.st_ino, 8, 1, stdout);
	printf("\n");
	fwrite(&statbuf.st_mode, 4, 1, stdout);
	printf("\n");
	fwrite(&statbuf.st_mtime, 8, 1, stdout);
	printf("\n");
	//	fwrtie(
	
}

