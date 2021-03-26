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

void ReadParametersFromFile(const char*,int&,double&,double&,double&,double&,double&,bool&);

int main()
{
    Print("Begin program");
    Print("For now we will assume that all springs and masses are the same.")
    Print(' ');

    int num_masses {0};
    double length {0};
    double spring_const {0};
    double mass {0};
    double time {0};
    double dt {0};
    bool parallel {false};
    ReadParametersFromFile("params.txt", num_masses, length, spring_const, mass, time, dt, parallel);

    // setup variables
    Print("Setting up variable.");
    std::vector<Vector2D> positions{};  positions. resize(num_masses + 2); // "+ 2" is for fixed endpoints
    std::vector<Vector2D> velocities{}; velocities.resize(num_masses);

    // std::vector<Spring> springs{}; springs.resize(num_masses + 1); // "+ 1" num_masses partitions into num_masses + 1 segments

    // std::vector<double> masses{}; masses.resize(num_masses);

    Spring sp = Spring(spring_const, length);

    // from end point to endpoint length
    double full_length = (double) (num_masses + 1) * length;

    // set endpoints' positions 
    positions[0]              = Vector2D(0.         , 0.);
    positions[num_masses + 1] = Vector2D(full_length, 0.);

    for (int i = 1; i <= num_masses; i++) positions[i] = Vector2D((double) i * length, sin((double) i * 3.14159 / 11));

    Print("Running simulation.");
    double t = 0;
    auto start = std::chrono::system_clock::now();
    while(t < time)
    {
        Update(positions, velocities, sp, mass, dt, parallel);
        t += dt;
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

void ReadParametersFromFile(const char* file_name, int& mass_count, double& spring_length, double& spring_const, double& mass, double& elapsed_time, double& time_step, bool& parallel)
{
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

        if      (input == "number_of_masses")   line >> mass_count;
        else if (input == "equilibrium_length") line >> spring_length;
        else if (input == "spring_constant")    line >> spring_const;
        else if (input == "mass")               line >> mass;
        else if (input == "total_elapsed_time") line >> elapsed_time;
        else if (input == "time_step")          line >> time_step;
        else if (input == "run_parallel")       line >> parallel;
        else continue;
    }
}