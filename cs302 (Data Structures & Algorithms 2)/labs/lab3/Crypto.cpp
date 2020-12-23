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

bool get_bit(const char &c, int bit) {
	return (c >> bit) & 0x1;
}

void encode(ppm img, const vector<pixel> &pix) {
	char c;
	int x, y, i_col, i_pix, i_bit, psz;
	bool insert;

	i_col = 0;
	i_pix = 0;
	insert = false;
	psz = pix.size();

	while(insert == false) {
		//set the breaking point (breaking condition)
		if(!(cin.get(c))) {
			c = ETX;
			insert = true;
		}

		for(i_bit = 0; i_bit < 7; i_bit++) {
			if(i_pix >= psz)
				print_error();
		
			x = pix[i_pix].x;
			y = pix[i_pix].y;

			RGB &ref = img[x][y];

			if(i_col == 0) {
				ref.r &= 0xFE;
				ref.r |= get_bit(c, i_bit);
			}
			if(i_col == 1) {
				ref.g &= 0xFE;
				ref.g |= get_bit(c, i_bit);
			}
			if(i_col == 2) {
				ref.b &= 0xFE;
				ref.b |= get_bit(c, i_bit);
			}
	
			i_col++;

			if(i_col > 2)
				i_col = 0;

			i_pix++;	
		}
	}
}

void decode(ppm img, const vector<pixel> &pix) {
    char c;
    int x, y, i_col, i_pix, i_bit;

    i_col = 0;
    i_pix = 0;

    while(true) {
        c = 0;

        for(i_bit = 0; i_bit < 7; i_bit++) {

            x = pix[i_pix].x;
            y = pix[i_pix].y;

            RGB &ref = img[x][y];

            if(i_col == 0) {
            	c |= ((ref.r & 0x01) << i_bit);
			}
            if(i_col == 1) {
                c |= ((ref.g & 0x01) << i_bit);
            }
            if(i_col == 2) {
                c |= ((ref.b & 0x01) << i_bit);
            }

            i_col++;

            if(i_col > 2)
                i_col = 0;

            i_pix++;

        }

		if(c == ETX)
			break;

		printf("%c", c);
    }
}

vector<pixel> set_pixel_list(ppm &image) {
	vector<pixel> list;
	int x, y, w, h, color;

	vector<int> histogram(2<<15, 0);

	w = image.get_Ncols();
	h = image.get_Nrows();

	//reading in one character at a time and adding it to the vector
	//also doing bit shifting to get the seven least significant bits
	for(y = 0; y < h; y++) {
		for(x = 0; x < w; x++) {
			list.push_back(pixel(x, y));
			RGB &ref = image[x][y];
			color = ((ref.r >> 3) << 10) | ((ref.g >> 3) << 5) | (ref.b >> 3);
			histogram[color]++;
		}
	}

	rnumgen RNG(0, histogram);
	
	//rand perm: makes it harder for someone to try and decode message
	for (int i=(int)list.size()-1; i>0; --i) { 
		int r1 = RNG.rand(); 
		int r2 = RNG.rand();
		int r30 = (r1 << 15) | r2;
  
		swap(list[i], list[r30 % (i+1)]);  
	}	
	
	return list;
}

//changes the name of the file when encoded
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
	if (strcmp("-decode" , arg.c_str()) == 0) {
		decode(img, proc_pix);
	}
	else
		return 0;
}


