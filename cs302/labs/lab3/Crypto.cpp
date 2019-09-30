#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

#include "Support.h"

void print_error() {
	cerr << "usage: crypto -encode|decode image.ppm\n";
	exit(0);
}

void encode(ppm img, const vector<pixel> &pix) {
	char c;
	int x, y, i_col, i_pix, i_bit, psz;
	bool insert;

	i_col = 0;
	i_pix = 0;
	insert = false;
	psz = pix.size();

	while(cin.get(c)) {
		if(i_col == 0)
			img[x][y].r;
		if(i_col == 1)
			img[x][y].g;
		if(i_col == 2)
			img[x][y].b;
	}

	for(i_bit = 0; i_bit < 7; i_bit++) {
		if(i_pix >= psz)
			print_error();

		x = pix[i_pix].x;
	}
}

//void decode(...) {
  //write this
//}

vector<pixel> set_pixel_list(ppm &image) {
	vector<pixel> list;
	int x, y, w, h;

	w = image.get_Ncols();
	h = image.get_Nrows();

	for(y = 0; y < h; y += 2)
		for(x = 0; x < w; x += 2)
			list.push_back(pixel(x, y));

	return list;
}

string inject_wmsg(const char* fn) {
	string fname = fn;

	return fname.substr(0, fname.length() - 4) + "_wmsg.ppm";
}

int main(int argc, char *argv[]) {
	if(argc != 3)
		print_error();

	ppm img;
	string arg = string(argv[1]);
	vector<pixel> proc_pix;

	//read in image
	img.read(argv[2]);

	//create pixel list
	proc_pix = set_pixel_list(img);			

  //finds out what function they called
	if (strcmp("-encode", arg.c_str()) == 0) {
		encode(img, proc_pix);
		//write to the file with '_wmsg" appended
		img.write(inject_wmsg(argv[2]).c_str());
	}
//	elseif (strcmp("-decode" , arg) == 0) 
//		decode(img, proc_pix);
	else
		return 0;
}


