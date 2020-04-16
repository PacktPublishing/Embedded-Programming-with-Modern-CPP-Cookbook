#include <iostream>

class Error {
  int code;

  public:
    Error(int code): code(code) {
      std::cout << " Error instance " << code << " was created" << std::endl;
    }
    Error(const Error& other): code(other.code) {
      std::cout << " Error instance " << code << " was cloned" << std::endl;
    }
    ~Error() {
      std::cout << " Error instance " << code << " was destroyed" << std::endl;
    }
};

void CatchByValue() {
  std::cout << "Catch by value" << std::endl;
  try {
    throw Error(1);
  }
  catch (Error e) {
    std::cout << " Error caught" << std::endl;
  }
}

void CatchByPointer() {
  std::cout << "Catch by pointer" << std::endl;
  try {
    throw new Error(2);
  }
  catch (Error* e) {
    std::cout << " Error caught" << std::endl;
  }
}

void CatchByReference() {
  std::cout << "Catch by reference" << std::endl;
  try {
    throw Error(3);
  }
  catch (const Error& e) {
    std::cout << " Error caught" << std::endl;
  }
}


int main() {
  CatchByValue();
  CatchByPointer();
  CatchByReference();
	return 0;
}
