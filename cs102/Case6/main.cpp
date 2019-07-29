#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//function prototype
void printTopNames(const string mnames[], const string fnames[], const int mfreq[], const int ffreq[], int mcount, int gcount, int topnames, ofstream& fout); 

int main(int argc, char **argv)
{
//declares variables
	int freq, topnames;
	string names;
        string mnames[10000], fnames[10000];
        int mfreq[10000], ffreq[10000];
	int mcount=0, gcount=0;
	char gender, gen;
	int count;
	int lim;
	
	ifstream fin;
	
	//A - check to make sure argc has the correct number of parameters should be 2 - the name 
	//of the program and the name of the file
	if(argc != 4){
		cout << "Wrong number of arguments" << endl;
		cout << "Correct usage: ifilename ofilename #namesToPrint";
		return 0;
	}//end of if
	

	count = atoi(argv[3]);

	//B - now we can open the file.... the name of the file is in argv[1]
	fin.open(argv[1]);
	if(fin.fail()){
		cout << argv[1] << " not opened";
		return 0;
	}//end of if
	
	lim = 0;

//receiving data from the file
        while(fin >> names >> gender >> freq){
         if(gender == 'F'){
            fnames[gcount] = names;
            ffreq[gcount] = freq;
            gcount++;
         }//end of if
         if(gender == 'M'){
            mnames[mcount] = names;
            mfreq[mcount] = freq;
            mcount++;
         }//end of if
         if(gen == gender){
            cout << setw(10) << left << names << setw(10) << right << freq << endl;
            lim++;
         }//end of if
         if(lim >= count)
            break;
        }//end of while

        ofstream fout;
        fout.open(argv[2]);

//writing to file
	printTopNames(mnames, fnames, mfreq, ffreq, mcount, gcount, count, fout);
	fin.close();
	return 0;

}//end of main

//function declaration
void printTopNames(const string mnames[], const string fnames[], const int mfreq[], const int ffreq[], int mcount, int gcount, int topnames, ofstream& fout){
   fout << topnames << " Most Popular Boys and Girls Names" << endl;
   fout << endl;
   fout << left << setw(10) << "Girls" << right << setw(10) << "Frequency" << "    " << left << setw(10) << "Boys" << right << setw(10) << "Frequency"<< endl;

   if(mcount < gcount && mcount < topnames)
      topnames = mcount;
   if(gcount < mcount && gcount < topnames)
      topnames = gcount;
   if(topnames < mcount && topnames < gcount)
      topnames = topnames;

   for(int i = 0; i < topnames; i++){
       fout << left << setw(10) << fnames[i] << right << setw(10) << ffreq[i] << "    " << left << setw(10) << mnames[i] << right << setw(10) << mfreq[i] << endl;
   }//end of for loop

}//end of printTopNames