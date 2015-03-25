#include "reader.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <map>

#define BUFF_SIZE 4096

using AMOS::Overlap;
using std::string;
using std::map;
using std::cerr;
using std::cout;

namespace ASQG {

  int get_overlaps(std::vector<Overlap*>& container, std::istream& in) {
    int records = 0;

    int buff_size = BUFF_SIZE/2;
    char *line = new char[buff_size];

    map<string, int> read_id;

    while (!in.eof()) {
      in.getline(line, buff_size);
      while (in.fail()) {
        delete[] line;
        buff_size *= 2;
        line = new char[buff_size];
        in.getline(line, buff_size);
      }

      string type;
      in >> type;

      if (type == "VT") {
        string read_name;
        in >> read_name;
        assert(!in.fail());

        read_id[read_name] = read_id.size() + 1;
      } else if (type == "ED") {
        string read1, read2;
        int start1, end1, len1;
        int start2, end2, len2, orientation2;
        int diff;
        in >> read1 >> read2 >> start1 >> end1 >> len1 >> start2 >> end2 >> len2 >> orientation2 >> diff;
        assert(!in.fail());

        assert(read_id.count(read1) && read_id.count(read2));
        int r1 = read_id[read1], r2 = read_id[read2];
        int scr = (len1 + len2)/2 - diff;
        container.push_back(new Overlap(r1, r2, orientation2, start1, end1+1, len1, start2, end2+1, len2, scr));

        ++records;
      }
    }

    return records;
  }
}
