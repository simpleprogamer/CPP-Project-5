
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <syncstream>
#include <future>
void compute(const std::string& name, int sec)
{
    std::this_thread::sleep_for(std::chrono::seconds(sec));
    std::osyncstream(std::cout) << name << std::endl;
}
void slow(const std::string& name) { compute(name, 7); }
void quick(const std::string& name) { compute(name, 1); }

void work ()
{
    auto start = std::chrono::steady_clock::now();
    auto t1 = std::async(std::launch::async, [] {slow("B2");});
    auto t2 = std::async(std::launch::async, [] { quick("A1"); quick("A3"); quick("A4"); });
    slow("A2");
    t2.get();
    quick("B1");
    t1.get();
    quick("C");
    double sec = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
    std::osyncstream(std::cout) << "Time:" << sec << "s" << std::endl;
    std::osyncstream(std::cout) << "Work is done!" << std::endl;

}
int main()
{
    work();
}
