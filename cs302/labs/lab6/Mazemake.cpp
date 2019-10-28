
#include <cstdlib>
#include <ctime>
#include <cstdio>

#include "dset.h"

struct cell { ... }

void swap(cell &c1, cell &c2) { ... }

int main(int argc, char *argv[]) {
  if (argc != 4) {
	print usage error message to stderr
    return 0;
  }

  int Nrow = atoi(argv[1]);
  int Ncol = atoi(argv[2]);

  // Grid wall:     (i0,j0) | (i1,j1)
  // Horizontal wall: (i,j) | (i+1,j)
  // Vertical wall:   (i,j) | (i,j+1)

  int N = number of interior grid walls
  cell wall[N][2];

  populate wall[][] with interior grid walls
  randomly perturb list order: swap based

  open output file for writing (argv[3])

  write MAZE, Nrow, Ncol header 

  for (k=0; k<N; k++) {
    if: pair of cells given by wall[k][] are not
	connected (belong to different disjoint sets),
	merge them
	
	else: write wall to file in the form of the
	two pairs of cell indices (i0,j0) (i1,j1)

    if: all cells belong to the same set, break
  }

  write any remaining walls to file

  close output file
}
