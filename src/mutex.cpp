#include <thread>      // std::thread
#include <iostream>
#include <mutex>

const int n = 100;
int count = 0;
std::recursive_mutex mutex;


void dummyIncrement() {
    for (int i=0; i<n; i++) {
        std::lock_guard<std::recursive_mutex> guard(mutex);
        std::cout << std::this_thread::get_id() << " , " << count << std::endl;
        count++;
    }
}

int main() {

    std::thread thread_1(dummyIncrement);
    std::thread thread_2(dummyIncrement);

    thread_1.join();
    thread_2.join();

    return 0;
}
