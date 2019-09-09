
// include header files needed
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class data {
 public:
    // add operator< using lastname, firstname, phone number

    friend istream & operator>>(istream &, data &);
    friend ostream & operator<<(ostream &, const data &);

    bool operator<(const data &) const;

  private:
    string firstname;
    string lastname;
    string phonenum;
};

istream & operator>>(istream &in, data &r) {
  // write this to read data object data
  in >> r.firstname >> r.lastname >> r.phonenum;
  return in;
}

ostream & operator<<(ostream &out, const data &r) {
  // write this to write data object data
  out << setw(24) << left << r.lastname + " "  + r.firstname << r.phonenum << "\n";
  return out;
}

bool data::operator<(const data &rhs) const {
    /*compare last name*/
    if(lastname != rhs.lastname)
        return lastname < rhs.lastname;

    /*compare first name*/
    if(firstname != rhs.firstname)
        return firstname < rhs.firstname;

    /*compare phone number*/
    return phonenum < rhs.phonenum;
}

template <typename T>
void printlist(T i, T p) {
  // template based iterator code for printing data to stdout
  while(i != p) {
    cout << *i;
    i++;
  }
  return;
}

template <typename T>
int quicksort(std::vector<T> &A, int left, int right) {  
	//creating pindex value and setting it to pivot
	if(left < right) {
		int pindex = left + rand() % (right-left+1);
		T pivot = A[pindex];  
	
		//swapping pindex with right (beginning stage)
		swap(A[pindex], A[right]);  
	
		int i = left - 1;  
		int j = right;   

		//runs through until i is greater than pivot and j is less than pivot, then it swaps the two
		while (1) {    
			while (A[++i] < pivot) { 
				if(i == right)
					break;
			}    
			while (pivot < A[--j]) { 
				if(j == left)
					break;
			}
    
			if (i>=j) 
				break;
    
			swap(A[i], A[j]);  
		}  
	
		pindex = i;  
		swap(A[pindex], A[right]); 
		
		//calls itself to go through the rest of the vector
		quicksort(A, left, pindex-1);
    	quicksort(A, pindex+1, right);

		return pindex;
	}
}

template <typename T>
void quickselect(vector<T> &A, int left, int k, int right) { 
	//creating pindex value and setting it to the pivot
	while(left < right) {
        int pindex = left + rand() % (right-left+1);
        T pivot = A[pindex];
    
        //swapping pindex with right (beginning stage)
		swap(A[pindex], A[right]);
    
        int i = left - 1;
        int j = right;

		//runs through until i is greater than pivot and j is less than pivot, then it swaps the two
        while (1) {
            while (A[++i] < pivot) {
                if(i == right)
                    break;
            }

            while (pivot < A[--j]) {
                if(j == left)
                    break;
            }
    
            if (i>=j)
                break;
    
            swap(A[i], A[j]);
        }
    
        pindex = i;
        swap(A[pindex], A[right]);
        
		//checks to see if the pindex in the now sorted list is equal to k, if so then you return
        if(pindex == k)
            return;

		//if pindex is greater or less than k then you adjust right and left
        if (k < pindex) 
            right = pindex-1;
        else            
            left = pindex+1;

    }
}

int main(int argc, char *argv[]) {
  //command-line error checking

	if(argc != 2 && argc != 4) { 
		cerr << "usage : QsortB -stl | -rpivot [k0 k1]" << endl;
		return 1;
	}

	vector<data> A;

	//reading in data
  	data din;
	while (cin >> din)
    	A.push_back(din);

  	int N = (int)A.size();
  	int k0 = 0;
  	int k1 = N-1;

	//checking the input to determine which code to run
	if(argc == 2) {  		
		if(string(argv[1]) == "-stl")
			std::sort(A.begin(), A.end());
		if(string(argv[1])  == "-rpivot")			
			quicksort(A, k0, k1);	
	}

	if(argc == 4) {
		int k0 = atoi(argv[2]);
		int k1 = atoi(argv[3]);

		if(k0 < 0)
			k0 = 0;

		if(k1 > N - 1)
			k1 = N - 1;

		quickselect(A, 0, k0, N-1); //sorts only up to when pivot equals to k0
		quickselect(A, k0, k1, N-1); //sorts only up to when pivot equals to k1
		quicksort(A, k0, k1); //sorts the rest of the vector
	}

	//prints list
	printlist(A.begin(), A.end());
}
