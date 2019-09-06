
// include header files needed
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

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
}

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

template <typename Tdata>
void quicksort(...) { 
  // write this 
}

template <typename Tdata>
void quickselect(...) { 
  // write this 
}

int main(int argc, char *argv[]) {
  // perform command-line error checking
  // usage: QsortB -stl | -rpivot [k0 k1]

  vector<data> A;

  data din;
  while (cin >> din)
    A.push_back(din);
  
  // add selection between sorting options

  // option -stl
  std::sort(A.begin(), A.end());

  // option -rpivot
  int N = (int)A.size();

  int k0 = 0;
  int k1 = N-1;

  // update k0, k1 if given as command-line arguments, 
  // then apply quickselect to partition A accordingly
  // A[0:N-1] --> A[0:k0-1] <= A[k0:k1] <= A[k1+1:N-1]

  quicksort(A, k0, k1);

  printlist(A.begin(), A.end());
}
