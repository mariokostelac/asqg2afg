#ifndef _ASQG_READ_H
#define _ASQG_READ_H

namespace ASQG {

  class Read {
    public:
      string key;
      string seq;

      Read(const string key, const string seq): key(key), seq(seq) {}
  };
}
#endif
