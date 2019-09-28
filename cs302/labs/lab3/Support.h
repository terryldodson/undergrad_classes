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
		//should there be 2 asteriks or 1
		T **buf;
};

struct pixel { 
	//should there be a variable before "=0" (like i or j)
	pixel(int = 0, int = 0);
	int x, y;
};

struct RGB {
	RGB(uchar = 0, uchar = 0, uchar = 0);
	uchar r, g, b;
};

class ppm {
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
