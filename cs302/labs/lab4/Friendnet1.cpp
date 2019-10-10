#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

void set_oldfriends(vector <string> &name, vector<vector<bool> > &friends, int M0, int M1) {
  	int N = (int) name.size();
	int j;

	friends.assign(N, vector<bool>(N,0)); //assign friends vector (0 because they're not friends yet)		

  	for (int i=0; i<N; i++) {
		set<int> doknow;

		int M = M0 + rand() % M1;	
		
		while ((int) doknow.size() < M) {
			do {
				j = rand() % N; //compute j (random friend index: hint j != i)
			} while(i == j);

			doknow.insert(j);

		}

		//use iterator to sweep thru doknow set
		//update the corresponding pairs of friends entries
		set<int>::iterator it;

		for(it = doknow.begin(); it != doknow.end(); ++it) {
			j = *it;

			friends[i][j] = friends[j][i] = 1;
		}
  	}
}

void set_newfriends(vector<vector<bool> > &friends, vector<vector<bool> > &new_friends) {
  	int N = (int) friends.size();

  	new_friends.assign(N, vector<bool>(N,0)); //assign new_friends vector (0 because they're not friends yet)

  	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) { //for each adjacent friend (friends[i][j] == 1)
			if(i != j && friends[i][j] == 1) {
				for (int k=0; k<N; k++) { //for each adjacent friend-of-friend (friends[k][i] == 1)
					if (friends[k][j] == 1 && k != i && friends[i][k]==0) //if k is not i and k is not friend of i
						new_friends[i][k] = new_friends[k][i] = 1; //update the corresponding pairs of new_friends entries
				}
			}
    	}
  	}
}

void writetofile(const char *fname, vector<string> &name, vector<vector<bool> > &friends) {
	ofstream op;

	op.open(fname);

  	int N = (int) name.size();
	int max = 0;
	int count = 0;

	//determine max name length
	for(int i = 0; i < N; i++) {
		if(name[i].length() > max)
			max = name[i].length();
	}

	for (int i=0; i<N; i++) {
		count = 0;
		op << setw(max) << left << name[i] << " :"; 
		for (int j = 0; j < N; j++) {
			if(friends[i][j] == 1) { //for each adjacent friend
				//	op << " " << setw(max) << left  << name[j]; //pretty-print name[i] and name[j] (see assignment) 
				//	count++;
				if(count >= 8) {
					count = 0;
					op << endl << setw(max) << left << name[i] << " :";

				}
				op << " " << setw(max) << left << name[j];
				count++;
			}

		}
		op << endl;

	}
	op.close();
}

void print_error() {
	cerr << "usage: datafile.txt | Friendnet1 [-seed N]\n";
	exit(0);
}

int main(int argc, char *argv[]) {
  	if(argc != 1 && argc != 3) {
		print_error();
  	}

	int seednum = atoi(argv[2]);
	string names;

	if(argc == 1)
		srand(time(NULL));
	else
		srand(seednum);

  	vector<string> name;

	while(cin >> names) {
		name.push_back(names);
	}

 	int M0 = 1; // min number of friends
  	int M1 = 3; // potential extra friends

	vector<vector<bool> > friends;  
	vector<vector<bool> > new_friends;

  	set_oldfriends(name, friends, M0, M1);
  	writetofile("doknow1.txt", name, friends);

  	set_newfriends(friends, new_friends);
  	writetofile("mightknow1.txt", name, new_friends);
}
