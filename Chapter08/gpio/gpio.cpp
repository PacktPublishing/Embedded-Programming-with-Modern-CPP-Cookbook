#include <chrono>
#include <iostream>
#include <thread>

#include <wiringPi.h>

using namespace std::literals::chrono_literals;

const int kLedPin = 0;

int main (void)
{

  if (wiringPiSetup () <0) {
    throw std::runtime_error("Failed to initialize wiringPi");
	}

  pinMode (kLedPin, OUTPUT);

  while (true) {
    digitalWrite (kLedPin, HIGH);
		std::cout << "LED on" << std::endl;
    std::this_thread::sleep_for(500ms) ;
    digitalWrite (kLedPin, LOW);
		std::cout << "LED off" << std::endl;
    std::this_thread::sleep_for(500ms) ;
  }
  return 0 ;
}
