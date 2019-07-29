/*Assignment Name: Case 7
 *Name: Terryl Dodson
 * Description: This program will be able to receive a name
 *and let the user know the rank and the frequency of that name.
 *it does this by reading names in from a file and displays the
 *information*/

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector> 

using namespace std;

//function prototype
void printTopNames(const vector<string> &mnames, const vector<string> &fnames, const vector<int> &mfreq, const vector<int> &ffreq, int topnames, ofstream& fout); 
int searchNames(vector <string> &names, string name);

int main(int argc, char **argv)
{
//declares variables
	int freq, topnames, i;
	string name, names;
	vector<string> mnames;
	vector<string> fnames;
	vector<int> mfreq;
	vector<int> ffreq;
	int mcount=0, gcount=0;
	char gender, gen;
	int count;
	int lim;
	istringstream ss;
	string line;
	int findf, findm;
	
	ifstream fin;
	
	//A - check to make sure argc has the correct number of parameters should be 2 - the name 
	//of the program and the name of the file
	if(argc != 4){
		cout << "Wrong number of arguments" << endl;
		cout << "Correct usage: ifilename ofilename #namesToPrint";
		return 0;
	}//end of if
	
	ss.str(argv[3]);
	ss >> count;

	//B - now we can open the file.... the name of the file is in argv[1]
	fin.open(argv[1]);
	if(fin.fail()){
		cout << argv[1] << " not opened";
		return 0;
	}//end of if
	
	lim = 0;

//receiving data from the file
	while(getline(fin, line)){
		ss.clear();
		ss.str(line);
		ss >> names >> gender >> freq;

		if(gender == 'F'){
			fnames.push_back(names);
			ffreq.push_back(freq);
		}//end of if
		if(gender == 'M'){
			mnames.push_back(names);
			mfreq.push_back(freq);
		}//end of if
		if(gen == gender){
			lim++;
		}//end of if
		if(lim >= count && count != 0)
			break;
	}//end of while

	ofstream fout;
	fout.open(argv[2]);
		
//writing to file
	printTopNames(mnames, fnames, mfreq, ffreq, count, fout);
	
	cout << left << setw(12) << "Name " << right << setw(10) << "Girl Rank " << right << setw(10) << "Frequency " << left << setw(11) << right << setw(10) << "Boy Rank " << right << setw(10) << "Frequency " << endl;
	cout << endl;
        
//loop runs as long as a name is being entered and prints 
//out the information
	while(cin >> name){
		findm = searchNames(mnames, name);
		findf = searchNames(fnames, name);
			if(findm == -1 && findf == -1){
				cout << left << setw(11) << name << right << setw(10) << "---" << right << setw(10) << "---" << left << setw(11) << right << setw(10) << "---" << right << setw(10) << "---" << endl;
				cout << endl;
			}
			else if(findf == -1){
				cout << left << setw(11) << name << right << setw(10) << "---" << right << setw(10) << "---" << left << setw(11) << right << setw(10) << (findm+1) << right << setw(10) << mfreq[findm] << endl;
				cout << endl;
			}
			else if(findm == -1){
				cout << left << setw(11) << name << right << setw(10) << (findf+1) << right << setw(10) << ffreq[findf] << left << setw(11) << right << setw(10) << "---" << right << setw(10) << "---" << endl;
				cout << endl;
			}
			else{
				cout << left << setw(11) << name << right << setw(10) << (findf+1) << right << setw(10) << ffreq[findf] << left << setw(11) << right << setw(10) << (findm+1) << right << setw(10) << mfreq[findm] << endl;
				cout << endl;
			}
			if(name == "Quit")
				break;
	}//end of while
	
	fin.close();
	return 0;

}//end of main

//function declaration
void printTopNames(const vector<string> &mnames, const vector<string> &fnames, const vector<int> &mfreq, const vector<int> &ffreq, int topnames, ofstream& fout){
   int mcount=0, gcount=0;
 
   fout << topnames << " Most Popular Boys and Girls Names" << endl;
   fout << endl;
   fout << left << setw(10) << "Girls" << right << setw(10) << "Frequency" << "    " << left << setw(10) << "Boys" << right << setw(10) << "Frequency"<< endl;

   if(mnames.size() < fnames.size() && mnames.size() < topnames)
      topnames = mnames.size();
   if(fnames.size() < mnames.size() && fnames.size() < topnames)
      topnames = fnames.size();
   if(topnames < mnames.size() && topnames < fnames.size())
      topnames = topnames;

	if(topnames > mnames.size())
		topnames = mnames.size();
	if(topnames > fnames.size())
		topnames = fnames.size();

   for(int i = 0; i < topnames; i++){
       fout << left << setw(10) << fnames[i] << right << setw(10) << ffreq[i] << "    " << left << setw(10) << mnames[i] << right << setw(10) << mfreq[i] << endl;
   }//end of for loop
}//end of printTopNames

//searches through vector until it finds name
//once it finds name it returns its index
int searchNames(vector <string> &names, string name){
	for(int i = 0; i < names.size(); i++){
		if(names[i] == name){
			return i;
		}//end of if
	}//end of for loop
        return -1;
}//end of searchNames