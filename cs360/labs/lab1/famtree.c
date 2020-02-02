#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

typedef struct person {
	char* name[100];
	char* type[100];
	char* key;
	char sex;
	struct Person* Mother;
	struct Person* Father;
	Dllist children;
	Dllist toprint;
	int visited;
	int printed;
} Person;

void is_descendant(Person *p);

int main(int argc, char **argv) {
	JRB people, temp;
	int nsize, found;
	Person* p;
	Person* m;
	Person* f;
	char* name_copy;
	Dllist print; //node used to jump around
	Dllist toprint;

	//creates red black tree titled 'people'
	people = make_jrb();
	IS is;
	int i;
	char name[100];
	char type[100];

	is = new_inputstruct(argv[1]);
	if (is == NULL) {
		perror(argv[1]);
		exit(1);
	}

	while(get_line(is) >= 0) {
		for (i = 0; i < is->NF; i++) {
			printf("%d: %s\n", is->line, is->fields[i]);
		}

		nsize = strlen(is->fields[0]);
		for (i = 1; i < is->NF-1; i++) {
			nsize += (strlen(is->fields[i])+1);
		}

		//allocate name string and copy the first word into the string
		strcpy(type, is->fields[0]);
		strcpy(name, is->fields[1]);


		//copy in the remaining words and set it equal to name
		nsize = strlen(is->fields[1]);
		for (i = 1; i < is->NF-1; i++) {
			p->name[nsize] = ' ';
			strcpy(p->name+nsize+1, is->fields[i]);
			nsize += strlen(p->name+nsize);

			//checks to see if name is in rbtree, if not it inserts it
			temp = jrb_find_str(people, name);

			if(temp == NULL && type == "FATHER_OF") {
				p = (Person*) malloc(sizeof(Person));
				p->sex = 'M';
				p->Mother = NULL;
				p->Father = NULL;
				p->children = new_Dllist();
				p->visited = 0;
				p->printed = 0;
				p->name = strdup(name);
				jrb_insert_str(people, name, new_jval_v((Person *) p));
			}

			if(temp == NULL && type == "MOTHER_OF") {
				p = (Person*) malloc(sizeof(Person));
				p->sex = 'F';
				p->Mother = NULL;
				p->Father = NULL;
				p->children = new_Dllist();
				p->visited = 0;
				p->printed = 0;
				p->name = strdup(name);
				jrb_insert_str(people, name, new_jval_v((Person *) p));
			}
			
			//create another person
			//say we have Bob, the info beneath is all about Bob
			//if he haas a child called Alice I need to create another person 
			//and set her equal to bob as a child
			
			//person, father_of(set the chid equal to the father), mother_of(set the child equal to the mother), sex, children, father, mother
		}

		//creating name key
		p->key = (char*) malloc(sizeof(char) * (nsize + 12));
		sprintf(p->key, "%s", p->name);

		p->visited = 0;

		JRB y;

		//checks for cycles
		jrb_traverse(y, people) {
			if(is_descendant((Person *) y->val.v, print)) {
				fprintf(stderr, "Bad input -- cycle in specification\n");
				return -1;
			}
		}

		/* assume that there is an integer field called "printed" 
		 *    in the Person struct, and that this field is initialized 
		 *       to zero for all people */

		traverse(y, people) {
			dll_append(toprint, y->val);

			while(!dll_empty(toprint)) {
				take p off the head of toprint
				if p has not been printed, then 
				if p doesn't have parents, or if p's parents have been printed then
				print p
				for all of p's children, put the child at the end of toprint
				end if
				end if
				end while
			}
	} 

	/* assume that there is an integer field called "visited" 
	 *         in the Person struct, and that this field is initialized 
	 *                 to zero for all people */

	void is_descendant(Person *p, Dllist print)  {

		if (p->visited == 1) 
			return 0;							/* I.e. we've processed this 
												   person before and he/she's ok */
		if (p->visited == 2) 
			return 1;  /* I.e. the graph is messed up */

		p->visited = 2;

		dll_traverse(print, p->children) {
			//extracts the person to look at children
			Person* p2;
			p2 = jval_v(print->val);
			if(is_descendant(p2, print) return 1;
		}
		p->visited = 1; //already visited node
		return 0;
	}

