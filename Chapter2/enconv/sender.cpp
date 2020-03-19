#include <stdexcept>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

void WriteData(int fd, const void* ptr, size_t size) {
  size_t offset =0;
  while (size) {
    const char *buffer = (const char*)ptr + offset;
    int written = write(fd, buffer, size);
    if (written < 0) {
      throw std::runtime_error("Can not write to file");
    }
    offset += written;
    size -= written;
  }
}

void WriteMessage(int fd, const char* str) {
  uint32_t size = strlen(str);
  uint32_t encoded_size = htonl(size);
  WriteData(fd, &encoded_size, sizeof(encoded_size));
  WriteData(fd, str, size);
}

int main(int argc, char** argv) {
  int fd = open("envconv.data", O_WRONLY|O_APPEND|O_CREAT, 0666);
  for (int i = 1; i < argc; i++) {
    WriteMessage(fd, argv[i]);
  }
}
