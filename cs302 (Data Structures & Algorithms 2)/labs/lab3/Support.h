#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

#include <stddef.h>

typedef unsigned char uchar;
extern const char ETX;

template <typename T>
class matrix { 
	public:
		/* Swap Rows/Cols from handout */
		matrix(int n_Ncols, int n_Nrows) {
			Ncols = n_Ncols;
			Nrows = n_Nrows;

			buf = new T *[Ncols];
			for(int i = 0; i < Ncols; i++)
				buf[i] = new T[Nrows];
		}

		~matrix() {
			for(int i = 0; i < Ncols; i++)
				delete [] buf[i];

			delete [] buf;
		}

		int get_Nrows() const {
			return Nrows;
		}

		int get_Ncols() const {
			return Ncols;
		}

		T *operator[] (int i) {
			return buf[i];
		}

	private:
		int Nrows, Ncols;
		T **buf;
};

class rnumgen {  
	public:    
		rnumgen(int seedvalue, std::vector<int> &v);    
		int rand();  
	private:    
		std::vector<float> F;
};

struct pixel { 
	//stores a pair of row and colummn indices 
	pixel(int = 0, int = 0);
	int x, y;
};

struct RGB {
	//sets the three character values to 0
	RGB(uchar = 0, uchar = 0, uchar = 0);
	uchar r, g, b;
};

class ppm {
	//contains all functionality in order to 
	public:
		ppm();
		void read(const char*);
		void write(const char*);

		int get_Nrows() const;
		int get_Ncols() const;

		RGB * operator[](int);
	
	private:
		matrix<RGB> *pixels;

		void new_image(int, int);
};

#endif
