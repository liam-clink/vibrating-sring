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

class SimulationClass
{
public:
    Vector2D               Force(Vector2D& r_mass,
                                 Vector2D& r_left_mass,
                                 Spring&   r_left_spring,
                                 Vector2D& r_right_mass,
                                 Spring&   r_right_spring);                
    static SimulationClass GetInstance(void);
    void                   ReadParametersFromFile(const char* file_name);
    void                   RunSimulation (const char* file_name);
    void                   Update(void); 

    
    std::vector<Vector2D>  positions;
    std::vector<Vector2D>  velocities;

private:
    SimulationClass(void) = default;

    static SimulationClass *_instance;
    Simulation_Parameters  _params;
    Spring                 _spring;
};

