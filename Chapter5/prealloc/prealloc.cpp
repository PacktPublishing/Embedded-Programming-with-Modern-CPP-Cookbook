#include <cstdint>
#include <string.h>

constexpr size_t kMaxFileNameSize = 256;
constexpr size_t kBufferSize = 4096;
constexpr size_t kMaxDevices = 16;

class SerialDevice {
    char device_file_name[256];
    uint8_t input_buffer[kBufferSize];
    uint8_t output_buffer[kBufferSize];
    int file_descriptor;
    size_t input_length;
    size_t output_length;

  public:
    SerialDevice(): 
      file_descriptor(-1), input_length(0), output_length(0) {}

    bool Init(const char* name) {
      strncpy(device_file_name, name, sizeof(device_file_name));
    }

    bool Write(const uint8_t* data, size_t size) {
      if (size > sizeof(output_buffer)) {
        throw "Data size exceeds the limit";
      }
      memcpy(output_buffer, data, size);
    }

    size_t Read(uint8_t* data, size_t size) {
      if (size < input_length) {
        throw "Read buffer is too small";
      }
      memcpy(data, input_buffer, input_length);
      return input_length;
    }
    
};

int main() {
  SerialDevice devices[kMaxDevices];
  size_t number_of_devices = 0;

  uint8_t data[] = "Hello";
  devices[0].Init("test");
  devices[0].Write(data, sizeof(data));

  return 0;
}
