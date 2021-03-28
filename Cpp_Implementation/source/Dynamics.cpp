#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

#include "../include/Dynamics.hpp"
#include "../include/Outputs.hpp"

// Set default instance to nullptr
SimulationClass *SimulationClass::_instance = nullptr;

Vector2D SimulationClass::Force(Vector2D& r_mass,
                                Vector2D& r_springLeft,
                                Spring&   sp_left,
                                Vector2D& r_springRight,
                                Spring&   sp_right)
{
    Vector2D r_mass_left  = r_mass - r_springLeft;
    Vector2D r_mass_right = r_mass - r_springRight;

    double len_sp_left  = sqrt(vec_inner(r_mass_left , r_mass_left ));
    double len_sp_right = sqrt(vec_inner(r_mass_right, r_mass_right));

    Vector2D force_left  = r_mass_left *
        (-sp_left. k() * (len_sp_left  - sp_left. L0()) / len_sp_left );
    Vector2D force_right = r_mass_right *
        (-sp_right.k() * (len_sp_right - sp_right.L0()) / len_sp_right);

    return force_left + force_right;
}

//
// ==========================================================================
//

SimulationClass SimulationClass::GetInstance(void)
{
    if (!_instance)
    {
        _instance = new SimulationClass;
    }
    return *_instance;
}

//
// ==========================================================================
//

void SimulationClass::ReadParametersFromFile(const char* file_name)
{
    // TODO: Implement variations that read in different numbrs of masses and spring constants
    //       to facilitate, we can offer some templates.
    std::fstream fin(file_name, std::fstream::in); 

    if (!fin.is_open())
    {
        Print(std::cout, 
              "Failed to open parameters file.",
              "\nTerminating program with error code -2.");
        exit(-2);
    }

    std::string input;
    while (std::getline(fin, input))
    {
        std::stringstream line(input);
        line >> input;

        if      (input == "number_of_masses")   line >> _params.num_masses;
        else if (input == "equilibrium_length") line >> _params.spring_length;
        else if (input == "spring_constant")    line >> _params.spring_const;
        else if (input == "mass")               line >> _params.mass;
        else if (input == "total_elapsed_time") line >> _params.elapsed_time;
        else if (input == "time_step")          line >> _params.time_step;
        else if (input == "run_parallel")       line >> _params.parallel;
        else continue;
    }

    _spring = Spring(_params.spring_const, _params.spring_length);

    // num_mass + 2 positions to accout for fixed endpoints
    positions.resize(_params.num_masses + 2);
    velocities.resize(_params.num_masses);

    // from end point to endpoint length
    double full_length = 
                (double) (_params.num_masses + 1) * _params.spring_length;

    // set endpoints' positions 
    positions[0]                      = Vector2D(0.         , 0.);
    positions[_params.num_masses + 1] = Vector2D(full_length, 0.);
}
//
// ==========================================================================
//

// void SimulationClass::Update(std::vector<Vector2D>& positions,
//             std::vector<Vector2D>& velocities,
//             std::vector<Spring>&   springs,
//             std::vector<double>&   masses,
//             double                 delta_time)
// {
//     int N = (int) positions.size();
//     for (int i = 1; i < N-1; i++) positions[i] = velocities[i] * delta_time;
//     for (int i = 1; i < N-1; i++)
//     {
//         Vector2D t_force = Force(positions[i],
//                                  positions[i-1],
//                                  springs[i-1],
//                                  positions[i+1],
//                                  springs[i]);
//         velocities[i] += t_force * (delta_time / masses[i]);
//     }
// }

//
// ==========================================================================
//

void SimulationClass::RunSimulation(const char* file_name)
{
    ReadParametersFromFile(file_name);

    // Needs to be moved to separate function...
    for (int i = 1; i <= _params.num_masses; i++)
    {
        positions[i] = Vector2D((double) i * _params.spring_length,
                                sin((double) i * 3.14159 / 11));
    }

    double t {0};
    while (t < _params.elapsed_time)
    {
        Update();
        t += _params.time_step;
    }
}

//
// ==========================================================================
//

void SimulationClass::Update(void)
{
    int N = (int) positions.size();
    if (_params.parallel)   
    {
        #pragma omp parallel for
        for (int i = 1; i < N-1; i++) 
        {
            positions[i] += velocities[i-1] * _params.time_step;
        }

        #pragma omp parallel for
        for (int i = 1; i < N-1; i++)
        {
            Vector2D t_force = Force(positions[i],
                                     positions[i-1],
                                     _spring,
                                     positions[i+1],
                                     _spring);
            velocities[i-1] += t_force * (_params.time_step / _params.mass);
        }
    }
    else 
    {
        for (int i = 1; i < N-1; i++) 
        {
            positions[i] += velocities[i-1] * _params.time_step;
        }

        for (int i = 1; i < N-1; i++)
        {
            Vector2D t_force = Force(positions[i],
                                     positions[i-1],
                                     _spring,
                                     positions[i+1],
                                     _spring);
            velocities[i-1] += t_force * (_params.time_step / _params.mass);
        }
    }

}