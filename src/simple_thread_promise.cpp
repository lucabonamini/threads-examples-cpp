#include <random>
#include <vector>
#include <thread>      // std::thread
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>  // std::ref
#include <future>      // std::promise, std::future

const int n = 100000;

int main() {

    std::promise<double> meanProm;
    std::future<double> meanRes = meanProm.get_future();

    std::random_device rnd;
    std::mt19937 mt {rnd()};
    std::uniform_real_distribution<double> dist{0,n};

    // Generate random vector
    std::vector<double> vec(n);
    std::generate(vec.begin(),vec.end(), [&dist,&mt]() {
        return dist(mt);
    });

    // Calc vector' mean in a separate thread
    std::thread thread([&meanProm,&vec] {
        auto sum = std::accumulate(vec.begin(),vec.end(),0.0);
        meanProm.set_value(sum/vec.size());
    });

    thread.join();

    std::cout << "Mean: " << meanRes.get() << std::endl;

    return 0;
}