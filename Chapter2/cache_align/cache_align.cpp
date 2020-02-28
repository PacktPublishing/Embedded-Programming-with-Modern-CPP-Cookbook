#include <stdlib.h>
#include <stdio.h>

constexpr int kAlignSize = 128;
constexpr int kAllocBytes = 256;

constexpr int overlap(void* ptr) {
  size_t addr = (size_t)ptr;
  return addr & (kAlignSize - 1);
}

int main() {
  char static_buffer[kAllocBytes];
  char* dynamic_buffer = new char[kAllocBytes];
  printf("Static buffer address: %p (%d)\n", static_buffer,
         overlap(static_buffer));
  printf("Dynamic buffer address: %p (%d)\n", dynamic_buffer,
         overlap(dynamic_buffer));
  delete[] dynamic_buffer;

  alignas(kAlignSize) char aligned_static_buffer[kAllocBytes];
  char* aligned_dynamic_buffer = nullptr;
  if (posix_memalign((void**)&aligned_dynamic_buffer,
      kAlignSize, kAllocBytes)) {
    printf("Failed to allocate aligned memory buffer\n");
  }
  printf("Aligned static buffer address: %p (%d)\n", aligned_static_buffer,
         overlap(aligned_static_buffer));
  printf("Aligned dynamic buffer address: %p (%d)\n", aligned_dynamic_buffer,
         overlap(aligned_dynamic_buffer));
  free(aligned_dynamic_buffer);
  return 0;
}
