#include <ctime>
#include <iostream>
#include <system_error>
#include <thread>

#include <pthread.h>

using namespace std::chrono_literals;

void ConfigureRealtime(pthread_t thread_id, int priority) {
    sched_param sch;
    sch.sched_priority = 20;
    if (pthread_setschedparam(thread_id, SCHED_FIFO, &sch)) {
        throw std::system_error(errno, std::system_category(),
                                "Failed to set real-time priority");
    }
}

void Measure(const char* text) {
    struct timespec prev;
    timespec_get(&prev, TIME_UTC);
    struct timespec delay{0, 10};
    for (int i = 0; i < 100000; i++) {
      nanosleep(&delay, nullptr);
    }
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    double delta = (ts.tv_sec - prev.tv_sec) +  (double)(ts.tv_nsec - prev.tv_nsec) / 1000000000;
    std::clog << text << " completed in " <<  delta << " sec" << std::endl;
}
 
void RealTimeThread(const char* txt) {
    ConfigureRealtime(pthread_self(), 1);
    Measure(txt);
}
 
int main() {
    std::thread t1(RealTimeThread, "Real-time");
    std::thread t2(Measure, "Normal");
    t1.join();
    t2.join();
}
