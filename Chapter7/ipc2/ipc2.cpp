#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

std::string kSharedFile = "/tmp/test.fifo";

template<class T>
class Writer {
  private:
    std::ofstream out;
  public:
    Writer(std::string& name):
      out(name, std::ofstream::binary) {}

    void Write(const T& data) {
      out.write(reinterpret_cast<const char*>(&data), sizeof(T));
      out.flush();
    }
};

template<class T>
class Reader {
  private:
    std::ifstream in;
  public:
    Reader(std::string& name):
      in(name, std::ofstream::binary) {}

    T Read() {
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
}

void DoWrites() {
  std::vector<Message> messages {{1, 0}, {0, 1}, {1, 1}, {0, 0}};
  Writer<Message> writer(kSharedFile);
  for (const auto& m : messages) { 
    std::cout << "Write " << m << std::endl;
    writer.Write(m);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
  int ret = mkfifo(kSharedFile.c_str(), 0600);
  if (!ret) {
    throw std::runtime_error("Failed to create named pipe");
  } 
  if (fork()) {
    DoWrites();
  } else {
    DoReads();
  }
}
