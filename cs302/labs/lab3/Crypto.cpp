#include <...>
using namespace std;

#include "Support.h"

void encode(...) {
  write this
}

void decode(...) {
  write this
}

int main(int argc, char *argv[]) {
  parse command line arguments
  if something not right,
    print error message and exit

  ppm img;
  img.read(fname);

  if (encode) encode(fname, img);
  else
  if (decode) decode(fname, img);
}
