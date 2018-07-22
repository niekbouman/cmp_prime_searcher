#ifndef NUMBERGEN_HPP
#define NUMBERGEN_HPP 

#include <vector>

struct number_generator {
  number_generator(uint64_t NN, uint64_t start, std::vector<int>&&j)
      : N(NN), base(start), ptr(0), jump_list(std::move(j)) {}

  inline uint64_t next() {
    if (ptr == jump_list.size()) {
      ptr = 0;
      base += N;
    }
    return base + jump_list[ptr++];
  }

  uint64_t N;
  uint64_t base;
  uint64_t ptr;
  std::vector<int> jump_list;
};

#endif
