// STL includes
#include <chrono>
#include <math.h>
#include <fstream>
#include <sstream>

// Local defined headers
#include "Dynamics.h"

// Macros
#define PARALLEL 1
#define Print(x) std::cout << x << std::endl;

struct Simulation_Paramters
{
    int num_masses;
    double spring_length;
    double spring_const;
    double mass;
    double elapsed_time;
    double time_step;
    bool parallel;
};

void ReadParametersFromFile(const char*, Simulation_Paramters& params);

int main()
{
    Print("Begin program");
    Print("For now we will assume that all springs and masses are the same.")
    Print(' ');

    Simulation_Paramters params;
    ReadParametersFromFile("params.txt", params);

    // setup variables
    Print("Setting up variable.");
    std::vector<Vector2D> positions{};  positions. resize(params.num_masses + 2); // "+ 2" is for fixed endpoints
    std::vector<Vector2D> velocities{}; velocities.resize(params.num_masses);

    // std::vector<Spring> springs{}; springs.resize(num_masses + 1); // "+ 1" num_masses partitions into num_masses + 1 segments

    // std::vector<double> masses{}; masses.resize(num_masses);

    Spring sp = Spring(params.spring_const, params.spring_length);

    // from end point to endpoint length
    double full_length = (double) (params.num_masses + 1) * params.spring_length;

    // set endpoints' positions 
    positions[0]              = Vector2D(0.         , 0.);
    positions[params.num_masses + 1] = Vector2D(full_length, 0.);

    for (int i = 1; i <= params.num_masses; i++) positions[i] = Vector2D((double) i * params.spring_length, sin((double) i * 3.14159 / 11));

    Print("Running simulation.");
    double t = 0;
    auto start = std::chrono::system_clock::now();
    while(t < params.elapsed_time)
    {
        Update(positions, velocities, sp, params.mass, params.time_step, params.parallel);
        t += params.time_step;
    }
    auto elapsed = std::chrono::system_clock::now() - start;
    Print(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms" << std::endl);
    // for (auto pos : positions) Print(pos); Print('\n');
    // for (auto vel : velocities) Print(vel); Print('\n');

    positions. erase(positions. begin(), positions. end());
    velocities.erase(velocities.begin(), velocities.end());

    return 0;
}

//
// ==========================================================================
//

void ReadParametersFromFile(const char* file_name, Simulation_Paramters& params)
{
    // TODO: Implement variations that read in different numbrs of masses and spring constants
    //       to facilitate, we can offer some templates.
    std::fstream fin(file_name, std::fstream::in); 

    if (!fin.is_open())
    {
        Print("Failed to open parameters file. Terminating program with error code -2.\n");
        exit(-2);
    }

    std::string input;
    while (std::getline(fin, input))
    {
        std::stringstream line(input);
        line >> input;

        if      (input == "number_of_masses")   line >> params.num_masses;
        else if (input == "equilibrium_length") line >> params.spring_length;
        else if (input == "spring_constant")    line >> params.spring_const;
        else if (input == "mass")               line >> params.mass;
        else if (input == "total_elapsed_time") line >> params.elapsed_time;
        else if (input == "time_step")          line >> params.time_step;
        else if (input == "run_parallel")       line >> params.parallel;
        else continue;
    }
}
