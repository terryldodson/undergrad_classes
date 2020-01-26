#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>   
#include <stdbool.h> 

typedef struct node
{
	char *name;
	int x, y;
	int cur_PP, max_PP;
	struct node *prev;
	int adj_size;
	struct node **adj;
	bool visited;
	int hop_num;
} Node;

//./chain_heal 1 2 4 500 0.25 < small.txt

int main (int argc, char **argv) {
	int initial_range, jump_range, num_jumps, initial_power;
	double power_reduction;

	char *interim_name;
	int interim_x, interim_y, interim_cur_PP, interim_max_PP;
	struct node *interim_prev = NULL;
	int ncount = 0;
	int i, j, k;
	
	Node** array = malloc(ncount * sizeof(Node));

	//assigning variables
	if(argc != 6) {
	
	} else {
		initial_range = atoi(argv[1]);
		jump_range = atoi(argv[2]);
		num_jumps = atoi(argv[3]);
		initial_power = atoi(argv[4]);
		power_reduction = atoi(argv[5]);
	}//end of else

	//reading in and assigning variables
	while(scanf("%d %d %d %d %s\n", &interim_x, &interim_y, &interim_cur_PP, &interim_max_PP, interim_name)) {
		Node* n = malloc(sizeof(Node));
		n->prev = interim_prev;
		interim_prev = n;
		n->x = interim_x;
		n->y = interim_y;
		n->cur_PP = interim_cur_PP;
		n->max_PP = interim_max_PP;
		n->name = interim_name;
		ncount++; //counting number of nodes
	} //end of while loop

	//created array by traversing through it
	for(i = ncount - 1; i >= 0; i--) {
		array[i] = interim_prev;
		interim_prev = interim_prev->prev;
		printf("%p\n", array[i]->prev);
	}//end of for loop

//creating the graph
	
	//calculating adjacency size for each node
	for(i = 0; i < ncount; i++) {
		array[i]->adj_size = malloc(ncount * sizeof(Node*));
	}//end of for loop

	//connected adjacent nodes
	for(i = 0; i < ncount; i++) {
		for(j = 0; j < ncount; j++) {
			//check to make sure they are node the same node
			if(i == j)
				continue;
			else{
				//calculate the distance 
				int distance = sqrt(pow(array[j]->x - array[i]->x, 2) + pow(array[j]->y - array[i]->y, 2));
				
				//if distance is less than jump_range then create an edge
				k = 0;
				if(distance <= jump_range) {
					array[i]->adj[k] = array[j];
					array[i]->adj_size++;
					k++;
				}//end of if
			}//end of else
		}//end of inner for loop
	}//end of outer for loop

	return 0;
}
