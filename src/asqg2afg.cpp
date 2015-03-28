#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <cstdlib>
#include "amos/overlap.h"
#include "asqg/reader.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ifstream;
using std::map;

int main(int argc, char **argv) {

  if (argc <= 1) {
    cerr << "Usage: " << argv[0] << " graph.asqg" << endl;
    exit(1);
  }

  vector<ASQG::Read*> reads;
  vector<ASQG::Overlap*> overlaps;

  ifstream file(argv[1], std::ifstream::in);
  if (file.fail()) {
    cerr << "Error ocurred while opening the file" << endl;
    exit(1);
  }

  int reads_len = ASQG::get_reads(reads, file);
  cerr << "Read " << reads_len << " reads" << endl;

  file.clear();
  file.seekg(0, std::ios::beg);

  int overlaps_len = ASQG::get_overlaps(overlaps, file);
  cerr << "Read " << overlaps_len << " overlaps" << endl;

  file.close();

  // assign read ids (starting from 1)
  int last_read_id = 0;
  map<string, int> read_id;
  for (int i = 0; i < reads.size(); ++i) {
    const auto& curr_read = reads[i];
    read_id[curr_read->key] = ++last_read_id;
  }

  // convert ASQG overlaps to AMOS overlaps
  for (int i = 0; i < overlaps.size(); ++i) {
    const auto& curr_overlap = overlaps[i];
    assert(read_id.count(curr_overlap->read1) && read_id.count(curr_overlap->read2));

    // +1 because Amos considers ends as exclusive limit
    int r1 = read_id[curr_overlap->read1];
    int r2 = read_id[curr_overlap->read2];
    int start1 = curr_overlap->start1;
    int end1 = curr_overlap->end1 + 1;
    int len1 = curr_overlap->len1;
    int start2 = curr_overlap->start2;
    int end2 = curr_overlap->end2 + 1;
    int len2 = curr_overlap->len2;

    if (curr_overlap->second_reversed) {
      start2 = len2 - start2;
      end2 = len2 - end2;
      std::swap(start2, end2);
    }

    AMOS::Overlap converted(r1, r2, curr_overlap->second_reversed, start1, end1, len1, start2, end2, len2, 0);
    cout << converted;
  }

  return 0;
}
