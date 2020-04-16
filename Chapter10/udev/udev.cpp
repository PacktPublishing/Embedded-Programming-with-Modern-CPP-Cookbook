#include <iostream>
#include <functional>

#include <libudev.h>
#include <poll.h>

namespace usb {

class Device {
	struct udev_device *dev;
	
	public:
		Device() = delete;
		Device(struct udev_device* dev) : dev(dev) {}

		Device(const Device& other) : dev(other.dev) {
			udev_device_ref(dev);
		}

		~Device() {
        udev_device_unref(dev);
		}

		std::string action() const { return udev_device_get_action(dev); }

		std::string attr(const char* name) const {
			const char* val = udev_device_get_sysattr_value(dev, name);
			return val ? val : "";
		}
};

class Monitor {
	struct udev_monitor *mon;

	public:
		Monitor() {
    	struct udev* udev = udev_new();
      mon = udev_monitor_new_from_netlink(udev, "udev");
			udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", NULL);
			udev_monitor_enable_receiving(mon);
		}

		Monitor(const Monitor& other) = delete;

		~Monitor() {
			udev_monitor_unref(mon);
		}

		Device wait(std::function<bool(const Device&)> process) {
			struct pollfd fds[1];
			fds[0].events = POLLIN;
			fds[0].fd = udev_monitor_get_fd(mon);

			while (true) {
					int ret = poll(fds, 1, -1);
					if (ret < 0) {
						throw std::system_error(errno, std::system_category(),
								"Poll failed");
					}
					if (ret) {
						Device d(udev_monitor_receive_device(mon));
						if (process(d)) {
							return d;
						};
					}
			}
		}
};
};

int main() {
	usb::Monitor mon;
	usb::Device d = mon.wait([](auto& d) {
		auto id = d.attr("idVendor") + ":" + d.attr("idProduct");
		auto produce = d.attr("product");
		std::cout << "Check [" << id << "] action: " << d.action() << std::endl;
		return d.action() == "bind" && id == "8086:0808";
	});
	std::cout << d.attr("product") << " connected, uses up to "
						<< d.attr("bMaxPower") << std::endl;
	return 0;
}
