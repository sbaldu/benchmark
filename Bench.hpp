// Header containing some basic functions for benchmarking

#ifndef Bench_hpp
#define Bench_hpp

#include <chrono>
#include <iostream>
#include <ratio>
#include <type_traits>

namespace sb {
  // type of average execution time values
  using Average = long double;

  template <typename T, typename Period>
  using Duration = std::chrono::duration<T, Period>;

  // alias for time units
  using std::chrono::microseconds;
  using std::chrono::milliseconds;
  using std::chrono::nanoseconds;
  using std::chrono::seconds;

  template <typename T, typename Period = std::nano>
  class Timer {
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    Duration<T, Period>* m_duration;

  public:
    Timer(Duration<T, Period>* duration)
        : m_start{std::chrono::high_resolution_clock::now()}, m_duration{duration} {}
    ~Timer() {
      auto finish{std::chrono::high_resolution_clock::now()};
      *m_duration = finish - m_start;
    }
  };

  template <typename T, typename Period = std::nano>
  class Bench {
  private:
    Duration<T, Period> m_duration;
    Average m_avgTime;
    int m_rep;

  public:
    Bench() : m_rep{1} {}
    Bench(int rep) : m_rep{rep} {}

    template <typename F, typename... Tn>
    std::enable_if_t<std::is_invocable_v<F, std::remove_reference_t<Tn>...>, Average>
    benchmark(F func, Tn... args) {
      Duration<T, Period> duration{};

      for (int i{}; i < m_rep; ++i) {
        Timer<T, Period> t(&duration);
        func(args...);
      }

      m_duration = duration;
      m_avgTime = static_cast<Average>(m_duration.count()) / m_rep;
      return m_avgTime;
    }

    Average time() const { return m_avgTime; }
    int reps() const { return m_rep; }

    template <typename P = nanoseconds>
    void print() {
      std::cout << "Average execution time : "
                << std::chrono::duration_cast<P>(m_duration).count() << '\n';
    }
  };
};  // namespace sb

#endif
