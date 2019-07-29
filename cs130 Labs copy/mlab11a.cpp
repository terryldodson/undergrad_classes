
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	unsigned long int result;

	sscanf(argv[1], "%lx", &result);

	printf("Address: 0x%lx\n", result);

	int vpn2, vpn1, vpn0, poff;

	poff = result & 0xfff;
	vpn0 = 0x1ff & (result >> 12);
	vpn1 = 0x1ff & (result >> 21);
	vpn2 = 0x1ff & (result >> 30);

	printf("vpn[2] = %d\n", vpn2);
	printf("vpn[1] = %d\n", vpn1);
	printf("vpn[0] = %d\n", vpn0);
	printf("poff = %x\n", poff);
}
