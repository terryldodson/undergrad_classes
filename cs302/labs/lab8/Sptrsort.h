//WRITE THIS BASED ON SMART POINTER CLASS
using namespace std;

template <typename T>
class sptr {
  public:
    sptr(T *_ptr=NULL) { ptr = _ptr; }
    bool operator< (const sptr &rhs) const {
      return *ptr < *rhs.ptr;
    }
    operator T * () const { return ptr; }
  private:
    T *ptr;
}; 

template <typename T>
void sptrsort(std::vector<T *> &A) {
	size_t a_sz, i;
	vector< sptr<T> > ptrs;

	//vector of smart pointers
	a_sz = A.size();
	ptrs.resize(a_sz);

	//fill with values from "A"
	for(i = 0; i < a_sz; i++)
		ptrs[i] = sptr<T> (A[i]);
	
	//Utilize Introsort
	sort(ptrs.begin(), ptrs.end());

	//store sorted values back into "A"
	for(i = 0; i < a_sz; i++)
		A[i] = ptrs[i];
}
