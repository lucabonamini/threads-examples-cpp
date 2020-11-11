#include <vector>
#include <thread>
#include <algorithm>
#include <numeric>
#include <iostream>

int main() {

    int mean = 0;

    // Generate random vector
    std::vector<double> vec(10000);
    std::generate(vec.begin(),vec.end(), []() {
        return rand()%100;
    });

    // Calc vector' mean in a separate thread
    std::thread thread([&mean,&vec] {
        for (size_t i=0; i<vec.size(); i++) {
            auto sum = std::accumulate(vec.begin(),vec.end(),0.0);
            mean = sum/vec.size();
        }
    });

    std::cout << "Waiting for thread execution...." << std::endl;

    thread.join();

    std::cout << "Mean: " << mean << std::endl;

    return 0;
}