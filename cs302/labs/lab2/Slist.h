#ifndef SLIST_H
#define SLIST_H

// include header file(s) needed

// template <typename T>
template <class T>
class slist {
  private:
    struct node {
      node() { data = T(); next = NULL; }
      // add node(const T &key) { write this }
      // add overloaded operator< code

      T data;
      node *next;
    };

   // add class sptr { write this for node data }

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
  // set up smart pointer array called Ap
  // if quicksort, apply std::sort(...)
  // if mergesort, apply std::stable_sort(...)
  // use sorted Ap array to relink list 
}

#endif // SLIST_H
