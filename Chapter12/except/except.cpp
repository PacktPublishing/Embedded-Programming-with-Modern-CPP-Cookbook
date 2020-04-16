#include <iostream>
#include <system_error>
#include <fcntl.h>
#include <unistd.h>

class Device {
  int fd;

  public:
    Device(const std::string& deviceName) {
      fd = open(deviceName.c_str(), O_RDWR);
      if (fd < 0) {
        throw std::system_error(errno, std::system_category(),
                                "Failed to open device file");
      }
    }

    ~Device() {
      close(fd);
    }

    void Send(const std::string& data) {
      size_t offset = 0;
      size_t len = data.size();
      while (offset < data.size() - 1) {
        int sent = write(fd, data.data() + offset, data.size() - offset);
        if (sent < 0) {
          throw std::system_error(errno, std::system_category(),
                                  "Failed to send data");
        }
        offset += sent;
      } 
    }
};

int main() {
  try {
    Device serial("/dev/ttyUSB0");
    serial.Send("Hello");
  } catch (std::system_error& e) {
    std::cout << "Error: " << e.what() << std::endl;
    std::cout << "Code: " << e.code() << " means \"" << e.code().message()
        << "\"" << std::endl;
  }

	return 0;
}
