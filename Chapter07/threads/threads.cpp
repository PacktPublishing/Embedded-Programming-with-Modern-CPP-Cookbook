#include <chrono>
#include <iostream>
#include <thread>

void worker(int index) {
  for (int i = 0; i < 10; i++) {
    std::cout << "Worker " << index << " begins" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Worker " << index << " ends" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

int main() {
  std::thread worker1(worker, 1);
  std::thread worker2(worker, 2);
  worker1.join();
  worker2.join();
  std::cout << "Done" << std::endl;
}
