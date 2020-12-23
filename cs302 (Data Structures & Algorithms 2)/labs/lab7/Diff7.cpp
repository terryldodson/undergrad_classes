#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <set>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <limits>
#include <stack>
#include <map>

using namespace std; 

template <typename T>
class matrix {
	public:
		void assign(int n_Nrows, int n_Ncols) {
			Nrows = n_Nrows;
			Ncols = n_Ncols;
							        
			buf = new T [Nrows*Ncols]; 
		} 
			
		~matrix() { 
			delete [] buf;
		}
				       
		int get_Nrows() const { return Nrows; }			       
		int get_Ncols() const { return Ncols; }
						       
		T * operator[] (int i) { return &buf[i*Ncols]; }
							     
	private:
		int Nrows, Ncols;
		T *buf;
};

class LCS {
  public:
    void text1_push_back(string s) { text1.push_back(s); };
    void text2_push_back(string s) { text2.push_back(s); };
	void compute_alignment();
	void report_difference();
	void print_edits(int a, int b, int c, int d);

  private:
	// support functions
    // text1 buffer
	vector<string> text1;
    // text2 buffer
	vector<string> text2;

	int m, n;

	//const int VERT = 1;
	//const int HORZ = 2;
	//const int DIAG = 4;

	matrix<int> cost; //edit costs
	matrix<int> link; //alignment info
};

//write assign (similar to matrix constructor)
//make edits to compute_alignment 
//write report_difference given psuedo code

void LCS::compute_alignment() {
    m = text1.size() + 1;
    n = text2.size() + 1;

    cost.assign(m+1, n+1);
    link.assign(m+1, n+1);
    cost[0][0] = 0;
    link[0][0] = 0;

	//1 for DELcost and INScost
    for (int i=1; i<=m; i++) {
      cost[i][0] = cost[i-1][0] + 1;
      link[i][0] = 1;
    }

    for (int j=1; j<=n; j++) {
      cost[0][j] = cost[0][j-1] + 1;
      link[0][j] = 2;
    }

    for (int i=1; i<m; i++) {
      for (int j=1; j<n; j++) {
		if(text1[i-1] == text2[j-1]) {
			cost[i][j] = cost[i-1][j-1];
			link[i][j] = 4; //where DIAG = 4
		}
		else
			cost[i][j] = m + n;

		int delcost = cost[i-1][j] + 1;
		int inscost = cost[i][j-1] + 1;
        
        if (inscost < cost[i][j]) {
          cost[i][j] = inscost;
          link[i][j] = 2;
        }

        if (delcost < cost[i][j]) {
          cost[i][j] = delcost;
          link[i][j] = 1;
        }

      }
    }
}

void LCS::print_edits(int i, int j, int k, int l) {
	if(k == 0 && l == 0) {
		//match no print
	}

	else if(k != 0 && l != 0){
		//change
		if(i-k+1==i)
			cout << i << 'c';
		else
			cout << i-k+1 << ',' << i << 'c';
		if(j-l+1 == j)
			cout << j << endl;
		else
			cout << j-l+1 << ',' << j << endl;
		for(int y = 0; y < k; y++) {
			cout << "< " << text1[i+y-k] << endl;
		}

		cout << "---" << endl;

		for(int x = 0; x < l; x++) {
			cout << "> " << text2[j+x-l] << endl;
		}
	}

	else if(k != 0)  {
		//delete
		if(i-k+1 == i)
			cout << i << 'd';
		else
			cout << i-k+1 << ',' << i << 'd';
		if(j-l== j)
			cout << j << endl;
		else
			cout << j-l+1 << ',' << j << endl;

		for(int x = 0; x < k; x++) {
			cout << "< " << text1[i+x-k] << endl;
		}
	}


	else if(l != 0)  {
        //insert
        if(i-k == i)
            cout << i << 'a';
        else
            cout << i-k+1 << ',' << i << 'a';
        if(j-l+1== j)
            cout << j << endl;
        else
            cout << j-l+1 << ',' << j << endl;

        for(int x = 0; x < l; x++) {
            cout << "> " << text2[j+x-l] << endl;
        }
    }	
}

void LCS::report_difference() {
	string mode;
	stack<int> trace, x, y;
	int i = m - 1;
	int j = n - 1;

	while(link[i][j] != 0) {
			if(link[i][j] == 1) {
				x.push(i);
				y.push(j);
				trace.push(1);
				mode = "I";
				i--;
			}

			if(link[i][j] == 2) {
				x.push(i);
				y.push(j);
				trace.push(2);
				mode = "D";
				j--;
			}

			if(link[i][j] == 4) {
				x.push(i);
				y.push(j);
				trace.push(4);
				mode = "M";
				i--;
				j--;
			}
	}

	//i and j are positions in matrix (x and y)
	i = 0;
	j = 0;
	
	int icount = 0, dcount = 0;

	while(!trace.empty()) {
		if(trace.top() == 4) {
			print_edits(i , j, dcount, icount);
			dcount = 0;
			i++;
			icount = 0;
			j++;
		}
		else if(trace.top() == 2) {
			icount++;
			j++;
		}
		else if(trace.top() == 1) {
			dcount++;
			i++;
		}

		trace.pop();
	}

	print_edits(i, j, dcount, icount);
}


int main(int argc, char *argv[])
{
  // check two input files are specified on command line
  if(argc != 3)
	  return 0;

  LCS lcs;  // instantiate your "LCS based diff" object
  ifstream fp(argv[1]);
  ifstream sd(argv[2]);
  string line;

  // read the text from file1 into the lcs.text1 buffe
  while(getline(fp, line)) {
	lcs.text1_push_back(line);
  }

  // read the text from file2 into the lcs.text2 buffer
  while(getline(sd, line)) {
	lcs.text2_push_back(line);
  }

  lcs.compute_alignment();
  lcs.report_difference();
}
