#ifndef CONGRUENCES_HPP
#define CONGRUENCES_HPP

#include <range/v3/all.hpp>
#include <numeric>

std::vector<int> make_residue_set(int p);
std::vector<uint8_t> dense_residue_set(int q);

struct congruences {
  inline void add_congruence(int q) { singletons.push_back(dense_residue_set(q)); }
  inline void add_pair_congruence(int q, int r) {
    pairs.emplace_back(std::make_tuple(dense_residue_set(q), dense_residue_set(r)));
  }

  inline void add_triple_congruence(int q, int r, int s) {
    triples.emplace_back(std::make_tuple(dense_residue_set(q), dense_residue_set(r), dense_residue_set(s)));
  }

  [[gnu::always_inline]]
  inline bool check_singletons(uint64_t p) {
    for (const auto &congruence : singletons) {
      if (congruence[p % congruence.size()] != 1)
        return false;
    }
    return true;
  }

  [[gnu::always_inline]]
  inline bool check_pairs(uint64_t p) {
    for (const auto & [ u, v ] : pairs) {
      if (!(u[p % u.size()] || v[p % v.size()]))
        return false;
    }
    return true;
  }

  [[gnu::always_inline]]
   inline bool check_triples(uint64_t p) {
    for (const auto & [ u, v, w ] : triples) {
      if (!(u[p % u.size()] || v[p % v.size()] || w[p % w.size()]))
        return false;
    }
    return true;
  }

  [[gnu::always_inline]]
  inline bool check(uint64_t p) {
    return check_singletons(p) && check_pairs(p) && check_triples(p);
  }

private:
  std::vector<std::vector<uint8_t>> singletons;
  std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>>> pairs;
  std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>> triples;
};

template <class RngA, class RngB>
auto minkowski_sum(RngA &&A, RngB &&B) {

  using namespace ranges;
  using std::get;

  std::vector<int> v =
      view::cartesian_product(A, B) |
      view::transform([](auto pair) { return get<0>(pair) + get<1>(pair); });
  v |= action::sort | action::unique;
  return v;
}

template <class RngA, class RngB>
auto intersect_congruences(RngA&& A,int p,RngB&& B,int q)
{
  using namespace ranges;
  namespace rng = ranges::v3;

  auto l = std::lcm(p,q);

  std::vector<int> Ain = A;
  std::vector<int> Bin = B;

  std::vector<int> Am = minkowski_sum(Ain, view::ints(0,l/p) | view::transform([p](auto i) { return i * p; }));
  std::vector<int> Bm = minkowski_sum(Bin, view::ints(0,l/q) | view::transform([q](auto i) { return i * q; }));
  std::vector<int> C;
  set_intersection(Am.cbegin(),Am.cend(), Bm.cbegin(), Bm.cend(), rng::back_inserter(C));

  return std::make_tuple(C,l);
}

#endif
