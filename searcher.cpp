#include "number_gen.hpp"
#include "congruences.hpp"
#include "related.hpp"
#include "ring_buffer.hpp"

#include <cmath>
#include <flint/ulong_extras.h>
#include <iostream>
#include <numeric>
#include <range/v3/algorithm.hpp>
#include <vector>

class searcher {
public:
  searcher(int k_)
      : k(k_), window(2 * k_ + 1){}

  auto find_d_k(uint64_t p) {
    window.clear();
    uint64_t half = (p - 1) / 2;
    for (uint64_t it = 1; it < half; ++it) {
      window.insert(n_jacobi_unsigned(it, p));
      if (window.sum() <= 0) {
        return it - 1 - k;
      }
    }
    return static_cast<uint64_t>(0);
  }

  [[noreturn]] // endless loop, end with Ctrl-C
  void start_search(uint64_t start_prime, int D0, int Dk) {
    using ranges::accumulate;
    using std::get;

    std::vector<int> primes_for_num_gen;
    std::vector<int> remaining_primes;

    auto primes = prime_range(3, D0);

    // use the first six primes to initialize a number generator that generates
    // numbers that satisfy the congruences corresponding to those primes
    //
    // the congruences corresponding to the remaining primes will be checked
    // against the numbers produced by the number generator via the 
    // 'congruences' object

    if (primes.size() > 6) {
      primes_for_num_gen.assign(primes.begin(), primes.begin() + 6);
      remaining_primes.assign(primes.begin(), primes.end());
    } else
      primes_for_num_gen.swap(primes);

    std::tuple<std::vector<int>, int> init_state = {{7}, 8}; // require p to be:    p \equiv 7  (mod 8)

    auto[C, len] = accumulate(primes_for_num_gen, init_state, [](auto &&set_setlen, int prime) {
          return intersect_congruences(get<0>(set_setlen), get<1>(set_setlen),
                                       make_residue_set(prime), prime);
        });
    // intersect the congruence sets that correspond to the primes in primes_for_num_gen into one bit 
    // congruence set by means of a fold

    number_generator numbers(len,(start_prime / static_cast<uint64_t>(len)) * static_cast<uint64_t>(len), std::move(C));
    
    congruences c;

    for (auto prime : remaining_primes)
      c.add_congruence(prime);

    if (k == 1) {
      for (auto[p, q] : related_pairs(D0, Dk))
        c.add_pair_congruence(p, q);
    } else if (k == 2) {
      for (auto[p, q, r] : related_triples(D0, Dk))
        c.add_triple_congruence(p, q, r);
    }

    auto d = 0;
    uint64_t iter = 0;
    uint64_t p;

    while (true) {
      p = numbers.next();

      if (c.check(p) && n_is_probabprime(p)) {
        auto dn = find_d_k(p);
        if (dn > d) {
          d = dn;
          std::cout << std::ceil(std::log2(p)) << " & " << p << " & " << d
                    << std::endl;
        }
      }

      ++iter;
      if (iter % 1000000000 == 0) {
        std::cerr << "iteration: " << iter << ", current prime: " << p
                  << std::endl;
      }
    }
  }

private:
  int k;
  ring_buffer window;
};

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "usage: " << argv[0] << " <search offset> <k> <D0> <Dk>\n";
    return EXIT_FAILURE;
  } else {
    searcher s(std::stoi(argv[2]));
    s.start_search(std::stoull(argv[1]), std::stoi(argv[3]), std::stoi(argv[4]));
    return EXIT_SUCCESS;
  }
}
