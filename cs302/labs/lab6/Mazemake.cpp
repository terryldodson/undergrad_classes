
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#include "dset.h"

struct cell {
	int x, y = 0;

	cell() {
		x = 0;
		y = 0;
	}

	cell(int i, int j) {
		x = i;
		y = j;
	}
};

void swap(cell &c1, cell &c2) {
	int tmp_x, tmp_y;

	//swap X
	tmp_x = c1.x;
	c1.x = c2.x;
	c2.x = tmp_x;

	//swap y
	tmp_y = c1.y;
	c1.y = c2.y;
	c2.y = tmp_y;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
	printf("Enter %d arguments\n", 4); 
    return 0;
  }

  int Nrow = atoi(argv[1]);
  int Ncol = atoi(argv[2]);

  // Grid wall:     (i0,j0) | (i1,j1)
  // Horizontal wall: (i,j) | (i+1,j)
  // Vertical wall:   (i,j) | (i,j+1)

  int v_w = (Ncol - 1) * Nrow; //vertical walls
  int h_w = (Nrow - 1) * Ncol; //horizontal walls

  int N = v_w + h_w; // number of interior grid walls

  cell wall[N][2]; //stores pairs of all cells with wall in between

  int k = 0;

  for(int i = 0; i < Ncol; i++) { //populate wall[][] with interior grid walls
	for(int j = 0; j < Nrow; j++) {
		if(i < Ncol-1) { //if you're at the last column there shouldn't be a wall
			wall[k][0] = cell(i, j);
			wall[k][1] = cell(i+1, j);
			k++;
		}
		
		if(j < Nrow-1) { //if you're at the last row there shouldn't be a wall
			wall[k][0] = cell(i, j);
			wall[k][1] = cell(i, j+1);
			k++;
		}
	}	
  }

 //randomly perturb list order: swap based
 //selecting given wall and random wall and swapping them
  for (int i=N-1; i>0; --i) {
	int j = rand() % (i+1);
    swap(wall[i][0], wall[j][0]);
	swap(wall[i][1], wall[j][1]);
  }

  FILE* fp;
  fp = fopen(argv[3], "w");

  fprintf(fp, "MAZE %d %d\n", Nrow, Ncol); //write MAZE, Nrow, Ncol header

  dset obj(Nrow*Ncol);
  int i;

  for (i=0; i<N; i++) {
	//convert 2D to 1D
	int ii = wall[i][0].x + (wall[i][0].y * Ncol);
	int jj = wall[i][1].x + (wall[i][1].y * Ncol);

	//if not already merged...
	if(obj.find(ii) != obj.find(jj)) {
		obj.merge(ii, jj);
	}
	
	else {
		//can't merge, so there's a wall
		fprintf(fp, " %d %d %d %d\n", wall[i][0].x, wall[i][0].y, wall[i][1].x, wall[i][1].y);
	}
	
	//if all cells belong to the same set
	if(obj.size() == 1)
		break;
  }

  i++;

  for(;i<N; i++) {
	fprintf(fp, "%d %d %d %d\n", wall[i][0].x, wall[i][0].y, wall[i][1].x, wall[i][1].y);
  }

  fclose(fp);
}
