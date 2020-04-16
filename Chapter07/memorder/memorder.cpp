#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> running{true};
std::atomic<int> counter{0};

void worker() {
  while(running) {
    counter.fetch_add(1, std::memory_order_relaxed);
  }
}

int main() {
  std::thread worker1(worker);
  std::thread worker2(worker);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  running = false;
  worker1.join();
  worker2.join();
  std::cout << "Counter: " << counter << std::endl;
}
