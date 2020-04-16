#include <cassert>
#include <system_error>

#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>

class TimeSaver1 {
  int fd = -1;

public:
  TimeSaver1(const char* name) {
    assert(name != nullptr);
    assert(name[0] != '\0');

    int fd = open(name, O_RDWR|O_CREAT|O_TRUNC, 0600);
    if (fd < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed to open file");
    }
    assert(this->fd >= 0);
  }

  ~TimeSaver1() {
    assert(this->fd >= 0);
    close(fd);
  }
};

int main() {
  TimeSaver1 ts1("");
  return 0; 
}
