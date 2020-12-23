#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " [input] [output]\n";
        exit(1);
    }

    ifstream fin;
    ofstream fout;

    fin.open(argv[1]);
    fout.open(argv[2]);

    if (!fin.is_open()) {
        cerr << "Could not open input file '" << argv[1] << "'!\n";
        exit(1);
    }

    if (!fout.is_open()) {
        cerr << "Could not open output file '" << argv[2] << "'!\n";
    }

    string line;

    while (getline(fin, line))
        fout << line << endl;

    fin.close();
    fout.close();

}