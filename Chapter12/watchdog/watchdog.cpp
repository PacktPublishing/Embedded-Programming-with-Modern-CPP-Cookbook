#include <chrono>
#include <iostream>
#include <thread>

#include <unistd.h>

using namespace std::chrono_literals;

class Watchdog {
  std::chrono::seconds seconds;

  public:
    Watchdog(std::chrono::seconds seconds):
      seconds(seconds) {
        feed();
    }

    ~Watchdog() {
      alarm(0);
    }

    void feed() {
      alarm(seconds.count());
    }
};

int main() {
  Watchdog watchdog(2s);
  std::chrono::milliseconds delay = 700ms;
  for (int i = 0; i < 10; i++) {
    watchdog.feed();
    std::cout << delay.count() << "ms delay" << std::endl;
    std::this_thread::sleep_for(delay);
    delay += 300ms;
  }
  return 0;
}
