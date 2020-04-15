#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<size_t> shared_index{0};
std::vector<int> data;

void worker(int index, int timeout) {
  while(true) {
    size_t worker_index = shared_index.fetch_add(1);
    if (worker_index >= data.size()) {
      break;
    }
    std::cout << "Worker " << index << " handles " << worker_index << std::endl;
    data[worker_index] = data[worker_index] * 2;
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
  }
}

int main() {
  for (int i = 0; i < 10; i++) {
    data.emplace_back(i);
  }
  std::thread worker1(worker, 1, 50);
  std::thread worker2(worker, 2, 20);
  worker1.join();
  worker2.join();
  std::cout << "Result: ";
  for (auto& v : data) {
    std::cout << v << ' ';
  }
  std::cout << std::endl;
}
