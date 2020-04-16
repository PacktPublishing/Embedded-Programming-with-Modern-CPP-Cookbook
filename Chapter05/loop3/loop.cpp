#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <cstdarg>


#ifdef DEBUG
#define LOG_DEBUG(fmt, args...) fprintf(stderr, fmt, args)
#else
#define LOG_DEBUG(fmt, args...)
#endif


void runner(std::chrono::milliseconds limit,
            std::function<void(int)> fn,
            int value) {
  auto start = std::chrono::system_clock::now();
  fn(value);
  auto end = std::chrono::system_clock::now();
  std::chrono::milliseconds delta =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  LOG_DEBUG("Delay: %ld ms, max: %ld ms\n", 
            static_cast<long int>(delta.count()),
	          static_cast<long int>(limit.count()));
  if (delta > limit) {
    throw std::runtime_error("Time limit exceeded");
  }
}

void delay_ms(int count) {
  for (int i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::microseconds(1050));
  }
}


int main() {
  int max_delay = 10;
  for (int i = 0; i < max_delay; i++) {
    runner(std::chrono::milliseconds(max_delay), delay_ms, i);
  }
  return 0;
}
