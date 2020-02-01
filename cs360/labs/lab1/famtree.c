#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

typedef struct person {
	char* name[100];
	char* key;
	char sex;
	struct Person* Mother;
	struct Person* Father;
	Dllist children;
} Person;

int main(int argc, char **argv) {
	JRB people;
	int nsize, found;
	Person *p;
	Person* m;
	Person* f;
	char* name_copy;

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

		p = malloc(sizeof(Person));
		
		nsize = strlen(is->fields[0]);
		for (i = 1; i < is->NF-1; i++) {
			nsize += (strlen(is->fields[i])+1);
		}

		//allocate name string and copy the first word into the string
		p->name = (char*) malloc(sizeof(char)*(nsize+1));
		strcpy(p->name, is->fields[0]);
	
		//copy in the remaining words and set it equal to name
		nsize = strlen(is->fields[1]);
		for (i = 1; i < is->NF-1; i++) {
			p->name[nsize] = ' ';
			strcpy(p->name+nsize+1, is->fields[i]);
			nsize += strlen(p->name+nsize);
		
			//creates the name key
			p->key = (char *) malloc(sizeof(char) * (nsize + 12));
			sprintf(p->key, "%s", p->name);

			//checks to see if name is in rbtree, if not it inserts it
			(void) rb_find_key_n(people, p->name, &found);
			
			if(!found & p->name == "FATHER_OF") {
				f = malloc(sizeof(Person));
				p->sex = 'M';
				name_copy = strdup(p->name);
				rb_insert(people, name_copy, f);
			}

			if(!found & p->name == "MOTHER_OF") {
				m = malloc(sizeof(Person));
				p->sex = 'F';
				name_copy = strdup(p->name);
				rb_insert(people, name_copy, m);
			}

			if(!found & p->name == "SEX") {
					
				
			}
		}

		//creating name key
		p->key = (char*) malloc(sizeof(char) * (nsize + 12));
		sprintf(p->key, "%s", p->name);
	}

	//read each line and see what the line reads
	//if it reads person then create a person
	//add its children

}

