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

	c = getchar();

	while(c != EOF) {

		if(c != 'n' && c != 's' && c != 'i' && c != 'd')
			printf("Input error: bad type\n");

		c = getchar();

		if(c == 'd') {
			num_of_doubles = getchar();
			num_of_doubles++;
			double dbuffer[300];
			int nread;
			nread = fread(&dbuffer, sizeof(double), num_of_doubles, stdin);
			if(nread != num_of_doubles) {
				printf("Input error: not enough doubles\n");
				exit(1);
			} //end of inner if
			printf("%.10lg", *dbuffer);
		} //end of if

		if(c == 'i') {
			num_of_ints  = getchar();
			num_of_ints++;
			int ibuffer[300];
			int tmp;
			tmp = fread(&ibuffer, sizeof(int), num_of_ints, stdin);
			if(tmp != num_of_ints) {
				printf("Input error: not enough ints\n");
				exit(1);
			} //end of inner if
			printf("%d", *ibuffer);
		} //end of if

		if(c == 's') {
			wc = getchar();
			wc += 1;

			for(i = 0; i < wc; i++) {
				ws = getchar();
				ws += 1;
				
				for(j = 0; j < ws; j++) {
					letter = getchar();
					if(isprint(letter))
						printf("%c", letter);
				} //end of inner for loop
				
				//if(i != word_count-1)
					printf(" ");
			} //end of outer for loop
		}//end of if
		
		else if(c == 'n') {
			printf("\n");
		} //end of else if
		
		else if(c == EOF) {
			break;
		} //end of else if
	} //end of while

	return 0;
}//end of main
