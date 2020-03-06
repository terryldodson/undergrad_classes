#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

typedef struct Flist {
	int size;
	struct Flist *next;
	struct Flist *prev;
} flist;

struct Flist *head = NULL; 

void *my_malloc(size_t size) {
	struct Flist *node;

	//sets the size to a multiple of 8 and then + 8
	size = (size + 7 + 8) & -8;
	
	//copy of head
	struct Flist *head1 = head;

	//loops while head is not NULL
	while(head1 != NULL) {
		//checks to see if the size requested if less than the node size
		//if so, we return the requested size + bookkeeping and update the free list with the current size
		if(size < node->size) {
			int new_size = node->size-size;
			int left_over = node->size-new_size;
			node->size = size;
			head1->size = new_size;
			return (void*) (node+8) + left_over;
		}//end of if

		//checks if the size is equal to the node size
		//if so, we just take out that chunk and relink the nodes
		else if(size == node->size) {
			//looking at the first node
			//set the head node and return the head node (relink nodes)
			if(node->prev == NULL) {
				head->next = head;
				return head+8;
			}//end of if	

			//looking at the last node
			//set the previous equal to node (relink nodes)
			else if(node->next == NULL) {
				node = node->prev;
				return node+8;
			}//end of else if

			//looking at middle nodes
			//link the previous and next node once we delete the middle node
			//return that node
			else {
				node->prev = node->next; 
				return node+8;
			}//end of else
		}//end of else if

		head1 = head1->next;
	}//end of while

	//checks for nodes with sizes greater than 8192
	if(head == NULL && size > 8192) {
		//created a new node with size of 8192
		//and return that node
		node = (void*) sbrk(8192);
		node->size = size;
		return (void*) node+8;
	}//end of if

	//checks for nodes with sizes less than 8192
	else if(head == NULL && size < 8192) {
		//create a new node, update size of new node
		//set the next node equal to null bcuz its redundant
		//return the node 
		head = (void*) sbrk(8192);
		int new_size = 8192-size;

		head->size = new_size;
		//head->next = NULL;
		head->next = NULL;
		//head->size + new_size = size;

		return (head+new_size)+8;
	} //end of else if
}

void my_free(void *ptr) {
	//saves old head
	//sets the new head
	//links the new one to the old one
	struct Flist *node;
	struct Flist *ptr1;
	ptr1 = (flist*) ptr;

	node = head;
	head = ptr1-8; 
	ptr1->next = node;
}

//returns the first node in the free list
void *free_list_begin() {
	return (void*) head;
}

//returns the next node in the list
void *free_list_next(void *node) {
	flist *f = (flist*) node;

	return f->next;  
}

void coalesce_free_list() {

}
