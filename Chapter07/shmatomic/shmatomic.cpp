#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

const char* kSharedMemPath = "/sample_point";

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
  std::atomic_bool data_ready;
  std::atomic_bool data_processed;
  int index;
};


void producer() {
  SharedMem<Payload> writer(kSharedMemPath);
  Payload& pw = writer.get();
  if (!pw.data_ready.is_lock_free()) {
    throw std::runtime_error("Timestamp is not lock-free");
  }
  for (int i = 0; i < 10; i++) {
    pw.data_processed.store(false);
    pw.index = i;
    pw.data_ready.store(true);
    while(!pw.data_processed.load());
  }
}

void consumer() {
  SharedMem<Payload> point_reader(kSharedMemPath, true);
  Payload& pr = point_reader.get();
  if (!pr.data_ready.is_lock_free()) {
    throw std::runtime_error("Timestamp is not lock-free");
  }
  for (int i = 0; i < 10; i++) {
    while(!pr.data_ready.load());
    pr.data_ready.store(false);
    std::cout << "Processing data chunk " << pr.index << std::endl;
    pr.data_processed.store(true);
  }
}

int main() {

  if (fork()) {
    consumer();
  } else {
    producer();
  }
}
