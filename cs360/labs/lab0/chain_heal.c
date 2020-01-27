#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>   

typedef struct node
{
	char *name;
	int x, y;
	int cur_PP, max_PP;
	struct node *prev;
	int adj_size;
	struct node **adj;
	int visited;
} Node;

typedef struct info {
	int num_jumps;
	double power_reduction;
	int best_path_length;
	Node **best_path;
	int *healing;
} Info;

void dfs(Node* n, int hop_num, Info* d);

/*./chain_heal 1 2 4 500 0.25 < small.txt*/

int main (int argc, char **argv) {
	int initial_range, jump_range, initial_power;

	char *interim_name;
	int interim_x, interim_y, interim_cur_PP, interim_max_PP;
	struct node *interim_prev = NULL;
	int ncount = 0;
	int i, j, k;
	
	Node** array = malloc(ncount * sizeof(Node));
	
	/*assigning variables*/
	if(argc != 6) {
	
	} else {
		Info* d = malloc(sizeof(Info));
		initial_range = atoi(argv[1]);
		jump_range = atoi(argv[2]);
		d->num_jumps = atoi(argv[3]);
		initial_power = atoi(argv[4]);
		d->power_reduction = atoi(argv[5]);
	}/*end of else*/

	/*reading in and assigning variables*/
	while(scanf("%d %d %d %d %s\n", &interim_x, &interim_y, &interim_cur_PP, &interim_max_PP, interim_name)) {
		Node* n = malloc(sizeof(Node));
		n->prev = interim_prev;
		interim_prev = n;
		n->x = interim_x;
		n->y = interim_y;
		n->cur_PP = interim_cur_PP;
		n->max_PP = interim_max_PP;
		n->name = interim_name;
		ncount++; /*counting number of nodes*/
	} /*end of while loop*/

	/*created array by traversing through it*/
	for(i = ncount - 1; i >= 0; i--) {
		array[i] = interim_prev;
		interim_prev = interim_prev->prev;
	}/*end of for loop*/

/*creating the graph*/
	
	/*calculating adjacency size for each node*/
	for(i = 0; i < ncount; i++) {
		array[i]->adj_size = malloc(ncount * sizeof(Node*));
	}/*end of for loop*/

	/*setting up the initial_range*/
	for(i = 0; i < ncount; i++) {
		for(j = 0; j < ncount; j++) {
			if(initial_range <= array[i]->adj_size)
				
		}
	}

	/*connected adjacent nodes*/
	for(i = 0; i < ncount; i++) {
		for(j = 0; j < ncount; j++) {
			/*check to make sure they are node the same node*/
			if(i == j)
				continue;
			else{
				/*calculate the distance*/
				int distance = sqrt(pow(array[j]->x - array[i]->x, 2) + pow(array[j]->y - array[i]->y, 2));
				
				/*if distance is less than jump_range then create an edge*/
				k = 0;
				if(distance <= jump_range) {
					array[i]->adj[k] = array[j];
					array[i]->adj_size++;
					k++;
				}/*end of if*/
			}/*end of else*/
		}/*end of inner for loop*/
	}/*end of outer for loop*/

	return 0;
}


hop_num = 1;

void dfs(Node* n, int hop_num, Info* d, int total_healing) {
	/*set visited equal to true*/
	n->visited = 1;
	int i;

	/*calculating total healing*/
	total_healing = n->max_pp - n->cur_pp;

	for(i = 0; i < n->adj_size; i++) {
		/*if node isn't visited then process node*/
		if(n->adj[i]->visited == 0 & hop_num < d->num_jumps) {
			hop_num++;
			printf("Node:%s Hop %d\n", n->name, hop_num);
			dfs(n->adj[i], hop_num, d); /*recursively call dfs to go to next node*/
		} else { /*if node was already visited continue*/
			continue;
		} /*end of else*/ 
	} /*end of for loop*/
	n->visited = 0;
	
	/*keeping track of path*/
	d->best_path = (Node**) malloc(num_jumps * sizeof(Node*));
	
} /*end of dfs function*/
