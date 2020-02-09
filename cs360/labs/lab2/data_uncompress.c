#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	int c;
	int num_of_doubles;
	int num_of_ints;
	int wc, ws; //word count and word size
	int letter = 0;
	int i, j;
	int ibuffer[300];
	double dbuffer[300];
	char cbuffer[300];

	c = (int) getchar();

	while(c != EOF) {

		if(c != 'n' && c != 's' && c != 'i' && c != 'd')
			printf("Input error: bad type\n");

		//c = getchar();

		if(c == 'd') {
			num_of_doubles = (int) getchar();
			num_of_doubles++;
			int nread;
			nread = fread(dbuffer, sizeof(double), num_of_doubles, stdin);
			if(nread != num_of_doubles) {
				printf("Input error: not enough doubles\n");
				exit(1);
			} //end of inner if
			for(i = 0; i < num_of_doubles; i++) {
				printf("%.10lg", dbuffer[i]);
			}//end of for loop
		} //end of if

		else if(c == 'i') {
			num_of_ints = (int) getchar();
			num_of_ints++;
			int tmp;
			tmp = fread(ibuffer, sizeof(int), num_of_ints, stdin);
			if(tmp != num_of_ints) {
				printf("Input error: not enough ints\n");
				exit(1);
			} //end of inner if
			for(i = 0; i< num_of_ints; i++) {
				printf("%d ", ibuffer[i]);
			}
		} //end of if

		else if(c == 's') {
			wc = (int) getchar();
			wc += 1;

			for(i = 0; i < wc; i++) {
				ws = (int) getchar();
				ws += 1;
				
				fread(cbuffer, sizeof(char), ws, stdin);
				cbuffer[ws-1] = '\0';	
				//for(j = 0; j < ws; j++) {
				printf("%s", cbuffer);
				//} //end of inner for loop
				
				printf(" ");
			} //end of outer for loop
		}//end of if
		
		if(c == 'n') {
			printf("\n");
		} //end of else if
		
		else if(c == EOF) {
			break;
		} //end of else if
		c = (int) getchar();
	} //end of while

	return 0;
}//end of main
