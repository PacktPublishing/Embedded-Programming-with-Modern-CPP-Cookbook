#include <iostream>

void StoreData(const char* buffer, size_t size) {
  std::cout << "Store " << size << " bytes of data" << std::endl;
}

int main() {
  char data[] = "Hello,\x1b\a\x03world!";
  const char *buffer = data;
  std::cout << "Size of buffer pointer is " << sizeof(buffer) << std::endl;
  std::cout << "Size of int is " << sizeof(int) << std::endl;
  std::cout << "Size of size_t is " << sizeof(size_t) << std::endl;
  StoreData(data, sizeof(data));
  return 0;
}
