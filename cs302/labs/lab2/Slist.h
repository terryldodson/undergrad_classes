#ifndef SLIST_H
#define SLIST_H

// include header file(s) needed
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

template <class T>
class slist {
  private:
    struct node {
      node() { data = T(); next = NULL; }
      node(const T &key) {data = key; next = NULL;}
      // add overloaded operator< code
	  bool operator< (const node &rhs) const { return data < rhs.data; }

      T data;
      node *next;
    };

// add class sptr
class sptr {
	public:
    	sptr(node *_ptr=NULL) { ptr = _ptr; }
    	bool operator< (const sptr &rhs) const {
      		return *ptr < *rhs.ptr;
    	}
    	operator node * () const { return ptr; }
  	private:
  		node *ptr;
};

  public:
	class iterator {
	  public:
	    iterator() { p = NULL; }
	    T & operator*() { return p->data; }
	    iterator & operator++() { p = p->next; return *this; }
	    bool operator!=(const iterator & rhs) const { return p != rhs.p; }


	  private:
	    iterator(node *n_p) { p = n_p; }
	    node *p;

	  friend class slist<T>;
	};

  public:
    slist();
	~slist();

    void push_back(const T &);
	void sort(const string &);

	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(NULL); }

  private:
	node *head;
	node *tail;
};

template <typename T>
slist<T>::slist() {
  head = new node();
  tail = head;
}

template <typename T>
slist<T>::~slist() {
  while (head->next != NULL) {
    node *p = head->next;
    head->next = p->next;
    delete p;
  }
  delete head;

  head = NULL;
  tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
  tail->next = new node(din);
  tail = tail->next;
}

template <typename T>
void slist<T>::sort(const string &algname) {
  // determine number of list elements
	int num = 0;
	node *p;
	
	//get size of list
	p = head;
	while(p->next != NULL) {
		num++;
		p = p->next;
	}

  // set up smart pointer array called Ap
	vector<sptr> Ap(num);
	
	p = head;
	for(int i = 0; i < Ap.size(); i++) {
		Ap[i] = p->next;
		p = p->next;
	}
  // if quicksort, apply std::sort(...)
	if(algname == "quicksort")
		std::sort(Ap.begin(), Ap.end());
  // if mergesort, apply std::stable_sort(...)
	if(algname == "mergesort")
		std::stable_sort(Ap.begin(), Ap.end());
  // use sorted Ap array to relink list
	p = head;
	for(int i = 0; i < Ap.size(); i++) {
		p->next = Ap[i];
		p = p->next;
	}

  //set end of list to NULL so we dont loop back to a random spot
	p->next = NULL;
}

#endif // SLIST_H
