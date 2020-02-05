#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	int c, i;
	unsigned char n, size;
	char buffer[100];

	c = getchar();

	if(c != 110 || c != 115 || c != 105 || c != 100)
		fprintf(stderr, "Input error: bad type\n");

	if(c == 110) //character is an n
		printf("\n");

	//if(c == 115 || c == 105 || c == 100)
		
	switch(c) {
		case 110:
			printf("\n");
			break;
		case 115 || 105 || 100:
			n = getchar();			
				fread(buffer, n+1, 

	}
//printf("%d\n", c);
}
