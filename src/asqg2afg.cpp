#include <iostream>
#include <vector>
#include "reader.h"

using AMOS::Overlap;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

int main() {

  vector<Overlap*> overlaps;
  int read = ASQG::get_overlaps(overlaps, cin);

  for (int i = 0; i < read; ++i) {
    cout << *(overlaps[i]);
  }

  cerr << "Read " << read << " overlaps" << endl;

  return 0;
}
