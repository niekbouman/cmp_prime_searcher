#include "related.hpp"
#include <cppitertools/itertools.hpp>
#include <flint/ulong_extras.h>

bool is_related_pair(int p, int q, int D0, int D1, int jump) {
  std::vector<uint8_t> v(D1 - D0 + jump * 2, 0);
  write_ones(v, p, D0, D1, 1, jump);
  write_ones(v, q, D0, D1, 1, jump);
  return std::find(std::begin(v), std::end(v), 2) != std::end(v);
}

bool is_related_triple(int p, int q, int r, int D0, int D2, int jump) {
  std::vector<uint8_t> v(D2 - D0 + jump * 4, 0);
  write_ones(v, p, D0, D2, 2, jump);
  write_ones(v, q, D0, D2, 2, jump);
  write_ones(v, r, D0, D2, 2, jump);
  return std::find(std::begin(v), std::end(v), 3) != std::end(v);
}

std::vector<int> prime_range(int a, int b) {
  using iter::range;
  using iter::filter;

  std::vector<int> primes;
  for (auto x : range(a, b) | filter([](auto p) { return n_is_probabprime(p); }))
    primes.push_back(x);

  return primes;
}

std::vector<std::vector<int>> related_tuples(int k, int D0, int Dk) {
  using iter::filter;
  using iter::combinations;

  std::vector<std::vector<int>> prime_tups;

  auto primes = prime_range(D0, Dk);
  for (auto &&tup :
       combinations(primes, k + 1) | filter([=](auto &&tupl) {
         return is_related_tuple(std::forward<decltype(tupl)>(tupl), k, D0, Dk);
       }))
    prime_tups.emplace_back(std::vector<int>(tup.cbegin(), tup.cend()));
  return prime_tups;
}

std::vector<std::tuple<int,int>> related_pairs(int D0, int D1, int jump) {
  using iter::filter;
  using iter::combinations;

  std::vector<std::tuple<int, int>> prime_pairs;

  auto primes = prime_range(D0, D1);
  for (auto &&pair : combinations(primes, 2) | filter([=](auto &&pair) {
                       return is_related_pair(pair[0], pair[1], D0, D1, jump); }))
    prime_pairs.push_back(std::make_tuple(pair[0], pair[1]));
  return prime_pairs;
}

std::vector<std::tuple<int,int,int>> related_triples(int D0, int D2, int jump) {
  using iter::filter;
  using iter::combinations;

  std::vector<std::tuple<int, int, int>> prime_triples;

  auto primes = prime_range(D0, D2);
  for (auto &&triplet : combinations(primes, 3) | filter([=](auto &&triple) {
                       return is_related_triple(triple[0], triple[1], triple[2], D0, D2, jump); }))
    prime_triples.push_back(std::make_tuple(triplet[0], triplet[1], triplet[2]));
  return prime_triples;
}

