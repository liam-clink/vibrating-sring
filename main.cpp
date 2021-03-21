#include <iostream>
#include <thread>

void print_int(int number)
{
    // Return thread id
    std::cout << number << '\n';
}

int main()
{
    // do stuff
    for (int i=0; i<10; i++)
    {
        std::thread test_thread(print_int, i);
    }
    

    return 0;
}