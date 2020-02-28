#include <iostream>
#include <system_error>

#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>


class Rtc {
	int fd;
	public:
		Rtc() {
			fd = open("/dev/rtc", O_RDWR);
			if (fd < 0) {
				throw std::system_error(errno,
            std::system_category(),
            "Failed to open RTC device"); 
			}
		}

		~Rtc() {
			close(fd);
		}
		
		time_t GetTime(void) {
      union {
			  struct rtc_time rtc;
        struct tm tm;
      } tm;
			int ret = ioctl(fd, RTC_RD_TIME, &tm.rtc);
			if (ret < 0) {
				throw std::system_error(errno,
            std::system_category(),
            "ioctl failed");
			}
      return mktime(&tm.tm);
		}
};

int main (void)
{
	Rtc rtc;
  time_t t = rtc.GetTime();
	std::cout << "Current time is " << ctime(&t) << std::endl;

  return 0 ;
}
