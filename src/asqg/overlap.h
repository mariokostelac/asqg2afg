#ifndef _ASQG_OVERLAP_H
#define _ASQG_OVERLAP_H

#include <string>
using std::string;

namespace ASQG {

  class Overlap {
    public:
      string read1;
      string read2;
      int start1;
      int end1;
      int len1;
      int start2;
      int end2;
      int len2;
      bool second_reversed;
      int diff;

      Overlap(const string read1, const string read2, const int start1, const int end1, const int len1,
          const int start2, const int end2, const int len2, bool second_reversed, int diff)
        :read1(read1), read2(read2), start1(start1), end1(end1), len1(len1),
        start2(start2), end2(end2), len2(len2), second_reversed(second_reversed), diff(diff)
    {}
  };
}
#endif
