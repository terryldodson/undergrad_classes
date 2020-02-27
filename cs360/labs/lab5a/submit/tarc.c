/*Name: Terryl Dodson
 * Date: 2/25/20
 * Description: Goal is to write our own tarc program. Where we create a tar file
 * from provided files or directories*/

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
int long_comp(Jval v1, Jval v2);

int main(int argc, char *argv[]) {
	struct stat statbuf;
	char* dir;
	int i, last_slash = 0;
	DIR *directory;
	int path_info;
	JRB inode;
	char* short_path;
	int length;

	//checks for number of arguments
	if(argc != 2) {
		fprintf(stderr, "usage: tarc directory\n");
		exit(1);
	} //end of if
		
	if(argc == 2) {
		dir = argv[1];	
	} //end of else if

	//creates inode jrb
	inode = make_jrb();

	//looks for last slash in path
	for(i = strlen(dir)-1; i >= 0; i--) {
		if(dir[i] == '/') {
			last_slash = i+1;
			break;
		} //end of if
	}//end of for 

	//short_path contains the word after the last slash
	short_path = &dir[last_slash];

	path_info = lstat(dir, &statbuf);

	//checks to see if the path exists
	//If it does, it calls traverse_directories function
	//If not, it prints error and exits
	if(path_info < 0) {
		fprintf(stderr, "Path doesn't exist");
		exit(1);
	} 
	
	//prints out name size, name, inode, mode, and mode time
	length = (int) strlen(short_path);
	fwrite(&length, sizeof(int), 1, stdout);
	fwrite(short_path, sizeof(char), length, stdout);
	fwrite(&statbuf.st_ino, sizeof(statbuf.st_ino), 1, stdout);
	fwrite(&statbuf.st_mode, sizeof(statbuf.st_mode), 1, stdout);
	fwrite(&statbuf.st_mtime, sizeof(statbuf.st_mtime), 1, stdout);
	
	traverse_directories(dir, inode, last_slash);

	jrb_free_tree(inode);

	return 0;
} //end of main 

void traverse_directories(char* dir, JRB inode, int slash_index) {
	int direxists = 0;
	Dllist directory = new_dllist();
	Dllist tmp; // = new_dllist();
	DIR *d;
	struct dirent *de;
	char *s =  malloc(sizeof(char)*(strlen(dir)+258));
	struct stat buf;
	int exists = 0;
	FILE *f;
	int i, last_slash;
	char* short_path = malloc(sizeof(char)*(strlen(dir)+258));

	//opens directory
	d = opendir(dir);

	if(d == NULL) {
		fprintf(stderr, "unable to open directory");
		exit(1);
	} //end of if

	//opens each directory until it reaches a NULL
	for (de = readdir(d); de != NULL; de = readdir(d)) {
		//de->d_name is directory name
		sprintf(s, "%s/%s", dir, de->d_name);

		//checks to see if the s exists
		exists = lstat(s, &buf);
		if (exists < 0) {
			fprintf(stderr, "Couldn't stat %s\n", s);
			exit(1);
		} //end of if

		//ignores . and ..
		else if (strcmp(de->d_name, ".") == 0)
			continue;

		else if(strcmp(de->d_name, "..") == 0)
			continue;

		short_path = s + slash_index;
		int length = (int) strlen(short_path);
		fwrite(&length, sizeof(int), 1, stdout);
		fwrite(short_path, sizeof(char), length, stdout);
		fwrite(&buf.st_ino, sizeof(buf.st_ino), 1, stdout);

		//checks for soft links
		if(S_ISLNK(buf.st_mode)) continue;

		//checks if inode is in jrb tree
		else if (jrb_find_gen(inode, new_jval_l(buf.st_ino), long_comp) == NULL) {    
			//if not in tree, add to tree and write mode and modtime
			jrb_insert_gen(inode, new_jval_l(buf.st_ino), new_jval_i(0), long_comp);
			fwrite(&buf.st_mode, sizeof(buf.st_mode), 1, stdout);
			fwrite(&buf.st_mtime, sizeof(buf.st_mtime), 1, stdout);
			
			//checks to see if its a directory
			if(S_ISDIR(buf.st_mode)){ 
				dll_append(directory, new_jval_s(strdup(s)));
			} else { 
				
				//open files and print its contents
				fwrite(&buf.st_size, sizeof(buf.st_size), 1, stdout);
				f = fopen(s, "r");
				char buffer[buf.st_size];
				fread(buffer, buf.st_size, 1, f);
				fwrite(buffer, sizeof(char), buf.st_size, stdout);
				fclose(f);
			}//end of if and else
		} //end of else if
	}//end of for

	//closes directory
	closedir(d);

	//traverses through dllist and recursively call the function
	dll_traverse(tmp, directory) {
		traverse_directories(tmp->val.s, inode, slash_index);
		free(tmp->val.s);
	} //end of dll_traverse

	//free memory
	free_dllist(directory);
	free(s);
	//free(short_path);
}//end of traverse function

//from the lecture
int long_comp(Jval v1, Jval v2){
	if (v1.l < v2.l) 
		return -1;
	if (v1.l > v2.l) 
		return 1;
	
	return 0;
}
