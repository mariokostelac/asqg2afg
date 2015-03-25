#include "overlap.h"
using std::endl;

namespace AMOS {

  Overlap::Overlap(const uint32_t r1, const uint32_t r2, const char adj, const int32_t ahg, const int32_t bhg, const int32_t scr)
    :read1(r1), read2(r2), adjacency(adj), a_hang(ahg), b_hang(bhg), score(scr)
  {}

  // from http://sourceforge.net/p/amos/mailman/message/19965222/.
  //
  // read a      -------------------|-------------->     bhang
  // read b            ahang     ---------------|--------------->
  //
  // read a           -ahang     ---------------|--------------->
  // read b      -------------------|-------------->     -bhang
  Overlap::Overlap(const uint32_t r1, const uint32_t r2, bool second_flipped,
      const int32_t start1, const int32_t end1, const int32_t len1,
      const int32_t start2, const int32_t end2, const int32_t len2,
      const int32_t scr)
    :read1(r1), read2(r2), score(scr)
  {
    adjacency = second_flipped ? 'I' : 'N';

    int overlap_len_a = end1 - start1;
    int overlap_len_b = end2 - start2;

    int a_not_matching = len1 - overlap_len_a;
    int b_not_matching = len2 - overlap_len_b;

    if (start1 == 0 && end1 == len1) {
      // first contained
      a_hang = -start2;
      b_hang = len2 - end2;
    } else if (start2 == 0 && end2 == len2) {
      // second contained
      a_hang = start1;
      b_hang = -(len1 - end1);
    } else if (end1 == len1) {
      // first case from the comment
      a_hang = a_not_matching;
      b_hang = b_not_matching;
    } else if (end2 == len2) {
      // second case from the comment
      a_hang = -b_not_matching;
      b_hang = -a_not_matching;
    } else {
      assert(false);
    }
  }

  ostream& operator << (ostream &o, const AMOS::Overlap& overlap) {
    o << "{OVL" << endl;
    o << "rds:" << overlap.read1 << "," << overlap.read2 << endl;
    o << "adj:" << overlap.adjacency << endl;
    o << "ahg:" << overlap.a_hang << endl;
    o << "bhg:" << overlap.b_hang << endl;
    o << "scr:" << overlap.score << endl;
    o << "}" << endl;
    return o;
  }
}
