//check related

#ifndef RELATED_HPP
#define RELATED_HPP 

#include <vector>

template <typename T>
void write_ones(std::vector<T> &v, int p, int D0, int Dk, int k) {
  for (auto m = p; m < Dk; m += p) 
    for (int i = 0; i < 2 * k + 1; ++i)
      v.at(m - D0 + i) += 1;
}

template <typename Iterable>
bool is_related_tuple(Iterable&& primes, int k, int D0, int Dk) {
  std::vector<uint8_t> v(Dk - D0 + 2 * k, 0);
  for (auto p : primes) 
    write_ones(v, p, D0, Dk, k);
  return std::find(std::begin(v), std::end(v), k + 1) != std::end(v);
}

bool is_related_pair(int p, int q, int D0, int D1);
bool is_related_triple(int p, int q, int r, int D0, int D2);

// range of primes in [a,b)
std::vector<int> prime_range(int a, int b);

// list of related prime pairs in [D0, D1)
std::vector<std::tuple<int,int>> related_pairs(int D0, int D1);

// list of related prime triples in [D0, D2)
std::vector<std::tuple<int,int,int>> related_triples(int D0, int D2);

// list of related prime (k+1)-tuples in [D0, Dk)
std::vector<std::vector<int>> related_tuples(int k, int D0, int Dk);

#endif

