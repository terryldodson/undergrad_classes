#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

struct cell { ... }

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print usage error message to stderr
	return 0;
  } 

  open input file for reading
  open output file for writing

  int Nrow;
  int Ncol;

  determine Nrow,Ncol from input file

  create array of walls for each grid cell
  initialize to have boundary walls set and
  interior walls unset

  bool wall[Nrow][Ncol][4];

  read input file, set interior walls

  initalize DFS path computation

  source = (0,0)
  sink = (Nrow-1,Ncol-1)

  bool iswhite[][]
  cell link[][]

  carry out DFS source-to-sink computation

  write PATH, Nrow, Ncol header
  write cells on path to file

  close open files
}
