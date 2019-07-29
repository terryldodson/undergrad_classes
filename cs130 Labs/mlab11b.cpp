#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    unsigned long int result;

    sscanf(argv[1], "%lx", &result);

    printf("Page Table Entry: 0x%lx\n", result);

	printf("Physical Address: 0x%lx\n", result);
	printf("Entry Bits: \n");

	printf("\tBit V: %s", "SET\n");
	printf("\tBit R: %s", "SET\n");
	printf("\tBit W: %s", "SET\n");
	printf("\tBit X: %s", "SET\n");
	printf("\tBit U: %s", "CLEAR\n");
	printf("\tBit G: %s", "SET\n");
	printf("\tBit A: %s", "SET\n");
	printf("\tBit D: %s", "SET\n");
}	
