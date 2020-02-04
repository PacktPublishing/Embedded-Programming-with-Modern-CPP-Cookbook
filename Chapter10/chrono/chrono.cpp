#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

int main() {
  auto a = std::chrono::system_clock::now();
  auto b = a + 1s;
  auto c = a + 200ms;

  std::cout << "a < b ? " << (a < b ? "yes" : "no") << std::endl;
  std::cout << "a < c ? " << (a < c ? "yes" : "no") << std::endl;
  std::cout << "b < c ? " << (b < c ? "yes" : "no") << std::endl;

	return 0;
}
