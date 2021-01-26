#include <random>
#include <vector>
#include <thread>      // std::thread
#include <algorithm>
#include <numeric>
#include <iostream>

const int n = 100000;

int main() {

    double mean = 0;
    std::random_device rnd;
    std::mt19937 mt {rnd()};
    std::uniform_real_distribution<double> dist{0,n};

    // Generate random vector
    std::vector<double> vec(n);
    std::generate(vec.begin(),vec.end(), [&dist,&mt]() {
        return dist(mt);
    });

    // Calc vector mean in a separate thread
    std::thread thread([&mean,&vec] {
        auto sum = std::accumulate(vec.begin(),vec.end(),0.0);
        mean = sum/vec.size();
    });

    std::cout << "Waiting for thread execution...." << std::endl;

    thread.join();

    std::cout << "Mean: " << mean << std::endl;

    return 0;
}