#include <vector>
#include <algorithm>

class ring_buffer {
public:
  ring_buffer(int len) : pos(0), v(len, 0) {}

  void insert(int value) {
    v[pos] = value;
    ++pos;
    pos %= v.size();
  }

  void clear() { std::fill(v.begin(), v.end(), 0); }
  int sum() { return std::accumulate(v.begin(), v.end(), static_cast<int>(0)); }

private:
  int pos;
  std::vector<int> v;
};


