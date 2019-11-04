#ifndef DSET_Hi
#define DSET_H

#include <vector>

class dset {  
	struct node {    
		node() { rank=0, parent=-1; }    
		int rank;    
		int parent;  
	};  

	public:    
		dset(int Nsets);    
		~dset();
		
//		dset();

		int size() { return Nsets; }    
		
		int merge(int, int);    
		int find(int);  

	private:    
		int Nsets;    
		node* S = new node;
};

#endif
