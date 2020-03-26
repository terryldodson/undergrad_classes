/*Name: Terryl Dodson
 * dson3:hydra2 ~/comp_sci_classes/cs360/labs/lab7/subm
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
	struct Flist *next_node = free_list_begin(); //ptr node
	struct Flist *tmp = free_list_begin(); //temp node
	int count = 0;
	int i, size;

	//only a single node on the list
	if(head->next == head) {
		return;
	}//end of if

	//obtaining the count of nodes on the list
	while(next_node != NULL) {	
		int sum;
		count++;
		printf("count: %d\n", count);
		next_node = next_node->next;
		//sum += next_node->size;

		//printf("sum: %d\n", sum);
	}//end of while



	//creating and allocating size for array
	int *array = (int*) (malloc(sizeof(void*) * count));


	//	printf("pizza\n");
	//inserting nodes in array
	for(i = 0; i < count; i++) {
		array[i] = (int) head;
		head = ((flist*)head)->next;
		//head->prev->next = head->next;
	}//end of for 

	//for(i = 0; i < count; i++) {
	//		count = 1;
	//printf("count1: %d\n", count);
	//printf("# \t Address \t Size \t prev \t next\n");
	//array[i] = (int) head;	
	//printf("%d Memory: %0x%x Size: %d\n", array[i], array[i], ((flist*) array[i])->size);
	//}

	//sorting nodes
	qsort(array, count, sizeof(int), cmpnodes);

	/*	printf("Sorted: \n");
		for(i = 0; i < count; i++) {
	//      count = 1;
	//printf("count1: %d\n", count);
	//printf("# \t Address \t Size \t prev \t next\n");
	//array[i] = (int) head;
	printf("%d\n", array[i]);
	}
	*/

	//	for(i = 0; i < count; i++) {

	//i}
	//reset head variables
	head = (flist*) array[0];
	next_node = (flist*) array[0];
	tmp = (flist*) array[0];
	//	head->prev->next = head->next;
	//int sum;
	//

	for(i = 0; i < count-1; i++) {
		size = ((flist*) array[i])->size;
		printf("size: %d, array[i]: %d, size + array[i]: %d, array[i+1]:%d\n", size, array[i], array[i] + size, array[i+1]);
	}

	for(i = 0; i < count-1; i++) {
		size = ((flist*) array[i])->size;

		if(array[i+1] == array[i] + size) {
			//tmp = (flist*) array[i];	
			//tmp = (flist*) array[i];
			tmp->size += ((flist*) array[i+1])->size;
			printf("array[i] value: %d, i value: %d\n", array[i], i);

			//printf("pizza7");
			fflush(stdout);
			next_node = NULL;
			tmp->next = next_node;
			tmp = (flist*) array[i+1];

			/*if(tmp->next == NULL) {
				tmp = array[0];
			}*/

			/*printf("pizza10");
			flist* ptr = head;
			while(ptr != NULL){
				if(ptr->next == (flist*) array[i+1]) {
					printf("ptr: %d\n", ptr);
					//ptr = ptr->next;
					ptr->next = ((flist*) array[i+1])->next;
					break;
				}
				ptr = ptr->next;
			}*/

		/*	while(tmp != NULL) {
				printf("array[i]: %d array[i+1]: %d\n", array[i], array[i+1]);
				tmp = tmp->next;
			}*/
			/*while(ptr->next != (flist*) array[i+1]){
			  ptr = ptr->next;
			  }

			  ptr->next = ((flist*) array[i+1])->next;*/
			
		}

		else {
			//tmp = array[0];
			//i = 0;
			printf("array[i+1] next: %d\n", ((flist*) array[i+1])->next);
			next_node = ((flist*) array[i])->next;
			tmp->next = next_node;
			tmp = (flist*) array[i];

		}
		//printf("size: %d\n", size);
	}

	tmp = head;
	while(tmp != NULL) {
		printf("value: %d, size: %d\n", (int) tmp, tmp->size);
		tmp = tmp->next;
	}

	//goes through to check and make sure the nodes are contiguous
	//if so it merges them together and sets the size
	//if not, then it sets the head to the next node
	/*for(i = 0; i < count; i++) {
	  size = ((flist*) tmp[i])->size;
	//		printf("array previous[i]: %d array[i]: %d array[i+1]: %d Size: %d\n", ((flist*) array[i])->prev, array[i], array[i+1], size);

	if(tmp[i] == array[i+1] + size) {
	//printf("pizza1");
	next_node = (flist*) array[i];
	next_node->size += ((flist*) array[i+1])->size;
	//((flist*) array[i])->next = ((flist*) array[i+1])->next;

	if((flist*) array[i+1] == head) {
	(((flist*) array[i])->prev)->next = ((flist*) array[i+1])->next;
	head = (flist*) array[i];
	head = head->next;
	}


	else {
	flist* ptr = (flist*) array[i+1];
	//flist* ptr2 = (flist*) array[i+1];
	printf("pizza");
	printf("array[i]: %d array[i] next: %d array[i+1]: %d array[i+1] next: %d Size: %d\n", (flist*) array[i], ((flist*) array[i])->next, ptr, ptr->next, size);
	while(ptr == head){
	//if(ptr == NULL)
	//	break;
	printf("pizza5");
	ptr = ptr->next;
	}


	//printf("ptr->next was: %d, is now: %d\n", ptr->next, ((flist*) array[i+1])->next);
	//if(ptr != NULL)
	printf("ptr prev: %d\n", ptr->prev);
	printf("array[i] prev: %d\n", ((flist*) array[i])->prev);
	printf("array[i+1] prev: %d\n", ((flist*) array[i+1])->prev);
	ptr->next = ((flist*) array[i+1])->next;
	ptr->prev = ((flist*) array[i+1])->prev;
	}
	else if((((flist*) array[i])->prev) != NULL) {

	//while(head->next != (FList*) array[i+1]){
	//array[i+1]->prev = array[i+1]->prev->next;
	(((flist*) array[i])->prev)->next = ((flist*) array[i+1])->next;
	array[i] = array[i+1];
	}

	array[i+1] = array[i];
	}//end of if

	//printf("Size: %d\n", size);
	else {
	next_node->next = (flist*) array[i+1];
	next_node = next_node->next;
	}//end of else

	//sum += next_node->size;
	}//end of for*/

	//flist* tmp = head;
	/*while(tmp != NULL) {
	  printf("size: %d\n", tmp->size);		
	  tmp = tmp->next;
	  }*/

	//next_node->next = NULL;

	while(head != NULL) {
		//		count = 1;
		//printf("count1: %d\n", count);
		//printf("# \t Address \t Size \t prev \t next\n");
		//array[i] = (int) head;	
		//printf("Memory: %0x%x Size: %d Sum: %d\n", head, head->size, sum);
		head = head->next;
	}

	//sets the last node's next to NULL
	//also free the array
	//next_node->next = NULL;
	free(array);
}//end of coalesce_free_list
