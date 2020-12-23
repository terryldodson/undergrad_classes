//LAB5 Synopsis: Created a lab to read in a encrypted file, decrypt it, and print out its contents. 
//NAME: Terryl Dodson
//DATE: 9/25/18
//TAs and Students I worked with: Leroy (TA)

#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char **argv) {
	//checks to see if there are 4 commmand line arguments, if not it will exit
	if(argc != 4) {
		exit(1);
	}//end of if

	int convertedInt;
	char convertedChar;

	//opens file the file for reading, and converts the third and fourth argument
	FILE *f = fopen(argv[1], "rb");
	sscanf(argv[2], "%c", &convertedChar);
	sscanf(argv[3], "%d", &convertedInt);
	fseek(f, 0, SEEK_END); //fseek to the end to obtain size
	long int size = ftell(f);

	fseek(f, 0, SEEK_SET); //fseek back to beginning

	int chunks = size/8;

	char* word = new char[chunks];
	
	//loop over all chunks and stores the correct values into letter and location. Also prints out error message if the int is negative or greater than number of chunks
	for(int i = 0; i < chunks; i++) {
		char letter;
		fread(&letter, sizeof(letter), 1, f);
		fseek(f, 3, SEEK_CUR);
		int location;
		fread(&location, sizeof(location), 1, f);

		char decrypt = convertedChar ^ letter;
		int decryptInt = convertedInt ^ location;

		if(decryptInt > chunks || decryptInt < 0) {
			printf("Error decoding chunk %d, decoded index %d, but max chunks is %d\n", i, decryptInt, chunks);
			return 0;
		}//end of if
	
		//inserts letter at correct index in the word array
		word[decryptInt] = decrypt;
	}//end of for loop

	//prints out word array
	printf("%s\n", word);

	//closes file
	fclose(f);

}//end of main
