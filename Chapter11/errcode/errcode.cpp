#include <iostream>

int Receive(int input, std::string& output) {
  if (input < 0) {
    return -1;
  }

  output = "Hello";
  return 0;
}

std::string Receive(int input, int& error) {
  if (input < 0) {
    error = -1;
    return "";
  }
  error = 0;
  return "Hello";
}

std::pair<int, std::string> Receive(int input) {
  std::pair<int, std::string> result;
  if (input < 0) {
    result.first = -1;
  } else {
    result.second = "Hello";
  }
  return result;
}

void Display(const char* prefix, int err, const std::string& result) {
  if (err < 0) {
    std::cout << prefix << " error: " << err << std::endl;
  } else {
    std::cout << prefix << " result: " << result << std::endl;
  }
}

void Test(int input) {
  std::string result;
  int err;

  err = Receive(input, result);
  Display(" Receive 1", err, result);

  result = Receive(input, err);
  Display(" Receive 2", err, result);

  std::pair<int, std::string> ret = Receive(input);
  Display(" Receive 3", ret.first, ret.second);
}


int main() {
  std::cout << "Input: -1" << std::endl;
  Test(-1);
  std::cout << "Input: 1" << std::endl;
  Test(1);

	return 0;
}
