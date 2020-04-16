#include <system_error>

#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>

[[nodiscard]] ssize_t Write(int fd, const void* buffer, ssize_t size) {
  return ::write(fd, buffer, size);
}

class TimeSaver1 {
  int fd;

public:
  TimeSaver1(const char* name) {
    int fd = open(name, O_RDWR|O_CREAT|O_TRUNC, 0600);
    if (fd < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed to open file");
    }
    Update();
  }

  ~TimeSaver1() {
    Update();
    close(fd);
  }
  
  
private:
  void Update() {
    time_t tm;
    time(&tm);
    Write(fd, &tm, sizeof(tm));
  }
};

class TimeSaver2 {
  int fd;

public:
  TimeSaver2(const char* name) {
    fd = open(name, O_RDWR|O_CREAT|O_TRUNC, 0600);
    if (fd < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed to open file");
    }
    Update();
  }

  ~TimeSaver2() {
    Update();
    if (close(fd) < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed to close file");
    }
  }
  
private:
  void Update() {
    time_t tm = time(&tm);
    int rv = Write(fd, &tm, sizeof(tm));
    if (rv < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed to write to file");
    }
  }
};

int main() {
  TimeSaver1 ts1("timestamp1.bin");
  TimeSaver2 ts2("timestamp2.bin");
  return 0; 
}
