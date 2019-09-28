#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " [input] [output]\n";
        return 1;
    }

    ifstream fin;
    ofstream fout;

    fin.open(argv[1]);
    fout.open(argv[2]);

    if (!fin.is_open()) {
        cerr << "Could not open input file '" << argv[1] << "'!\n";
        return 1;
    }

    if (!fout.is_open()) {
        cerr << "Could not open output file '" << argv[2] << "'!\n";
        return 1;
    }

    unsigned char *data;
    unsigned long int size;

    fin.seekg(fin.end);
    size = fin.tellg();
    fin.seekg(fin.beg);

    data = new unsigned char[size];

    fin.read((char *) data, size);

    fout.write((char *) data, size);

    fin.close();
    fout.close();

    delete [] data;
}

