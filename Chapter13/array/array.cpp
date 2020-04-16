#include <algorithm>
#include <array>
#include <iostream>
#include <random>

using DataFrame = std::array<uint32_t, 8>;

void GenerateData(DataFrame& frame) {
  std::random_device rd;
  std::generate(frame.begin(), frame.end(),
      [&rd]() { return rd() % 100; });
}

void ProcessData(const DataFrame& frame) {
  std::cout << "Processing array of "
            << frame.size() << " elements: [";
  for (auto x : frame) {
    std::cout << x << " ";
  }
  auto mm = std::minmax_element(frame.begin(), frame.end());
  std::cout << "] min: " << *mm.first
            << ", max: " << *mm.second << std::endl;
}

int main() {
  DataFrame data;

  for (int i = 0; i < 4; i++) {
    GenerateData(data);
    ProcessData(data);
  }
  return 0; 
}
