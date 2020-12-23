#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

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

int main(int argc, char *argv[]) {
  int counter = 0; //gives the position in stack
  if (argc != 3) {
    //print usage error message to stderr
	return 0;
  } 

  FILE* fp;
  FILE *sd;

  fp = fopen(argv[1], "r");
  sd = fopen(argv[2], "w");

  int Nrow;
  int Ncol;

  fscanf(fp, "MAZE %d %d", &Nrow, &Ncol);

  //create array of walls for each grid cell
  //initialize to have boundary walls set and
  //interior walls unset

  bool ***wall; //creates a 3 dimensional array
  wall = new bool**[Nrow];

  //the three for loops sets up walls (provides memory for them)
  for(int i = 0; i < Nrow; i++) {
	  wall[i] = new bool*[Ncol];
  }

  for(int i = 0; i < Nrow; i++) {
	for(int j = 0; j < Ncol; j++) {
		wall[i][j] = new bool [4];
	}
  }

  //initialize every wall to be false
  for(int i = 0; i < Nrow; i++) {
	  for(int j = 0; j < Ncol; j++) {
		  for(int k = 0; k < 4; k++) {
			  wall[i][j][k] = false; //sets every wall in array to 0
			}
		}
  }

  //0-east 1-south 2-west 3-north

  //initialize boundary walls (boundary walls)
  for(int i = 0; i < Nrow; i++) {
	for(int j = 0; j < Ncol; j++) {
		if(i == 0) //sets north wall if at first row (can't go up), same thing for rest
			wall[i][j][3] = true;
		if(i == Nrow-1)
			wall[i][j][1] = true;
		if(j == 0)
			wall[i][j][2] = true;
		if(j == Ncol-1)
			wall[i][j][0] = true;
	}
  }

  //read in input file and set the interior walls
  
  int i0,j0,i1,j1; //four numbers from mazemake

  while(!feof(fp)) {
	fscanf(fp, "%3d %3d %3d %3d", &i0, &j0, &i1, &j1);

	if(j0 == j1) { //sets up symmetrical walls (if they have a wall in common)
		wall[i0][j0][1] = true;
		wall[i1][j1][3] = true;
	} 

	else if(i0 == i1) {
		wall[i0][j0][0] = true;
		wall[i1][j1][2] = true;
	}
  }

  //initialize the path using DFS computation
  cell source = cell(0,0);
  cell sink = cell(Nrow-1,Ncol-1);

  bool notvisited[Nrow][Ncol];

  for(int i = 0; i < Nrow; i++) {
	for(int j = 0; j < Ncol; j++) {
		notvisited[i][j] = true;
	}
  }

  int N = Nrow*Ncol;

  //carry out DFS computation
  cell S[N]; //stack
  S[0] = source;

  static const int directions[4][2] = {
	{0,1}, //east
	{1,0}, //south
	{0, -1}, //west
	{-1, 0} //north
  };

  while(1) {
	if(S[counter].x == sink.x && S[counter].y == sink.y)
		break;
	
	int dnum; //direction number in boolean array

	notvisited[S[counter].x][S[counter].y] = false;

	for(dnum = 0; dnum < 4; dnum++) {
		int nextcell_x, nextcell_y;
		nextcell_x = S[counter].x + directions[dnum][0];
		nextcell_y = S[counter].y + directions[dnum][1];

		if(wall[S[counter].x][S[counter].y][dnum] == false && notvisited[nextcell_x][nextcell_y]) {
			S[counter + 1].x = nextcell_x;
			S[counter + 1].y = nextcell_y;
			notvisited[nextcell_x][nextcell_y] = false;
			counter++;
			break;
		}
	}

	if(dnum == 4)
		counter--;
  }
  
  //write PATH the Nrow and the Ncol header
  //write the cells on the path to file
  
  fprintf(sd, "PATH %d %d\n", Nrow, Ncol);

  for(int i = 0; i <= counter; i++) {
	fprintf(sd, "%d %d\n", S[i].x, S[i].y);
  }

  fclose(fp);
  fclose(sd);
}
