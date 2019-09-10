// include header file(s) needed
using namespace std;

#include "Slist.h"

// modify the data class and the associated input 
// and output operators to store, set and print a 
// line number identifier called ID

class data { copy from QsortA.cpp };
istream & operator>> (...) { copy from QsortA.cpp }
ostream & operator<< (...) { copy from QsortA.cpp }

void printlist(...) { copy from QsortA.cpp }

int main(int argc, char *argv[]) {
  // copy command-line check from QsortB.cpp,
  // then modify to apply to this assignment

  slist<data> A;

  data din;
  while (cin >> din)
    A.push_back(din);

  A.sort(command line mode option);

  printlist(A.begin(), A.end());
}
