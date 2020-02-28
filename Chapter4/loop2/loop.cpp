#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include <syslog.h>

void runner(std::chrono::milliseconds limit,
            std::function<void(int)> fn,
            int value) {
  auto start = std::chrono::system_clock::now();
  fn(value);
  auto end = std::chrono::system_clock::now();
  std::chrono::milliseconds delta =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  syslog(LOG_DEBUG, "Delta is %ld", delta);
  if (delta > limit) {
    syslog(LOG_ERR, "Execution time %ld ms exceeded %ld ms limit",
           delta.count(), limit.count());
    throw std::runtime_error("Time limit exceeded");
  }
}

void delay_ms(int count) {
  for (int i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::microseconds(1050));
  }
}


int main() {
  openlog("loop3", LOG_PERROR, LOG_USER);
  int max_delay = 10;
  for (int i = 0; i < max_delay; i++) {
    runner(std::chrono::milliseconds(max_delay), delay_ms, i);
  }
  closelog();
  return 0;
}
