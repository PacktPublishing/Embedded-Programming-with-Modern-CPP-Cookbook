#include <iostream>
#include <chrono>

int main() {
  std::chrono::duration<double, std::micro> prev;
  for (int i = 0; i < 10; i++) {
    auto start = std::chrono::steady_clock::now();
    std::cout << i << ": ";
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> delta = end - start;
    std::cout << "output duration is " << delta.count() <<" us";
    if (i) {
      auto diff = (delta - prev).count();
      if (diff >= 0) {
        std::cout << ", " << diff << " us slower";
      } else {
        std::cout << ", " << -diff << " us faster";
      }
    }
    std::cout << std::endl;
    prev = delta;
  }
	return 0;
}
