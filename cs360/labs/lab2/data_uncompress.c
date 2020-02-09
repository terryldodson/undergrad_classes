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

	//c = (int) getchar();

	while((c = getchar()) != EOF) {

		if(c != 'n' && c != 's' && c != 'i' && c != 'd') {
			fprintf(stderr, "Input error: bad type\n");
			exit(1);
		}

		//c = getchar();

		else if(c == 'd') {
			num_of_doubles = (int) getchar();
			
			if(num_of_doubles == -1) {
				fprintf(stderr, "Input error: no size\n");
				exit(1);
			}

			num_of_doubles++;
			int nread;
			nread = fread(dbuffer, sizeof(double), num_of_doubles, stdin);
			
			if(nread != num_of_doubles) {
				fprintf(stderr, "Input error: not enough doubles\n");
				exit(1);
			} //end of inner if

			for(i = 0; i < num_of_doubles; i++) {
				printf("%.10lg", dbuffer[i]);
				printf(" ");
			}//end of for loop
		} //end of if

		else if(c == 'i') {
			num_of_ints = (int) getchar();
			
			if(num_of_ints == -1) {
				 fprintf(stderr, "Input error: no size\n");
				exit(1);
			}

			num_of_ints++;
			int tmp;

			tmp = fread(ibuffer, sizeof(int), num_of_ints, stdin);
			
			if(tmp != num_of_ints) {
				fprintf(stderr, "Input error: not enough ints\n");
				exit(1);
			} //end of inner if

			for(i = 0; i< num_of_ints; i++) {
				printf("%d", ibuffer[i]);
				printf(" ");
			}
		} //end of if

		else if(c == 's') {
			wc = (int) getchar();

			if(wc == -1) {
				fprintf(stderr, "Input error: no size\n");
				exit(1);
			}

			wc += 1;

			for(i = 0; i < wc; i++) {
				ws = (int) getchar();
				ws += 1;
				
				int tmp2;
				tmp2 = fread(cbuffer, sizeof(char), ws, stdin);
				
				if(tmp2 != ws) {
					fprintf(stderr, "Input error: not enough chars\n");
					exit(1);
				}

				if(tmp2 == 0) {
					fprintf(stderr, "Input error: no string size\n");
					exit(1);
				}

				cbuffer[ws] = '\0';	
				
				printf("%s", cbuffer);
			
				if(i != wc - 1)
					printf(" ");
			} //end of outer for loop
		}//end of else if
		
		else if(c == 'n') {
			printf("\n");
		} //end of if
		
		//else if(c != 'n' && c != 's' && c != 'i' && c != 'd')
		//	printf("Input error: bad type\n");

		else if(c == EOF) {
			break;
		} //end of else if
	} //end of while

	return 0;
}//end of main
