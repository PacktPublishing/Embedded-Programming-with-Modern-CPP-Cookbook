#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include <unistd.h>

std::string kSharedFile = "/tmp/test.bin";

template<class T>
class Writer {
  private:
    std::ofstream out;
  public:
    Writer(std::string& name):
      out(name, std::ofstream::binary) {}

    void Write(const T& data) {
      out.write(reinterpret_cast<const char*>(&data), sizeof(T));
    }
};

template<class T>
class Reader {
  private:
    std::ifstream in;
  public:
    Reader(std::string& name) {
      for(int count=10; count && !in.is_open(); count--) {
        in.open(name, std::ifstream::binary);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    }

    T Read() {
      int count = 10;
      for (;count && in.eof(); count--) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }

      T data;
      in.read(reinterpret_cast<char*>(&data), sizeof(data));
      if (!in) {
        throw std::runtime_error("Failed to read a message");
      }
      return data;
    }
};

struct Message {
  int x, y;
};

std::ostream& operator<<(std::ostream& o, const Message& m) {
  o << "(x=" << m.x << ", y=" << m.y << ")";
  return o;
}

void DoWrites() {
  std::vector<Message> messages {{1, 0}, {0, 1}, {1, 1}, {0, 0}};
  Writer<Message> writer(kSharedFile);
  for (const auto& m : messages) { 
    std::cout << "Write " << m << std::endl;
    writer.Write(m);
  }
}

void DoReads() {
  Reader<Message> reader(kSharedFile);
  try {
    while(true) {
      std::cout << "Read " << reader.Read() << std::endl;
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}


int main(int argc, char** argv) {
  if (fork()) {
    DoWrites();
  } else {
    DoReads();
  }
}
