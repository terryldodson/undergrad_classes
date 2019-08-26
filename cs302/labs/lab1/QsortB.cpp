
// include header files needed
using namespace std;

class data { ... }

void printlist(...) { ... }

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
  std::sort(A.begin(), A.end();

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
