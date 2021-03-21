#include <iostream>
#include <thread>
#include <vector>

void print_int(int number)
{
    // Return thread id
    std::cout << number << '\n';
}

int main()
{
    // This program makes a vector of threads, runs print_int()
    // on each of them and then joins them after they are all
    // started. If the join was done in the first loop, it would
    // defeat the purpose of multithreading, because join() waits
    // for the thread to complete before proceeding.
    
    std::cout << "How many threads?\n";
    int number_of_threads;
    std::cin >> number_of_threads;
    std::cout << '\n';

    {
        std::vector<std::thread> threads;

        for (int i=0; i<number_of_threads; i++)
        {
            threads.push_back(std::thread (print_int, i));
        }
        for (int i=0; i<number_of_threads; i++)
        {
            // Without this line, this error happens
            // terminate called without an active exception
            // Aborted (core dumped)
            threads[i].join();
            // This function 
        }
    }

    std::cout << '\n';

    // Threads also has a built in array functionality
    std::thread threads[number_of_threads];
    for (int i=0; i<number_of_threads; i++)
    {
        threads[i] = std::thread(print_int, i);
    }
    for (int i=0; i<number_of_threads; i++)
    {
        threads[i].join();
    }

    return 0;
}
