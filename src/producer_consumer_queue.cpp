#include <iostream>
#include <thread>
#include <array>
#include <vector>
#include <mutex>
#include <string>
#include <condition_variable>
#include <queue>
#include <algorithm>

using namespace std;

mutex mtx;
condition_variable producer_cv, consumer_cv;
queue<int> buffer;

const int BUFFER_SIZE = 10;
const int MAX_ITERATION = 100;
int iteration_counter = 0;

void consumer_thread(int id) {
    for (int i = 0; i < 2500; i++) {
        unique_lock<mutex> lk(mtx);
        if (!buffer.empty()) {
            cout << "Consumer " << id << " ate " << buffer.front() << endl;
            buffer.pop();
            producer_cv.notify_all();
        } else {
            cout << "*** Consumer " << id << " is waiting" << endl;
            consumer_cv.wait(lk, []{ return !buffer.empty(); });
        }
        iteration_counter++;
    }
}

void producer_thread(int id) {
    for (int i = 0; i < 10000; i++) {
        unique_lock<mutex> lk(mtx);
        if (buffer.size() < BUFFER_SIZE) {
            int a = random() % 400;
            cout << "Producer " << id << " produced: " << a << endl;

            buffer.push(a);
            consumer_cv.notify_all();
        } else {
            cout << "### Producer " << id << " is waiting" << endl;
            producer_cv.wait(lk, []{ return buffer.size() < BUFFER_SIZE; });
        }
    }
}

int main()
{
    const int consumers_count = 5;
    const int producers_count = 3;

    vector<thread> producers;
    vector<thread> consumers;
    for (int i = 0; i < consumers_count; i++)
        consumers.push_back(thread(consumer_thread, i + 1));
    for (int i = 0; i < producers_count; i++)
        producers.push_back(thread(producer_thread, i + 1));

    for (int i = 0; i < consumers_count; i++)
        consumers.at(i).join();
    for (int i = 0; i < producers_count; i++)
        producers.at(i).join();

    return 0;
}