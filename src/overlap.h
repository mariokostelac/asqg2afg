#ifndef _AMOS_OVERLAP_H
#define _AMOS_OVERLAP_H

#include <cassert>
#include <cstdint>
#include <iostream>

using std::ostream;

namespace AMOS {

  class Overlap {
    public:
      uint32_t read1;
      uint32_t read2;
      char adjacency;
      int32_t a_hang;
      int32_t b_hang;
      uint32_t score;

      // from http://sourceforge.net/p/amos/mailman/message/19965222/.
      //
      // read a      -------------------|-------------->     bhang
      // read b            ahang     ---------------|--------------->
      //
      // read a           -ahang     ---------------|--------------->
      // read b      -------------------|-------------->     -bhang
      Overlap(const uint32_t r1, const uint32_t r2, const char adj, const int32_t ahg, const int32_t bhg, const int32_t scr);

      Overlap(const uint32_t r1, const uint32_t r2, bool second_flipped,
          const int32_t start1, const int32_t end1, const int32_t len1,
          const int32_t start2, const int32_t end2, const int32_t len2,
          const int32_t scr);
  };

  ostream& operator << (ostream &o, const AMOS::Overlap& sol);
}
#endif
