# benchmark
This project contains some basic tools for benchmarking C++ code.  
These tools are thought to be simple to understand and to use

## Usage
Here is an example of the use of this library:
```C++
#include <algorithm>
#include <iostream>
#include <vector>

#include "Bench.hpp"

// function that doubles every element in a vector
template <typename T>
T accumulate(const std::vector<T>& vec) {
  T result{};
  for (const auto x : vec) {
	result += x;
  }

  return result;
}

int main() {
  const int N{1000000};

  // generate a vector and fill it with random elements
  std::vector<int> v(N);
  std::ranges::for_each(v, [](auto& x) { x = std::rand(); });

  // benchmark the double function
  const int n_rep{1000};
  sb::Bench<long long int> b(n_rep);
  b.benchmark(accumulate<int>, v);
  b.print<sb::microseconds>();
}
```
