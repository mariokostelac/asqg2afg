#include "reader.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

#define BUFF_SIZE 4096

using std::string;
using std::stringstream;
using std::cerr;
using std::cout;

namespace ASQG {

  int get_overlaps(std::vector<Overlap*>& container, std::istream& in) {
    int records = 0;

    int buff_size = BUFF_SIZE/2;
    char *line = new char[buff_size];

    while (!in.eof()) {
      in.getline(line, buff_size);
      if (in.eof()) break;
      while (in.fail()) {
        delete[] line;
        buff_size *= 2;
        line = new char[buff_size];
        in.getline(line, buff_size);
      }

      stringstream curr_line(line);

      string type;
      curr_line >> type;

      if (type == "ED") {
        string read1, read2;
        int start1, end1, len1;
        int start2, end2, len2, orientation2;
        int diff;
        curr_line >> read1 >> read2 >> start1 >> end1 >> len1 >> start2 >> end2 >> len2 >> orientation2 >> diff;
        assert(!in.fail());

        container.push_back(new Overlap(read1, read2, start1, end1, len1,
              start2, end2, len2, orientation2, diff));

        ++records;
      }
    }

    return records;
  }

  int get_reads(std::vector<Read*>& container, std::istream& in) {
    int records = 0;

    int buff_size = BUFF_SIZE/2;
    char *line = new char[buff_size];

    while (!in.eof()) {
      in.getline(line, buff_size);
      if (in.eof()) break;
      while (in.fail()) {
        delete[] line;
        buff_size *= 2;
        line = new char[buff_size];
        in.getline(line, buff_size);
      }

      stringstream curr_line(line);

      string type;
      curr_line >> type;

      if (type == "VT") {
        string key, seq;
        curr_line >> key >> seq;
        assert(!in.fail());

        container.push_back(new Read(key, seq));

        ++records;
      }
    }

    return records;
  }
}
