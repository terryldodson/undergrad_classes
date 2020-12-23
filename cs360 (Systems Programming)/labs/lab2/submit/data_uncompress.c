/* Name: Terryl Dodson
 * Date: 2/9/20
 * Summary: worked on extracting compressed data and printing it out
 * according to the type: int, double, or string
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	//initalizing variables
	int c;
	int num_of_doubles;
	int num_of_ints;
	int wc, ws; //word count and word size
	int letter = 0;
	int i, j;
	int line_space = 1;
	int ibuffer[300];
	double dbuffer[300];
	char cbuffer[300];

	//while loop runs until it reaches the end of file
	while((c = getchar()) != EOF) {

		//prints out error if input isnt n, s, i or d
		if(c != 'n' && c != 's' && c != 'i' && c != 'd') {
			fprintf(stderr, "Input error: bad type\n");
			exit(1);
		}//end of if

		//runs this if statment if char is equal to d
		else if(c == 'd') {
			num_of_doubles = (int) getchar();

			//if getchar didn't receive anything print out error message
			if(num_of_doubles == -1) {
				fprintf(stderr, "Input error: no size\n");
				exit(1);
			}//end of if

			//read in doubles to dbuffer and set to nread
			num_of_doubles++;
			int nread;
			nread = fread(dbuffer, sizeof(double), num_of_doubles, stdin);

			//if nread doesn't equal the number of doubles then print this error
			if(nread != num_of_doubles) {
				fprintf(stderr, "Input error: not enough doubles\n");
				exit(1);
			} //end of inner if

			//traverses through the dbuffer and prints each one out. Only prints a space if its not the first one
			for(i = 0; i < nread; i++) {
				if(line_space == 0)
					printf(" ");
				else{line_space = 0;}
				printf("%.10lg", dbuffer[i]);
			}//end of for loop
		} //end of if

		//calls this if char is equal to a i
		else if(c == 'i') {
			num_of_ints = (int) getchar();

			//if getchar didn't receive anything print out error message
			if(num_of_ints == -1) {
				fprintf(stderr, "Input error: no size\n");
				exit(1);
			}//end of if

			num_of_ints++;
			int tmp;

			//read in ints to ibuffer and set to tmp
			tmp = fread(ibuffer, sizeof(int), num_of_ints, stdin);

			//if tmp doesn't equal the number of ints then print this error
			if(tmp != num_of_ints) {
				fprintf(stderr, "Input error: not enough ints\n");
				exit(1);
			} //end of inner if

			//traverses through the ibuffer and prints each one out
			for(i = 0; i < tmp; i++) {
				//printf(" ");
				if(line_space == 0)
					printf(" ");
				else{line_space = 0;}
					printf("%d", ibuffer[i]);

			}//end of for
		} //end of if

		//calls this if char is equal to a s
		else if(c == 's') {
			//reads in number of words
			wc = (int) getchar();

			//if getchar didn't receive anything print out error message
			if(wc == -1) {
				fprintf(stderr, "Input error: no size\n");
				exit(1);
			}//end of if

			wc += 1;

			//runs this loop until it reaches the number of words
			for(i = 0; i < wc; i++) {
				//word length
				ws = (int) getchar();
				ws += 1;

				//reads in chars and sets them to cbuffer
				int tmp2;
				tmp2 = fread(cbuffer, sizeof(char), ws, stdin);

				//if it didn't read the right number of chars print this error message
				if(tmp2 != ws) {
					fprintf(stderr, "Input error: not enough chars\n");
					exit(1);
				}//end of if

				//if it didn't read anything print this error message
				if(tmp2 == 0) {
					fprintf(stderr, "Input error: no string size\n");
					exit(1);
				}//end of if

				//set the null character
				cbuffer[ws] = '\0';	

				//print a space after each word if it isnt the first word
				if(line_space == 0)
					printf(" ");
				else{line_space = 0;}	
					//print the buffer
					printf("%s", cbuffer);

			} //end of outer for loop
		}//end of else if

		//if the character is an n just print a new line
		else if(c == 'n') {
			printf("\n");
			line_space = 1;
		} //end of if

		//if c reaches the end of file, break 
		else if(c == EOF) {
			break;
		} //end of else if
	} //end of while

	return 0;
}//end of main
