/*Assignment Name: Case 8
 *Name: Terryl Dodson
 * Description: This program will be able to read in a picture
 * file and will be able to perform different tasks on the
 * picture. Tasks such as flipping the picture across the X and
 * Y axis, and also flattening and greying the picture.*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

//creates the structure for the individual pixels
struct pixelInfo1{
	int red, green, blue;
	pixelInfo1(int r, int g, int b);
	pixelInfo1();
};//end of pixelInfo1 struct

//creates the class for the overall picture
class pixelInfo2{
	vector <vector <pixelInfo1> > picture_data;
	int intensity, nRows, nCols;
	string p3;
public:
	bool inputa(ifstream&);
	bool outputa(ofstream&);
	pixelInfo2();
	void flipX();
	void flipY();
	void flatten();
	void grey();
};//end of pixelInfo2 class

int main(int argc, char **argv)
{
	pixelInfo2 pixel;
	ifstream fin;
	ofstream fout;
	istringstream sin;
	char letter;
	
//opens input file
	fin.open(argv[1]);
	if(pixel.inputa(fin) == false){
		cout << "Usage: inputfile outputfile [XYFG]" << endl;
		return -1;
	}//end of if
	
	//opens output file
	fout.open(argv[2]);
	
	if(argc < 3 || argc > 4){
		cout << "Usage: inputfile outputfile [XYFG]" << endl;
		return 0;
	}//end of if

//calls a function due to the letter that it was passed
	if(argc == 4){
		sin.str(argv[3]);
		sin >> letter;

		switch(letter){
			case 'X':
				pixel.flipX();
				break;
			case 'Y':
				pixel.flipY();
				break;
			case 'F':
				pixel.flatten();
				break;
			case 'G':
				pixel.grey();
				break;
			default:
				cout << "Error: "<< letter <<" is an invalid command. Use either X, Y, F or G" << endl;
				return -1;
		}//end of switch
	}//end of if

      //outputs the output file
	if(pixel.outputa(fout) == false){
		cout << "Error: tried to output an uninitialized PPM picture" << endl;
		return -1;
	}//end of if


}//end of main
pixelInfo1::pixelInfo1(int r, int g, int b){
	red = r;
	green = g;
	blue = b;
}//end of constructor 

pixelInfo1::pixelInfo1(){
	red = 0;
	green = 0;
	blue = 0;
}//end of constructor

//input function
bool pixelInfo2::inputa(ifstream& fin){
	int r, g, b;
	vector <pixelInfo1> rows;
	
	if(fin.fail()){
		return false;
	}//end of if
	
	fin >> p3 >> nCols >> nRows >> intensity;
	if(p3 != "P3")
		cout << "Error" << endl;
	if(nRows < 0 || nCols < 0)
		cout << "Error" << endl;
	if(intensity < 0)
		cout << "Error" << endl;

	for(int i = 0; i < nRows; i++){
		rows.clear();
		for(int j = 0; j < nCols; j++){
			fin >> r >> g >> b;
			rows.push_back(pixelInfo1(r,g,b));
		}//end of inner loop
		picture_data.push_back(rows);
	}//end of outer loop
	
	return true;
}//end of inputa function

//output function 
bool pixelInfo2::outputa(ofstream& fout){
	int r,g,b;
	if(fout.fail()){
		cout << "Error: unable to write PPM file \'given output file\'" << endl;
		return false;
	}//end of if

	if(nRows == 0 && nCols == 0){
		cout << "Error: tried to output an uninitialized PPM picture" << endl;
		return -1;
	}//end of if
	
	fout << p3 << endl; 
	fout << nCols << " " << nRows << endl;
	fout << intensity << endl;
	
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nCols; j++){
			fout << picture_data[i][j].red << " " << picture_data[i][j].green << " " << picture_data[i][j].blue << endl;
		}//end of inner loop
	}//end of outer loop
        return true;
}//end of outputa function
	
pixelInfo2::pixelInfo2(){
}//end of constructor

//code that flips the picture across the X axis
void pixelInfo2::flipX(){
	pixelInfo1 temp;

	for(int i = 0; i < nRows/2; i++){
		for(int j = 0; j < nCols; j++){
			temp = picture_data[i][j];
			picture_data[i][j] = picture_data[nRows - 1 - i][j];
			picture_data[nRows - 1- i][j] = temp;
		}//end of inner loop
	}//end of outer loop
}//end of flipX function

//code that flips the picture across the Y axis
void pixelInfo2::flipY(){
	pixelInfo1 temp;

	for(int i = 0; i < nRows; i++){
		for(int j = 0; j <nCols/2; j++){
			temp = picture_data[i][j];
			picture_data[i][j] = picture_data[i][nCols - 1 - j];
			picture_data[i][nCols - 1 - j] = temp;
		}//end of inner loop
	}//end of outer loop
}//end of flipY function

//code that flattens the picture
void pixelInfo2::flatten(){
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nCols; j++){
			picture_data[i][j].red = 0;
		}//end of inner loop
	}//end of outer loop
}//end of flatten function

//code that greys out the picture
void pixelInfo2::grey(){
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nCols; j++){
			int num = (picture_data[i][j].red + picture_data[i][j].green + picture_data[i][j].blue)/3;
			picture_data[i][j].red = num;
			picture_data[i][j].green = num;
			picture_data[i][j].blue = num;
		}//end of inner loop
	}//end of outer loop
}//end of grey function
