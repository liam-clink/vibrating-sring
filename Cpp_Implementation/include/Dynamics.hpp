#pragma once
#include <omp.h>
#include <vector>

#include "Vector2D.hpp"
#include "Spring.hpp"

struct Simulation_Parameters
{
    int num_masses;
    double spring_length;
    double spring_const;
    double mass;
    double elapsed_time;
    double time_step;
    bool parallel;
};

// This is a singleton class
class SimulationClass
{
public:
    static SimulationClass GetInstance(void);

    Vector2D Force(const Vector2D& r_mass,
                   const Vector2D& r_left_mass,
                   const Spring&   r_left_spring,
                   const Vector2D& r_right_mass,
                   const Spring&   r_right_spring);                

    void ReadParametersFromFile(const char* file_name);
    void RunSimulation (const char* file_name);
    void Update(void); 

    
    std::vector<Vector2D>  positions;
    std::vector<Vector2D>  velocities;

private:
    // The constructor is private because this is a singleton
    SimulationClass(void) = default;

    // static means there's only one copy of _instance
    static SimulationClass* _instance;
    Simulation_Parameters  _params;
    Spring                 _spring;
};

