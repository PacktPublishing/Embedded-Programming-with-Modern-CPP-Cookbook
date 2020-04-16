#include <iostream>
#include <chrono>

int main() {
  auto now = std::chrono::system_clock::now();

  std::time_t ts = std::chrono::system_clock::to_time_t(now);
  std::cout << "POSIX timestamp: " << ts << std::endl;

  auto restored = std::chrono::system_clock::from_time_t(ts);

  std::chrono::duration<double, std::milli> delta = now - restored;
  std::cout << "Recovered time delta " << delta.count() << std::endl;
	return 0;
}
