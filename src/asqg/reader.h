#ifndef _ASQG_READER_H
#define _ASQG_READER_H

#include "overlap.h"
#include "read.h"

#include <cstdio>
#include <iostream>
#include <vector>

namespace ASQG {
  int get_overlaps(std::vector<Overlap*>& container, std::istream& in);
  int get_reads(std::vector<Read*>& container, std::istream& in);
}

#endif
