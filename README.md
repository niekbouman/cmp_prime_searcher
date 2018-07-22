# cmp_prime_searcher
Search for prime numbers that enable small-range secure comparisons

# requirements
- a C++17 compiler
- FLINT library for number theory
- GMP (header files)
- CMake
- Ninja build system

# installation
Please clone project with --recursive option to also clone the submodules

    git clone --recursive https://github.com/niekbouman/cmp_prime_searcher.git
    cd cmp_prime_searcher
    ./create_build
    cd _build
    ninja

# running

    ./searcher <search offset> <k> <D0> <Dk>
        
Example:

    ./searcher 0 1 10 100

will give the following output: 
(format:  bit-length & prime & d_k(prime) )

    19 & 333791 & 109
    21 & 1884791 & 129
    22 & 2817239 & 140
    24 & 10522511 & 149
    25 & 25155191 & 156
    25 & 29036999 & 157
    27 & 79107311 & 179
    27 & 89658791 & 217
    30 & 927633671 & 227
    31 & 1514970551 & 276
    ...

(c) 2018 Niek J Bouman
