#include <chrono>
#include <thread>

#include <wiringPi.h>

using namespace std::literals::chrono_literals;

const int kLedPin = 0;

void Blink(std::chrono::microseconds duration, int percent_on) {
    digitalWrite (kLedPin, HIGH);
    std::this_thread::sleep_for(duration * percent_on / 100) ;
    digitalWrite (kLedPin, LOW);
    std::this_thread::sleep_for(duration * (100 - percent_on) / 100) ;
}

int main (void)
{

  if (wiringPiSetup () <0) {
    throw std::runtime_error("Failed to initialize wiringPi");
	}

  pinMode (kLedPin, OUTPUT);

	int count = 0;
	int delta = 1;
  while (true) {
		Blink(10ms, count);
		count = count + delta;
		if (count == 101) {
			delta = -1;
		} else if (count == 0) {
			delta = 1;
		}
  }
  return 0 ;
}
