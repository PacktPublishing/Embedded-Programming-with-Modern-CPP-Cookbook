#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

auto touched = std::chrono::steady_clock::now();
std::mutex m;
std::atomic_bool ready{ false };

void Worker() {
  for (int i = 0; i < 10; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + (i % 4) * 10));
    std::cout << "Step " << i << std::endl;
    {
      std::lock_guard<std::mutex> l(m);
      touched = std::chrono::steady_clock::now();
    }
  }
  ready = true;
}


int main() {
  std::thread t(Worker);
  std::chrono::milliseconds threshold(120);
  while(!ready) {
    auto now = std::chrono::steady_clock::now();
    std::chrono::milliseconds delta;
    {
      std::lock_guard<std::mutex> l(m);
      auto delta = now - touched;
      if (delta > threshold) {
        std::cout << "Executiuon threshold exceeded" << std::endl;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
  }
  t.join();
	return 0;
}
