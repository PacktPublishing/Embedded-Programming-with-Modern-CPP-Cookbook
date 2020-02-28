#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

const char* kSharedMemPath = "/sample_point";
const size_t kPayloadSize = 16;

using namespace std::literals;

template<class T>
class SharedMem {
  int fd;
  T* ptr;
  const char* name;

  public:
    SharedMem(const char* name, bool owner=false) {
      fd = shm_open(name, O_RDWR | O_CREAT, 0600);
      if (fd == -1) {
        throw std::runtime_error("Failed to open a shared memory region");
      }
      if (ftruncate(fd, sizeof(T)) < 0) {
        close(fd);
        throw std::runtime_error("Failed to set size of a shared memory region");
      };
      ptr = (T*)mmap(nullptr, sizeof(T), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
      if (!ptr) {
        close(fd);
        throw std::runtime_error("Failed to mmap a shared memory region");
      }
      this->name = owner ? name : nullptr;
      std::cout << "Opened shared mem instance " << name << std::endl;
    }

    ~SharedMem() {
      munmap(ptr, sizeof(T));
      close(fd);
      if (name) {
        std::cout << "Remove shared mem instance " << name << std::endl;
        shm_unlink(name);
      }
    }

    T& get() const {
      return *ptr;
    }
};


struct Payload {
  uint32_t index;
  uint8_t raw[kPayloadSize];
};


void producer() {
  SharedMem<Payload> writer(kSharedMemPath);
  Payload& pw = writer.get();
  for (int i = 0; i < 5; i++) {
    pw.index = i;
    std::fill_n(pw.raw, sizeof(pw.raw) - 1, 'a' + i);
    pw.raw[sizeof(pw.raw) - 1] = '\0';
    std::this_thread::sleep_for(150ms);
  }
}

void consumer() {
  SharedMem<Payload> point_reader(kSharedMemPath, true);
  Payload& pr = point_reader.get();
  for (int i = 0; i < 10; i++) {
    std::cout << "Read data frame " << pr.index << ": " << pr.raw << std::endl;
    std::this_thread::sleep_for(100ms);
  }
}

int main() {

  if (fork()) {
    consumer();
  } else {
    producer();
  }
}
