#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

typedef struct person {
	char* name;
	char* type[100];
	char* key;
	int sex;
	struct person* Mother;
	struct person* Father;
	Dllist children;
	Dllist toprint;
	int visited;
	int printed;
} Person;

int is_descendant(Person *p);

int main(int argc, char **argv) {
	JRB people, temp, tmp2;
	int nsize, found;
	Person* p;
	Person* m;
	Person* f;
	char* name_copy;
	Dllist print; //node used to jump around
	Dllist toprint = new_dllist();
	Dllist head; //used to print out nodes in sorted form
	Dllist end;

	//creates red black tree titled 'people'
	people = make_jrb();
	IS is;
	int i = 0;
	char name[100];
	char type[100];
//	int num_of_people = 0;

	is = new_inputstruct(argv[1]);
	if (is == NULL) {
		perror(argv[1]);
		exit(1);
	}

	while(get_line(is) >= 0) {
		//has to read something
		if(is->NF == 0)
			continue;

		/*(for (i = 0; i < is->NF; i++) {
			//printf("%d", 1);
			//printf("%d: %s\n", is->line, is->fields[i]);
		}
		nsize = strlen(is->fields[0]);
		for (i = 0; i < is->NF; i++) {
			nsize += (strlen(is->fields[i])+1);
		}

		//allocate name string and copy the first word into the string
		strcpy(type, is->fields[0]);
		strcpy(name, is->fields[1]);

		/*copy in the remaining words and set it equal to name*/
		//nsize = strlen(is->fields[1]);
		//for (i = 0; i < is->NF; i++) {
			//printf("%s\n", "Inside for loop");
			//printf("%s", type);
			//p->name[nsize] = ' ';
			//strcpy(p->name+nsize+1, is->fields[i]);
			//nsize += strlen(p->name+nsize);

			/*checks to see if name is in rbtree, if not it inserts it*/
	
			//temp = jrb_find_str(people, name);
			//tmp2 = jrb_find_str(people, name); */

			if(!strcmp(is->fields[0], "PERSON")) {
                p = (Person*) malloc(sizeof(Person));
                p->sex = 0;

                //set sex and write error message
                /*if(p->sex == '\0') {
                    p->sex = 'M';
                } else if(p->sex != 'M') {
                    fprintf(stderr, "Bad input -- sex mismatch on line #");
                }*/

                p->Mother = NULL;
                p->Father = NULL;;
                p->children = new_dllist();
                //dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) p));
                p->visited = 0;
                p->printed = 0;
                p->name = strdup(name);
				jrb_insert_str(people, p->name, new_jval_v(p));
				temp = jrb_find_str(people, name);
				//JRB tmp3;
//				printf("%s\n", "ADDING A PERSON");
				//tmp3 = jrb_find_str(people, name);	
				//printf("%s\n", ((Person *) (tmp3->val.v))->name);
//				printf("%s\n", "Looking FOR A PERSON");
//				num_of_people++;
			}
             			
			if(temp == NULL && strcmp(type, "FATHER_OF") == 0) {
				p = (Person*) malloc(sizeof(Person));
				p->sex = '\0';

				//set sex and write error message
				if(p->sex == '\0') {
					p->sex = 'M';
				} else if(p->sex != 'M') {
					fprintf(stderr, "Bad input -- sex mismatch on line #");
				}

				p->Mother = NULL;
				p->Father = (Person *) temp->val.v;
				p->children = new_dllist();	
				dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) p));
				p->visited = 0;
				p->printed = 0;
				p->name = strdup(name);
				jrb_insert_str(people, name, new_jval_v((Person *) p));
			} else if(strcmp(type, "FATHER_OF") == 0) {
				dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) tmp2->val.v));
			}

			if(temp == NULL && strcmp(type, "MOTHER_OF") == 0) {
				p = (Person*) malloc(sizeof(Person));
				p->sex = '\0';

				//set sex and write error message
				if(p->sex == '\0') {
					p->sex = 'F';
				} else if(p->sex != 'F') {
					fprintf(stderr, "Bad input -- sex mismatch on line #");
				}

				p->Mother = NULL;
				p->Father = NULL;
				((Person*)(temp->val.v))->Mother = p;
				p->children = new_dllist();
				dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) p));
				p->visited = 0;
				p->printed = 0;
				p->name = strdup(name);
				jrb_insert_str(people, name, new_jval_v((Person *) p));
			} else if(strcmp(type, "MOTHER_OF") == 0) {
				dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) tmp2->val.v));
			}

			if(temp == NULL && type == "FATHER") {
				p = (Person*) malloc(sizeof(Person));
				p->sex = '\0';

				//set sex and write error message
				if(p->sex == '\0') {
					p->sex = 'M';
				} else if(p->sex != 'M') {
					fprintf(stderr, "Bad input -- sex mismatch on line #");
				}

				p->Mother = NULL;
				p->children = new_dllist();
				((Person *) (temp->val.v))->Father = p;
				dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) tmp2->val.v));
				p->visited = 0;
				p->printed = 0;
				p->name = strdup(name);
				jrb_insert_str(people, name, new_jval_v((Person *) p));

				if(p->Father != NULL && p->Father != p) {
					fprintf(stderr, "Bad input -- child with two fathers on line #");
				}
			}

			if(temp == NULL && type == "MOTHER") {
				p = (Person*) malloc(sizeof(Person));
				p->sex = '\0';

				//set sex and write error message
				if(p->sex == '\0') {
					p->sex = 'F';
				} else if(p->sex != 'F') {
					fprintf(stderr, "Bad input -- sex mismatch on line #");
				}

				p->children = new_dllist();
				((Person *) (temp->val.v))->Mother = p;
				dll_append(((Person *) (temp->val.v))->children, new_jval_v((void *) tmp2->val.v));
				p->Father = NULL;
				p->visited = 0;
				p->printed = 0;
				p->name = strdup(name);
				jrb_insert_str(people, name, new_jval_v((Person *) p));

				if(p->Mother != NULL && p->Mother != p) {
					fprintf(stderr, "Bad input -- child with two fathers on line #");
				}
			}
	//	}
	} //end of while


	JRB y;
	Dllist z;

	//checks for cycles
	jrb_traverse(y, people) {
//		printf("%d\n", 11);
		if(is_descendant((Person *) y->val.v)) {
			fprintf(stderr, "Bad input -- cycle in specification\n");
			return -1;
		}
	}

	//	printf("%s", y->val.v->name);

	/* assume that there is an integer field called "printed" 
	 *    in the Person struct, and that this field is initialized 
	 *       to zero for all people */

//	printf("%d", 1);

	jrb_traverse(y, people) {
//		printf("%d", 3);
		dll_append(toprint, new_jval_v(temp->val));
		printf("%s", toprint->val.v);
//		printf("%d", 7);
	}

//	printf("%d\n", 5);			

	while(!dll_empty(toprint)) {
		//printf("%s", 4);
		//take p off the head of toprint
		p = (Person *) dll_first(toprint)->val.v;

		//if p has not been printed, then 
		if(p->printed == 0) {
			printf("%s", p->name);			
			p->printed = 1;

			//if p doesn't have parents, or if p's parents have been printed then
			//print p
			if(p->Father == NULL && p->Mother == NULL || p->printed == 1)
				printf("%s", p->name);

			//for all of p's children, put the child at the end of toprint
			dll_traverse(z, p->children) 
				dll_append(toprint, new_jval_v(z->val.v));

		} //end of if
	} //end of while
} //end of main

/* assume that there is an integer field called "visited" 
 *         in the Person struct, and that this field is initialized 
 *                 to zero for all people */

int is_descendant(Person *p)  {
	Dllist print;

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
		if(is_descendant(p2)) return 1;
	}

	p->visited = 1; //already visited node

	return 0;

}

