#include <...>
using namespace std;

void set_oldfriends(vector <string> &name, 2D-vector-array &friends, int M0, int M1) {
  int N = (int)name.size();
  initialize 2D-vector-array friends (hint: use vector::assign())

  for (int i=0; i<N; i++) {
	declare std::set called doknow

	initialize M (random number of friends: function of M0, M1)

	while ((int)doknow.size() < M) {
	  compute j (random friend index: hint j != i)
	  doknow.insert(j);
	}

	use iterator to sweep thru doknow set
	update the corresponding pairs of friends entries
  }
}

void set_newfriends(2D-vector-array &friends, 2D-vector-array &new_friends) {
  int N = (int)friends.size();
  initialize 2D-vector-array new_friends (hint: use vector::assign())

  for (int i=0; i<N; i++) {
	for (each adjacent friend: friends[i][j] == 1) {
	  for (each adjacent friend-of-friend: friends[j][k] == 1) {
	    if (k-is-not-i && k-is-not-friend-of-i)
	      update the corresponding pairs of new_friends entries
	  }
    }
  }
}

void writetofile(const char *fname, vector<string> &name, 2D-vector-array &friends) {
  open file

  int N = (int)name.size();
  determine max name length

  for (int i=0; i<N; i++) {
	for (each adjacent friend: friends[i][j] == 1) {
	  pretty-print name[i] and name[j] (see assignment) 
  }

  close file
}

int main(int argc, char *argv[]) {
  parse argc, argv arguments
  print usage message and exit if invalid

  seed random number generator

  vector<string> name;
  read strings from stdin into name vector

  int M0 = 1; // min number of friends
  int M1 = 2; // potential extra friends

  declare 2D-vector-array called friends
  declare 2D-vector-array called new_friends

  set_oldfriends(name, friends, M0, M1);
  writetofile("doknow1.txt", name, friends);

  set_newfriends(friends, new_friends);
  writetofile("mightknow1.txt", name, new_friends);
}
