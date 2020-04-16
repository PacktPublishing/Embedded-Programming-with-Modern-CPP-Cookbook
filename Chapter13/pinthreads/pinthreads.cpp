#include <ctime>
#include <iostream>
#include <system_error>
#include <thread>

#include <sched.h>

using namespace std::chrono_literals;

bool PinToCore(std::thread& t, int core) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);
    int errCode = pthread_setaffinity_np(t.native_handle(),
                                     sizeof(cpuset), &cpuset);
    if (errCode < 0) {
        std::cerr << "Failed to set CPU affinity:"
                  << errCode << std::endl;
        return false;
    }
    return true;
}

void Worker(int n) {
  while(true) {
    std::clog << "Worker " << n << " running on CPU "
              << sched_getcpu() << std::endl;
    std::this_thread::sleep_for(1s);
  }
}

int main() {
    int n = std::thread::hardware_concurrency();
    std::clog << n << " cores detected" << std::endl;
    //PinToCore(std::this_thread, 0);
    for (int i = 1; i < n; i++) {
      std::clog << "Create worker thread for CPU " << i << std::endl;
      std::thread t = std::thread(Worker, i);
      PinToCore(t, i);
      t.detach();
    }
    std::cout << "Main thread on core " << sched_getcpu() << std::endl;
    for (int i = 0; i < 4; i++) {
      std::clog << "Main thread on cpu " << sched_getcpu() << std::endl;
      std::this_thread::sleep_for(1s);
    }
}
