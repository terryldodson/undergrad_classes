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
//	printf("Here4\n");
	struct Flist *node;

	//sets the size to a multiple of 8 and then + 8
	size = (size + 7 + 8) & -8;

	//copy of head
	struct Flist *head1 = head;

	//loops while head is not NULL
//	printf("here2\n");
	while(head1 != NULL) {
//		printf("Here3\n");
		//checks to see if the size requested if less than the node size
		//if so, we return the requested size + bookkeeping and update the free list with the current size
		printf("head1 size: %d\n", head1->size);
		printf("size: %d\n", size);
		//printf("head1 next size: %d\n", head1->next->size);
		//printf("tmp size first: %d\n", tmp->size);
		if(size <= head1->size) {
			struct Flist* tmp;
			int new_size = head1->size-size;
			int leftover_size = head1->size-new_size;
			head1->size = new_size;	
			
			tmp = (flist*) ((void*) head1 + new_size);
			tmp->size = leftover_size;
			printf("Tmp size: %d\n", tmp->size);
	
//			print_free_list(tmp);

			//if its the first node
			//printf("previous to head node: %d\n", head1->prev->size);
			if(head1->prev == NULL) {
			//if(1) {
				//printf("head is NULL");
				if(leftover_size <= 8) {
					struct Flist* old_head;
					old_head = head1;
					head1 = head1->next;
//					printf("old head size: %d\n", old_head->size);
					return (char*) old_head + 8;
				}

//				printf("head node but more than 8");
				//head1 = head;
				//head1 = head1->next;
				//printf("head node size: %d\n", head1->size);
				//printf("Tmp2 size: %d\n", tmp->size);
				return (flist*) ((char*) tmp + 8);
			} //end of if

			else {
				if(leftover_size <= 8) {	
					head1->prev->next = head1->next; 
					//printf("head1 size: %d\n", head1);
					return (char*) head1 + 8;
				}	

//				printf("non-head node but more than 8");
				return (char*) tmp + 8;
			} //end of else

//			printf("fasfdf\n");
		}//end of if
		//printf("going to next head");
		printf("going to next node\n");
		printf("next node size: %d\n", head1->next->size);
		head1 = head1->next;
	}//end of while

		//checks if the size is equal to the node size
		//if so, we just take out that chunk and relink the nodes
		//else if(size == head1->size) {
			//looking at the first node
			//set the head node and return the head node (relink nodes)
		//	if(head1->prev == NULL) {
		//		head1 = head1->next;
		//		return (void*) head1 + 8;
		//	}//end of if	

			//looking at the last node
			//set the previous equal to node (relink nodes)
		//	else if(head1->next == NULL) {
		//		head1 = head1->prev;
		//		return (void*) head1 + 8;
		//	}//end of else if

			//looking at middle nodes
			//link the previous and next node once we delete the middle node
			//return that node
		//	else {
		//		head1->prev = head1->next; 
		//		return (void*) head1 + 8;
		//	}//end of else
	//	}//end of else if

	//checks for nodes with sizes greater than 8192
	if(size > 8192) {
//		printf("piza");
		//created a new node with size of 8192
		//and return that node
//		head = (flist*) ((char*) sbrk(0) - size - 8);
		head1 = (void*) sbrk(size);
		head1->size = size;
//		printf("here");
		return (char*) head1 + 8;
	}//end of if

	//checks for nodes rest of nodes
	//create a new node, update size of new node
	//set the next node equal to null bcuz its redundant
	//return the node 
	struct Flist* tmp;
	struct Flist* head_copy;

//	printf("if NULL and not enough size");
	
	//head = (void*) sbrk(8192);
	
	head_copy = head;
	
	head = (void*) sbrk(8192);

	int new_size = 8192-size;
	int leftover_size = 8192-new_size;

	head->size = new_size;
	
//	printf("size of head: \n", head->size);
	
	head->next = head_copy;
	//head->next->size = new_size;

	tmp = (flist*) ((char*) head + new_size);
	tmp->size = leftover_size;
	//head->size = tmp->size;

	printf("tmp size last: %d\n", tmp->size);
	printf("head size last: %d\n", head->size);
//	printf("allocated size: sbrk");
	
	return (char*) tmp + 8;
}

void my_free(void *ptr) {
	//saves old head
	//sets the new head
	//links the new one to the old one
	struct Flist *node;
	struct Flist *old_head;
	
	if(ptr == NULL) {
		return;
	}

	node = (flist*) ((char*) ptr-8);
	ptr = head;
	head = node;
	node->next = ptr;
}

//returns the first node in the free list
void *free_list_begin() {
	//if free list is empty return NULL 
	if(head == NULL) {
		return NULL;
	}

	return (void*) head;
}

//returns the next node in the list
void *free_list_next(void *node) {
	/*if (node == NULL){
		return NULL;
	}

	return ( (flist *) node)->next; */
	
	flist *f = (flist*) node;

	//if its the last node, return NULL
	if(f->next == NULL) {
		return NULL;
	}

	return (flist*) ((void*) f->next);
}

void coalesce_free_list() {

}

void print_free_list(struct Flist* node) {
	while(node->next != NULL) {
		printf("previous node: \n", node->prev);
		printf("previous node size: \n", node->prev->size);
		printf("node: \n", node);
		printf("size:\n", node->size);
		printf("next node: \n", node->next);
		printf("next node size: \n", node->next->size);
		node = node->next;
	}
}
