#include <iostream>

template<class T, size_t N>
class RingBuffer {
  private:
    T objects[N];
    size_t read;
    size_t write;
    size_t queued;
  public:
    RingBuffer(): read(0), write(0), queued(0) {}

    T& push() {
      T& current = objects[write];
      write = (write + 1) % N;
      queued++;
      if (queued > N) {
        queued = N;
        read = write;
      }
      return current;
    }

    const T& pull() {
      if (!queued) {
        throw std::runtime_error("No data in the ring buffer");
      }
      T& current = objects[read];
      read = (read + 1) % N;
      queued--;
      return current;
    }

    bool has_data() {
      return queued != 0;
    }
};

struct Frame {
  uint32_t index;
  uint8_t  data[1024];
};

int main() {
  RingBuffer<Frame, 10> frames;

  std::cout << "Frames " << (frames.has_data() ? "" : "do not ")
      << "contain data" << std::endl;
  try {
    const Frame& frame = frames.pull();
  } catch (std::runtime_error e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (size_t i = 0; i < 5; i++) {
    Frame& out = frames.push();
    out.index = i;
    out.data[0] = 'a' + i;
    out.data[1] = '\0';
  }
  std::cout << "Frames " << (frames.has_data() ? "" : "do not ")
      << "contain data" << std::endl;
  while (frames.has_data()) {
    const Frame& in = frames.pull();
    std::cout << "Frame " << in.index << ": " << in.data << std::endl;
  }

  for (size_t i = 0; i < 26; i++) {
    Frame& out = frames.push();
    out.index = i;
    out.data[0] = 'a' + i;
    out.data[1] = '\0';
  }
  std::cout << "Frames " << (frames.has_data() ? "" : "do not ")
      << "contain data" << std::endl;
  while (frames.has_data()) {
    const Frame& in = frames.pull();
    std::cout << "Frame " << in.index << ": " << in.data << std::endl;
  }
}
