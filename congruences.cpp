#include "congruences.hpp"

#include <flint/ulong_extras.h>
#include <vector>

std::vector<int> make_residue_set(int p) {
  std::vector<int> v;
  for (auto i = 0; i < p; ++i)
    if (n_jacobi(p - i, p) == 1)
      v.push_back(i);
  return v;
}

std::vector<uint8_t> dense_residue_set(int q) {
  std::vector<uint8_t> data(static_cast<size_t>(q), 0);
  auto v = make_residue_set(q);
  for (auto &pos : v)
    data[pos] = 1;
  return data;
}

