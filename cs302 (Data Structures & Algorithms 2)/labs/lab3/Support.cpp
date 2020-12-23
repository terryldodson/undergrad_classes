#include <iostream>
#include <sstream>

using namespace std;

#include "Support.h"

const char ETX = 0x3;

//pixel struct
pixel::pixel(int _x, int _y) {
	x = _x;
	y = _y;
}

//RGB struct
RGB::RGB(uchar _r, uchar _g, uchar _b) {
	r = _r;
	g = _g;
	b = _b;
}

//PPM class
ppm::ppm() {
	pixels = NULL;
}


void ERROR_AND_DIE(string err, int code) {
	cerr << (err);
	exit(code);
}

void ppm::read(const char* fname) { 
  ifstream fp;
  string p6;
  int depth;
  int w,h,x,y;
	
  //opens file
  fp.open(fname);

  //check for if file was opened successfully
  if(!fp.is_open()) {
	ERROR_AND_DIE(string("Error: cannot open ") + fname + " for reading!\n", 0);
  }

  fp >> p6;

  //check "P6" header
  if(p6 != "P6")
	  ERROR_AND_DIE("Error: magicid not P6!\n", 0);

  //check invalid width/height and max depth
  //reads in w, h and depth. If it can't read those in it will print out error
  if(!(fp >> w >> h >> depth)) {
	ERROR_AND_DIE("Error: invalid width, height, or maxvalue!\n", 0);
  }

  //check "255"
  if(depth != 255) {
	cerr << "Error: maxvalue " << depth << " not supported\n";
	exit(0);
  }

  //read the newline
  fp.get();

  //create the image and fill in the data with bytes 
  new_image(w,h);

  for(y = 0; y < h; y++) {
	  for(x = 0; x < w; x++) {
		//get the current pixel and read in values
		RGB &ref = (*pixels)[x][y];

		//read in pixels.. if we can..
		ref.r = fp.get();
		ref.g = fp.get();
		ref.b = fp.get();
	  }
  }

  //closes file
  fp.close();

}

rnumgen::rnumgen(int seedvalue, vector<int> &v) {  
	srand(seedvalue);  
	
	F.resize(v.size());  
	partial_sum(v.begin(), v.end(), F.begin());  
	transform(F.begin(), F.end(), F.begin(),  bind2nd(divides<float>(), F.back()));
}

int rnumgen::rand() {  
	const double randmax = RAND_MAX+1.0;  
	const double p = (double)std::rand()/randmax;  
	
	return upper_bound(F.begin(), F.end(), p) - F.begin();
}

void ppm::write(const char* fname) { 
  ofstream op;
  int x, y;

  //opens file
  op.open(fname);

  op << "P6\n" << get_Ncols() << " " << get_Nrows() << "\n255\n";

  for(y = 0; y < get_Nrows(); y++) {
	for(x = 0; x < get_Ncols(); x++) {
		RGB &ref = (*pixels)[x][y];
		op << ref.r << ref.g << ref.b;
	}
  }
	
  //closes file
  op.close();
}

int ppm::get_Nrows() const {
	if(pixels != NULL)
		return pixels->get_Nrows();

	return 0;
}

int ppm::get_Ncols() const {
	if(pixels != NULL)
		return pixels->get_Ncols();

	return 0;
}

RGB * ppm::operator[](int r) {
	return (*pixels)[r];
}

void ppm::new_image(int w, int h) {
	//if we have an image that already exists, delete it
	if(pixels != NULL)
		delete pixels;

	//make a new one. simple
	pixels = new matrix<RGB>(w,h);
}
