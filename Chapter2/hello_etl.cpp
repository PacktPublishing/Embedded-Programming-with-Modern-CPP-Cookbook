#include <iostream>
#include <etl/vector.h>

int main() {
  etl::vector<uint32_t, 10> numbers {1, 2, 3, 4, 5};
  for (auto i: numbers) {
    std::cout << i << std::endl;
  }
  return 0; 
}
