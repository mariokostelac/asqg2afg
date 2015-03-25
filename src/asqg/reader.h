#ifndef _ASQG_READER_H
#define _ASQG_READER_H

#include "../amos/overlap.h"

#include <cstdio>
#include <iostream>
#include <vector>

namespace ASQG {
  int get_overlaps(std::vector<AMOS::Overlap*>& container, std::istream& in);
}

#endif
