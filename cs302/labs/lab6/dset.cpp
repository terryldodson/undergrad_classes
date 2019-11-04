#include "dset.h"

dset::dset(int N) { 
	S = new node[N];
	Nsets = N;
}

dset::~dset() {
	delete [] S;
}


int dset::merge(int i, int j) {  
	i = find(i);  
	j = find(j);  

	if (i != j) {    
		node &Si = S[i];    
		node &Sj = S[j];    

		// merge (union) by rank    
		if (Si.rank > Sj.rank)      
			Sj.parent = i;    
		else if (Si.rank < Sj.rank) 
			Si.parent = j;     
		else { 
			Sj.parent = i; 
			Si.rank += 1; 
		}    

		Nsets -= 1;  
	}  

	return find(i);
}

int dset::find(int i) {  
	if (S[i].parent == -1)    
		return i;  

	// recursive path compression  
	S[i].parent = find(S[i].parent);  
	return S[i].parent;
}
