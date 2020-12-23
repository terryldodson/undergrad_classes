#include <iostream>
#include <string>
#include "Support.h"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " ppm_input ppm_output\n";
		return 1;
	}

	ppm obj;             /* Create a PPM object         */
	obj.read(argv[1]);   /* Read in a PPM file          */
	obj.write(argv[2]);  /* Write the PPM to a new file */

	return 0;
}
