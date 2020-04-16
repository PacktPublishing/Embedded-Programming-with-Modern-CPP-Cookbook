#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex m;
std::condition_variable cv;
std::vector<int> result;
int next = 0;

void worker(int index) {
  for (int i = 0; i < 10; i++) {
    std::unique_lock<std::mutex> l(m);
    cv.wait(l, [=]{return next == index; });
    std::cout << "worker " << index << "\n";
    result.push_back(index);
    next = next + 1;
    if (next > 2) { next = 1; };
    cv.notify_all();
  }
}

int main() {
  std::thread worker1(worker, 1);
  std::thread worker2(worker, 2);
  {
    std::lock_guard<std::mutex> l(m);
    next = 1;
  }
  std::cout << "Start\n";
  cv.notify_all();
  worker1.join();
  worker2.join();
  for (int e : result) {
    std::cout << e << ' ';
  }
  std::cout << std::endl;
}
