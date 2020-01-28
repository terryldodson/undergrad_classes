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
	int *healing;
} Node;

typedef struct info {
	int num_jumps;
	double power_reduction;
	int best_healing;
	int best_path_length;
	Node **best_path;
	int *healing;
} Info;

void dfs(Node* n, int hop_num, Info* d, int total_healing, double power_reduction, int initial_power, Node* b);

/*./chain_heal 1 2 4 500 0.25 < small.txt*/
int* healing_array;

int main (int argc, char **argv) {
	int initial_range, initial_power;
	double jump_range;

	char interim_name[100];
	int interim_x, interim_y, interim_cur_PP, interim_max_PP;
	struct node *interim_prev = NULL;
	struct info *d = malloc(sizeof(Info));
	int ncount = 0;
	int i, j, k;
	
	/*assigning variables*/
	if(argc != 6) {
	
	} else {
		initial_range = atoi(argv[1]);
		jump_range = (double) atoi(argv[2]);
		d->num_jumps = atoi(argv[3]);
		initial_power = atoi(argv[4]);
		d->power_reduction = atoi(argv[5]);
	}/*end of else*/
	
	/*signing variables*/
	while(scanf("%d %d %d %d %s\n", &interim_x, &interim_y, &interim_cur_PP, &interim_max_PP, interim_name) != EOF) {
		Node* n = (Node*) malloc(sizeof(Node));
		n->name = (char*) malloc(sizeof(char) * 100);
		n->prev = interim_prev;
		interim_prev = n;
		n->x = interim_x;
		n->y = interim_y;
		n->cur_PP = interim_cur_PP;
		n->max_PP = interim_max_PP;
		strcpy(n->name, interim_name);
		ncount++; /*counting number of nodes*/
	} /*end of while loop*/

	Node** array = malloc(ncount * sizeof(Node));
	Node** initial_array = malloc(ncount * sizeof(Node));

	/*created array by traversing through it*/
	for(i = ncount - 1; i >= 0; i--) {
		array[i] = interim_prev;
		interim_prev = interim_prev->prev;
	}/*end of for loop*/

	/*creating the graph*/
	for(i = 0; i < ncount; i++) {
		array[i]->adj_size = 0;
		for(j = 0; j < ncount; j++) {
			double distance = sqrt(pow(array[i]->x - array[j]->x, 2) + pow(array[i]->y - array[j]->y, 2));
			
			if(distance <= jump_range && i != j) {
				array[i]->adj_size++;
			}
		}
	}

	/*calculating adjacency size for each node*/
	for(i = 0; i < ncount; i++) {
		array[i]->adj = malloc(array[i]->adj_size * sizeof(Node*));
	}/*end of for loop*/

	/*connected adjacent nodes*/
	for(i = 0; i < ncount; i++) {
		k = 0;
		for(j = 0; j < ncount; j++) {
			/*check to make sure they are node the same node*/
			if(i == j)
				continue;
			else{
				/*calculate the distance*/
				double distance = sqrt(pow(array[j]->x - array[i]->x, 2) + pow(array[j]->y - array[i]->y, 2));				
				/*if distance is less than jump_range then create an edge*/
				if(distance <= jump_range && i != j) {
					array[i]->adj[k] = array[j];
					k++;
				}/*end of if*/
			}/*end of else*/
		}/*end of inner for loop*/
	}/*end of outer for loop*/

	d->best_path = (Node**) malloc(d->num_jumps * sizeof(Node*));

	 /*setting up the initial_range*/
	int count;
	for(i = 0; i < ncount; i++) {
		double distance = sqrt(pow(array[i]->x - array[0]->x, 2) + pow(array[i]->y - array[0]->y, 2));

		if(distance <= initial_range) {
			count++;	
		}
	}

	/*setting up healing array*/
	healing_array = (int*) malloc(d->num_jumps * sizeof(int*));

	for(i = 0; i < count; i++) {
		dfs(array[i], 1, d, 0, d->power_reduction, initial_power, array[i]);
	}

	/*printing out total healing*/
	printf("Total Healing %d\n", d->best_healing);

	return 0;
}

void dfs(Node* n, int hop_num, Info* d, int total_healing, double power_reduction, int initial_power, Node* b) {
	printf("Node:%s Hop %d\n", n->name, hop_num);
	
	if(hop_num == d->num_jumps)
		return;

	/*set visited equal to true*/
	n->visited = 1;
	int i;

	/*calculating total healing*/
	int power_diff = (n->max_PP - n->cur_PP);
	int initial_power_rounded = rint(initial_power);

	if(initial_power_rounded > power_diff) {
		total_healing += power_diff;
		d->healing = power_diff;
	} else {
		total_healing += initial_power_rounded;
		d->healing = initial_power_rounded;
	}
	
	initial_power = initial_power * (1.0 - power_reduction);

	if(total_healing > d->best_healing) {
		Node* temp = n;
		d->best_healing = rint(total_healing);
		d->best_path_length = hop_num;
		for(i = hop_num; i > 0; i--) {
			d->best_path[i-1] = temp;
			healing_array[i-1] = temp->healing;
			temp = temp->prev;
		}
	}	

	b = n->prev;

	for(i = 0; i < n->adj_size; i++) {
		/*if node isn't visited then process node*/
		if(n->adj[i]->visited == 0 && hop_num < d->num_jumps) {
			dfs(n->adj[i], hop_num+1, d, total_healing, power_reduction, initial_power, b); /*recursively call dfs to go to next node*/
		} else { /*if node was already visited continue*/
			continue;
		} /*end of else*/ 
	} /*end of for loop*/
	
	n->visited = 0;

	/*keeping track of path*/
			
} /*end of dfs function*/
