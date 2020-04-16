#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

bool debounce(std::chrono::milliseconds timeout, bool (*handler)(void)) {
  bool prev = handler();
  auto ts = std::chrono::steady_clock::now();
  while (true) {
    std::this_thread::sleep_for(1ms);
    bool value = handler();
    auto now = std::chrono::steady_clock::now();
    if (value == prev) {
      if (now - ts > timeout) {
        break;
      }
    } else {
      prev = value;
      ts = now;
    }
  }
  return prev;
}


int main() {
  bool result = debounce(10ms, []() {
    return true;
  });
  std::cout << "Result: " << result << std::endl;
}
