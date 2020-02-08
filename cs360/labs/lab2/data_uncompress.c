#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	int c;
	int num_doubles;
	int num_ints;
	int word_count, word_size;
	int letter = 0;
	int i, j;
	//int counter = 0;

	c= getchar();

	while(c != EOF) {

		if(c != 'n' && c != 's' && c != 'i' && c != 'd')
			printf("Input error: bad type\n");

		c = getchar();

		if(c == 'd') {
			num_doubles = getchar();
			num_doubles++;
			double dbuffer[300];
			int nread;
			nread = fread(&dbuffer, sizeof(double), num_doubles, stdin);
			if(nread != num_doubles) {
				printf("Input error: not enough doubles\n");
				exit(1);
			}
			printf("%.10lg", *dbuffer);
		}

		if(c == 'i') {
			num_ints  = getchar();
			num_ints++;
			int ibuffer[300];
			int tmp;
			tmp = fread(&ibuffer, sizeof(int), num_ints, stdin);
			if(tmp != num_ints) {
				printf("Input error: not enough ints\n");
				exit(1);
			}
			printf("%d", *ibuffer);
		}

		if(c == 's') {
			word_count = getchar();
			word_count += 1;

			for(i = 0; i < word_count; i++) {
				word_size = getchar();
				word_size += 1;
				
				for(j = 0; j < word_size; j++) {
					letter = getchar();
					if(isprint(letter))
						printf("%c", letter);
				}
				
				//if(i != word_count-1)
					printf(" ");
			}
		}
		
		else if(c == 'n') {
			printf("\n");
		}
		
		else if(c == EOF)
			break;
		
/*		else if(c != 'n' && c != 'i' && c != 's' && c != 'd') {
			printf("Input error: bad type\n");
			exit(1);
		}*/
		
		//counter++;
	}

	return 0;
}
		/*	int c, i, nread, j, letter;
			unsigned char n, size;
			char cbuffer[300];
			int ibuffer[300];
			double dbuffer[300];

			c = getchar();

			while(c != EOF) {

			if(c != 'n' && c != 's' && c != 'i' && c != 'd') 
			fprintf(stderr, "Input error: bad type\n");

			switch(c) {
		//	printf(c);
		case 'n':
		printf("\n");
		break;
		case 's':
		n = getchar();
		n++;

		for(i=0; i <n; i++) {
		size = getchar();
		size++;

		for(j = 0; j < size; j++) {
		letter = getchar();
		if(isprint(letter))
		printf("%c", letter);
		}
		}

		if(i != n-1)
		printf(" ");

		//	size = getchar();
		//	fread(cbuffer, size + sizeof(char), n+1, stdin);

		break;
		case 'i':
		n = getchar();
		n++;
		fread(&ibuffer, sizeof(int), n, stdin);
		printf("%d ", *ibuffer);
		//printf("dogs");
		break;
		case 'd':
		n = getchar();
		n++;
		fread(&dbuffer, sizeof(double), n, stdin);
		printf("%.10lg ", *dbuffer);
		//printf("jellybean");
		break;
		}

		c = getchar();

		if(c == EOF)
		break;
		} */
//	}
