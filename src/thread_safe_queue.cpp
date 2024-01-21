#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <stdexcept>

#include <chrono>
#include <thread>


template <typename T, typename Alloc = std::allocator<T>>
class ThreadSafeQueue {
private:
    mutable std::mutex mtx;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
    Alloc allocator;
public:
    explicit ThreadSafeQueue(const Alloc& alloc = Alloc()) : allocator(alloc) {}

    ThreadSafeQueue(const ThreadSafeQueue& other) {
        std::scoped_lock lk(other.mtx);
        data_queue = other.data_queue;
    }

    ThreadSafeQueue(ThreadSafeQueue&& other) {
        std::scoped_lock lk(other.mtx);
        data_queue = std::move(other.data_queue);
    }

    ThreadSafeQueue& operator=(const ThreadSafeQueue& other) {
        if (this != &other) {
            std::scoped_lock lk1(mtx);
            std::scoped_lock lk2(other.mtx);
            data_queue = other.data_queue;
        }
        return *this;
    }

    ThreadSafeQueue& operator=(ThreadSafeQueue&& other) {
        if (this != &other) {
            std::scoped_lock lk1(mtx);
            std::scoped_lock lk2(other.mtx);
            data_queue = std::move(other.data_queue);
        }
        return *this;
    }

    void push(T new_value) {
        std::shared_ptr<T> data(std::allocate_shared<T>(allocator, std::move(new_value)));
        std::scoped_lock lk(mtx);
        data_queue.push(data);
        data_cond.notify_one();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock lk(mtx);
        data_cond.wait(lk, [this] { return !data_queue.empty(); });
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value) {
        std::scoped_lock lk(mtx);
        if (data_queue.empty()) {
            return false;
        }
        value = std::move(*data_queue.front());
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::scoped_lock lk(mtx);
        if (data_queue.empty()) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }

    bool empty() const {
        std::scoped_lock lk(mtx);
        return data_queue.empty();
    }
};

int main() {
    ThreadSafeQueue<int> tsQueue;

    const int numProducers = 3;

    std::vector<std::thread> producers;
    for (int i = 0; i < numProducers; ++i) {
        producers.emplace_back([&tsQueue, i]() {
            for (int j = 0; j < 10; ++j) {
                int value = i * 100 + j;
                tsQueue.push(value);
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some work
            }
        });
    }

    std::thread consumer([&tsQueue]() {
        for (int i = 0; i < 30; ++i) { 
            auto value = tsQueue.wait_and_pop();
            if (value) {
                std::cout << "Dequeued: " << *value << std::endl;
            }
        }
    });

    for (auto& producer : producers) {
        producer.join();
    }
    consumer.join();

    return 0;
}