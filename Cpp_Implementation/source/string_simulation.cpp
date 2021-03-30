// STL includes
#include <chrono>

// Local defined headers
#include "../include/Dynamics.hpp"
#include "../include/Outputs.hpp"


int main()
{
    Print("Begin program");
    Print("For now we will assume that all springs and masses are the same.");

    Print(std::cout, "Setting up simulation.");
    
    // Since it's a singleton we use GetInstance()
    SimulationClass sim = SimulationClass::GetInstance();
    
    Print(std::cout,"Running simulation.");
    {   
        using namespace std::chrono;
        auto start = system_clock::now();
        sim.RunSimulation("params.txt");
        auto elapsed = system_clock::now() - start;
        Print(std::cout, duration_cast<milliseconds>(elapsed).count(), "ms");
    }

    return 0;
}

//
// ==========================================================================
//
