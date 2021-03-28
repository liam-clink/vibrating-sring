// STL includes
#include <chrono>

// Local defined headers
#include "../include/Dynamics.hpp"
#include "../include/Outputs.hpp"


int main()
{
    std::cout << "Begin program\n";
    std::cout << "For now we will assume that all springs and masses are the same.\n";
    std::cout << '\n';

    Print(std::cout, "Setting up simulation.");
    SimulationClass sim = SimulationClass::GetInstance();
    
    Print(std::cout,"Running simulation.");
    sim.RunSimulation("params.txt");

    return 0;
}

//
// ==========================================================================
//
