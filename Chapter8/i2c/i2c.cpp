#include <thread>
#include <system_error>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

using namespace std::literals::chrono_literals;

enum class Function : uint8_t {
	clear = 0x01,
	home = 0x02,
	entry_mode_set = 0x04,
	display_control = 0x08,
	cursor_shift = 0x10,
	fn_set = 0x20,
	set_ddram_addr = 0x80
};

constexpr int En = 0b00000100;
constexpr int Rs = 0b00000001;

constexpr int kDisplayOn = 0x04;
constexpr int kEntryLeft = 0x02;
constexpr int kTwoLine = 0x08;
constexpr int kBacklightOn = 0x08;

class Lcd {
	int fd;

	public:
		Lcd(const char* device, int address) {
			fd = open(device, O_RDWR);
			if (fd < 0) {
				throw std::system_error(errno,
						std::system_category(),
						"Failed to open RTC device"); 
			}
			if (ioctl(fd, I2C_SLAVE, address) < 0) {
				close(fd);
				throw std::system_error(errno,
						std::system_category(),
						"Failed to aquire bus address"); 
			}
			Init();
		}

		~Lcd() {
			close(fd);
		}

		void Clear() {
			Call(Function::clear);
			std::this_thread::sleep_for(2000us);
		}

		void Display(const std::string& text, bool second=false) {
			Call(Function::set_ddram_addr, second ? 0x40 : 0);
			for(char c : text) {
				Write(c, Rs);
			}	
		}

	private:

		void SendToI2C(uint8_t byte) {
			if (write(fd, &byte, 1) != 1) {
				throw std::system_error(errno,
						std::system_category(),
						"Write to i2c device failed"); 
			}
		}

		void SendToLcd(uint8_t value) {
			value |= kBacklightOn;
			SendToI2C(value);
			SendToI2C(value | En);
			std::this_thread::sleep_for(1us);
			SendToI2C(value & ~En);
			std::this_thread::sleep_for(50us);
		}

		void Write(uint8_t value, uint8_t mode=0) {
			SendToLcd((value & 0xF0) | mode);
			SendToLcd((value << 4) | mode);
		}

		void Init() {
			// Switch to 4-bit mode
			for (int i = 0; i < 3; i++) {
				SendToLcd(0x30);
				std::this_thread::sleep_for(4500us);
			}
			SendToLcd(0x20);

			// Set display to two-line, 4 bit, 5x8 character mode
			Call(Function::fn_set, kTwoLine);
			Call(Function::display_control, kDisplayOn);
      Clear();
      Call(Function::entry_mode_set, kEntryLeft);
			Home();
		}

		void Call(Function function, uint8_t value=0) {
      Write((uint8_t)function | value);
		}

		void Home() {
      Call(Function::home);
			std::this_thread::sleep_for(2000us);
		}
};

int main (int argc, char* argv[])
{
	Lcd lcd("/dev/i2c-1", 0x27);
	if (argc > 1) {
		lcd.Display(argv[1]);
		if (argc > 2) {
			lcd.Display(argv[2], true);
		}
	}

  return 0 ;
}
