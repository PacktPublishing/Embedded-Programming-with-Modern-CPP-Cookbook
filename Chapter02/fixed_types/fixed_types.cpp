#include <iostream>

void SendDataToDevice(void* buffer, uint32_t size) {
  // This is a stub function to send data pointer by
  // buffer.
  std::cout << "Sending data chunk of size " << size << std::endl;
}

int main() {
  char buffer[] = "Hello, world!";
  uint32_t size = sizeof(buffer);
  SendDataToDevice(&size, sizeof(size));
  SendDataToDevice(buffer, size);
  return 0;
}
