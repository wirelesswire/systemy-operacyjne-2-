#include <iostream>
#include <mutex>
#include <string_view>
#include <syncstream>
#include <thread>
 
volatile long int g_i = 0;
std::mutex g_i_mutex;  // protects g_i
 
void safe_increment(int iterations)
{
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    while (iterations-- > 0)
        g_i = g_i + 1;
    std::cout << "thread #" << std::this_thread::get_id() << ", g_i: " << g_i << '\n';
 
    // g_i_mutex is automatically released when lock goes out of scope
}
 
void unsafe_increment(int iterations)
{
    while (iterations-- > 0)
        g_i = g_i + 1;
    std::cout << "thread #" << std::this_thread::get_id()
              << ", g_i: " << g_i << '\n';
}

std::mutex mtx ;
void wait1s(int i){
    std::lock_guard<std::mutex> lock(mtx);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "wait one s " << i << '\n';

}
void justprint (int i){
    std::lock_guard<std::mutex> lock(mtx);
    
    std::cout << i << '\n'; 
} 

 
int main()
{
    auto test = [](std::string_view fun_name, auto fun)
    {
        g_i = 0;
        // std::cout << fun_name << ":\nbefore, g_i: " << g_i << '\n';
        {
            std::thread t1(wait1s, 1);
            std::thread t2(justprint, 1);
            
            t1.join();
            t2.join();
        }
        // std::cout << "after, g_i: " << g_i << "\n\n";
    };
    test("test1", wait1s);
    // test("test2", justprint);


    // auto test = [](std::string_view fun_name, auto fun)
    // {
    //     g_i = 0;
    //     std::cout << fun_name << ":\nbefore, g_i: " << g_i << '\n';
    //     {
    //         std::thread t1(fun, 1'000'000'000);
    //         std::thread t2(fun, 1'000'000'000);
    //         std::thread t3(fun, 1'000'000'000);
    //         std::thread t4(fun, 1'000'000'000);

    //         t1.join();
    //         t2.join();
        
    //         t3.join();
    //         t4.join();
    //     }
    //     std::cout << "after, g_i: " << g_i << "\n\n";
    // };
    // test("safe_increment", safe_increment);
    // test("unsafe_increment", unsafe_increment);
}