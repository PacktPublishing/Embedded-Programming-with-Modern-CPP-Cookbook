#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void sleep_for(int count, auto delay) {
  for (int i = 0; i < count; i++) {
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(delay);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> delta = end - start;
    std::cout << "Sleep for: " << delta.count() << std::endl;
  }
}

void sleep_until(int count, std::chrono::milliseconds delay) {
  auto wake_up = std::chrono::system_clock::now();
  for (int i = 0; i < 10; i++) {
    wake_up += delay;
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_until(wake_up);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> delta = end - start;
    std::cout << "Sleep until: " << delta.count() << std::endl;
  }
}

int main() {
  sleep_for(10, 100ms);
  sleep_until(10, 100ms);
	return 0;
}
