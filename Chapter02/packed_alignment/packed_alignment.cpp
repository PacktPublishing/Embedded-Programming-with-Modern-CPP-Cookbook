#include <iostream>

enum class Category: uint8_t {
  file, directory, socket  
};

struct ObjectMetadata1 {
  uint8_t access_flags;
  uint32_t size;
  uint32_t owner_id;
  Category category;
} __attribute__((packed));

struct ObjectMetadata2 {
  uint32_t size;
  uint32_t owner_id;
  uint8_t access_flags;
  Category category;
} __attribute__((packed));

int main() {
  ObjectMetadata1 object_pool1[1000];
  ObjectMetadata2 object_pool2[1000];
  std::cout << "Poorly aligned:" << sizeof(object_pool1) << std::endl;
  std::cout << "Well aligned:" << sizeof(object_pool2) << std::endl;
  return 0;
}
