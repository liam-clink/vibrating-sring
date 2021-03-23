#include <iostream>
#include <thread>
#include <vector>

void call_thread(std::thread& this_thread, void (*func)(int), int val)
{
    this_thread = std::thread(func, val);
}

void func_call(int val)
{
    std::cout << "Printing for process " << val << "\n";
}

int main()
{
    std::thread temp_thread;
    for (int i = 0; i < 10; i++)
    {
        call_thread(temp_thread, func_call, i);
        temp_thread.join();
    }
    
    return 0;
}
