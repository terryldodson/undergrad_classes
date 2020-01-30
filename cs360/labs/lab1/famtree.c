#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

struct person {
	char* name[100];
	char sex;
	struct Person* Mother;
	struct Person* Father;
	Dllist children;
} Person;

int main(int argc, char **argv) {
	JRB people;

	//creates red black tree titled 'people'
	people = make_jrb();
	IS is;
	int i;

	is = new_inputstruct(argv[1]);
	if (is == NULL) {
		perror(argv[1]);
		exit(1);
	}

	while(get_line(is) >= 0) {
		for (i = 0; i < is->NF; i++) {
			printf("%d: %s\n", is->line, is->fields[i]);
		}
	}

	//read each line and see what the line reads
	//if it reads person then create a person
	//add its children

}

