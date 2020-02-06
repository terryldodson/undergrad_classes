#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	int c, i;
	unsigned char n, size;
	char cbuffer[300];
	int ibuffer[300];
	double dbuffer[300];

	c = getchar();

	while(c != EOF) {

		if(c != 'n' || c != 's' || c != 'i' || c != 'd')
			fprintf(stderr, "Input error: bad type\n");

		//if(c == 'n') //character is an n
		//	printf("\n");

		switch(c) {
			case 'n':
				printf("\n");
				break;
			case 's':
				n = getchar();			
				fread(cbuffer, n+1, strlen(c) + 1, stdin); 
				break;
			case 'i':
				n = getchar();
				fread(ibuffer, n+1, 4, stdin);
				break;
			case 'd':
				n = getchar();
				fread(dbuffer, n+1, 8, stdin);
				break;
		}

		//printf(
	} 
}
