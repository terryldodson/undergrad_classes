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
	int healing;
} Node;

typedef struct info {
	int num_jumps;
	double power_reduction;
	int best_healing;
	int best_path_length;
	Node **best_path;
	int *healing;
	double initial_power;
} Info;

void dfs(Node* n, int hop_num, Info* d, int total_healing, Node* b);

int main (int argc, char **argv) {
	int initial_range;
	int jump_range;

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
		d->initial_power = atoi(argv[4]);
		d->power_reduction = atof(argv[5]);
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
		n->visited = 0;
		n->healing = 0;
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
			if(i != j) {
				double distance = sqrt(pow(array[i]->x - array[j]->x, 2) + pow(array[i]->y - array[j]->y, 2));
				if(distance <= jump_range)
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
				if(distance <= jump_range) {
					array[i]->adj[k] = array[j];
					k++;
				}/*end of if*/
			}/*end of else*/
		}/*end of inner for loop*/
	}/*end of outer for loop*/

	d->best_path = (Node**) malloc(d->num_jumps * sizeof(Node*));

	/*setting up healing array*/
	d->healing = (int*) malloc(d->num_jumps * sizeof(int));
	
	/*setting up the initial_range*/
	int count;
	for(i = 0; i < ncount; i++) {
		double distance = sqrt(pow(array[i]->x - array[0]->x, 2) + pow(array[i]->y - array[0]->y, 2));

		if(distance <= initial_range) {
			dfs(array[i], 1, d, 0, array[i]);
			array[i]->visited = 0;
		}
	}

	for(i = 0; i < d->best_path_length; i++) {
		printf("%s %d\n", d->best_path[i]->name, d->healing[i]);
	}

	/*printing out total healing*/
	printf("Total_Healing %d\n", d->best_healing);

	/*freeing up memory*/
	for(i = 0; i < ncount; i++) {
		free(array[i]->adj);
		free(array[i]->name);
		free(array[i]);
	}

	free(array);
	free(initial_array);
	free(d);
	free(d->best_path);
	free(d->healing);
	
	return 0;
}

void dfs(Node* n, int hop_num, Info* d, int total_healing, Node* b) {

	if(hop_num > d->num_jumps)
		return;

	/*set visited equal to true*/
	n->visited = 1;
	int i;

	/*calculating total healing*/
	int power_diff = (n->max_PP - n->cur_PP);
	int initial_power_rounded = rint(d->initial_power);

	int power = rint(d->initial_power * pow((1 - d->power_reduction), hop_num-1));

	if(power > power_diff) {
		n->healing = power_diff;
	} else {
		n->healing = power;
	}

	n->prev = b;

	if(total_healing + n->healing > d->best_healing) {
        Node* temp = n;
        d->best_healing = total_healing + n->healing;
        d->best_path_length = hop_num;

		for(i = hop_num - 1; i >= 0; i--) {
			d->best_path[i] = temp;
            d->healing[i] = temp->healing;
            temp = temp->prev;
        }
    }	

	for(i = 0; i < n->adj_size; i++) {
		/*if node isn't visited then process node*/
		if(n->adj[i]->visited == 0 && hop_num <= d->num_jumps) {
			n->visited = 1;
			dfs(n->adj[i], hop_num+1, d, total_healing + n->healing, n); /*recursively call dfs to go to next node*/;
		} else { /*if node was already visited continue*/
			continue;
		} /*end of else*/ 
	} /*end of for loop*/

	n->visited = 0;

} /*end of dfs function*/
