#include <iostream>

int main() {
  union {
    uint32_t i;
    uint8_t c[4];
  } data;
  data.i = 0x01020304;
  if (data.c[0] == 0x01) {
    std::cout << "Big-endian" << std::endl;
  } else {
    std::cout << "Little-endian" << std::endl;
  }
}
