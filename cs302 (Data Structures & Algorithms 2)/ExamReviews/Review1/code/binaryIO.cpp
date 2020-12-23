#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [input] [output]\n", argv[0]);
        return 1;
    }

    FILE *fin  = fopen(argv[1], "rb"),
         *fout = fopen(argv[2], "wb");

    if (!fin) {
        fprintf(stderr, "Could not open input file '%s'!\n", argv[1]);
        return 1;
    }

    if (!fout) {
        fprintf(stderr, "Could not open output file '%s'!\n", argv[2]);
        return 1;
    }

    unsigned char *data;
    unsigned long int size;

    fseek(fin, 0, SEEK_END);
    size = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    data = new unsigned char[size];

    fread(data, 1, size, fin);
    fclose(fin);

    fwrite(data, 1, size, fout);
    fclose(fout);

    delete [] data;
}

