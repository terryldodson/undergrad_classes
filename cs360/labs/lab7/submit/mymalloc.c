/*Name: Terryl Dodson
 * Date: 3/23/2020
 * Description: Had to create our own malloc program by writing my_malloc 
 * which returned to the user the requested size. Then we had to write 
 * coalesce which joins two nodes together if they're continguous in  memory*/

#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

typedef struct Flist {
	int size;
	struct Flist *next;
	struct Flist *prev;
} flist;

//global variable for head node
struct Flist *head = NULL; 

void *my_malloc(size_t size) {
	struct Flist *node;
	int sizeN;

	//sets the size to a multiple of 8 and then + 8
	size = (size + 7 + 8) & -8;

	//copy of head
	struct Flist *head1 = head;

	//loops while head is not NULL
	while(head1 != NULL) {

		//checks to see if the size requested is equal to the head's size
		//if so, just return that chunk and relink the nodes 
		if(size == head1->size) {
			struct Flist* old_head;
			int new_size = 8192 - size;
			int leftover_size = 8192 - new_size;

			if(head1 == head) {
				head = head1->next;
				return (char*) head1 + 8;
			}

			else {
				head1->prev->next = head1->next; 
				return (char*) head1 + 8;
			} //end of else
		} //end of outer if

		//checks to see if the size requested is less than the node size
		//if so, we return the requested size + bookkeeping and update the free list with the current size
		else if(size < head1->size) {
			struct Flist* tmp;
			int new_size = head1->size-size;
			int leftover_size = head1->size-new_size;
			head1->size = new_size;	

			tmp = (flist*) ((void*) head1 + new_size);
			tmp->size = leftover_size;

			return (flist*) ((char*) tmp + 8);
		}//end of else if

		head1 = head1->next;
	}//end of while

	//checks for nodes with sizes greater than 8192
	if(size > 8192) {
		//created a new node with requested size
		//and return that node
		head1 = (void*) sbrk(size);
		head1->size = size;
		return (char*) head1 + 8;
	}//end of if

	//checks for nodes rest of nodes
	//create a new node, update size of new node
	//set the next node equal to null bcuz its redundant
	//return the node 
	struct Flist* tmp;
	struct Flist* head_copy;

	head_copy = head;

	head = (void*) sbrk(8192);

	int new_size = 8192-size;
	int leftover_size = 8192-new_size;

	head->size = new_size;

	head->next = head_copy;

	tmp = (flist*) ((char*) head + new_size);
	tmp->size = leftover_size;

	return (char*) tmp + 8;
} //end of my_malloc

void my_free(void *ptr) {
	//saves old head
	//sets the new head
	//links the new one to the old one
	struct Flist *node;

	if(ptr == NULL) {
		return;
	} //end of if

	node = (flist*) ((char*) ptr-8);

	ptr = head;
	head = node;
	node->next = ptr;
} //end of my_free

//returns the first node in the free list
void *free_list_begin() {
	//if free list is empty return NULL 
	if(head == NULL) {
		return NULL;
	}//end of if

	return (void*) head;
}//end of free_list_begin

//returns the next node in the list
void *free_list_next(void *node) {

	flist *f = (flist*) node;

	//if its the last node, return NULL
	if(f->next == NULL) {
		return NULL;
	}//end of if

	return (flist*) ((void*) f->next);
}//end of free_list_next


//compares the nodes
int cmpnodes(const void* a, const void* b) {
	return *(int*) a - *(int*) b;
}//end of cmpnodes 

void coalesce_free_list() {
	struct Flist *head = free_list_begin(); //primary head
	struct Flist *next_node = free_list_begin(); //temp head
	int count = 0;
	int i, size;

	//only a single node on the list
	if(head->next == head) {
		return;
	}//end of if

	//obtaining the count of nodes on the list
	while(next_node != NULL) {	
		count++;
		printf("count: %d\n", count);
		next_node = next_node->next;
	}//end of while

	//creating and allocating size for array
	int *array = (int*) (malloc(sizeof(void*) * count));

	printf("pizza\n");
	//inserting nodes in array
	for(i = 0; i < count; i++) {
		array[i] = (int) head;	
		head = head->next;
	}//end of for 

	for(i = 0; i < count; i++) {
		//		count = 1;
		//printf("count1: %d\n", count);
		printf("# \t Address \t Size \t prev \t next\n");
		array[i] = (int) head;	
		printf("%d \t %0x%x \t %d \t %0x%x \t %0x%x\n", count, array[i], ((flist*) array[i])->size, ((flist*) array[i])->prev, array[i+1]);
	}

	//sorting nodes
	qsort(array, count, sizeof(int), cmpnodes);

	printf("Sorted: \n");
	for(i = 0; i < count; i++) {
        //      count = 1;
        //printf("count1: %d\n", count);
        printf("# \t Address \t Size \t prev \t next\n");
        array[i] = (int) head;
        printf("%d \t %0x%x \t %d \t %0x%x \t %0x%x\n", count, array[i], ((flist*) array[i])->size, ((flist*) array[i])->prev, array[i+1]);
    }

	//reset head variables
	head = (flist*) array[0];
	next_node = (flist*) array[0];

	//goes through to check and make sure the nodes are contiguous
	//if so it merges them together and sets the size
	//if not, then it sets the head to the next node
	for(i = 0; i < count-1; i++) {
		size = ((flist*) array[i])->size;

		if(array[i+1] == array[i] + size) {
			head->size += ((flist*) array[i+1])->size;
		}//end of if

		else {
			head->next = (flist*) array[i+1];
			head = head->next;
		}//end of else
	}//end of for

	//sets the last node's next to NULL
	//also free the array
	head->next = NULL;
	free(array);
}//end of coalesce_free_list
