#include <thread>      // std::thread
#include <iostream>
#include <mutex>

const int n = 10;
int count = 0;
std::mutex mutex;

void dummyIncrement() {
    std::lock_guard<std::mutex> guard(mutex);
    for(int i=0; i<n; i++) {
        std::cout << std::this_thread::get_id() << " , " << count << std::endl;
        count++;
    }
}

int main() {

    std::cout << "count at start: " << count << std::endl;
    std::thread thread_1(dummyIncrement);
    std::cout << "count after thread_1: " << count << std::endl;
    std::thread thread_2(dummyIncrement);
    std::cout << "count after thread 2: " << count << std::endl;

    thread_1.join();
    thread_2.join();

    return 0;
}