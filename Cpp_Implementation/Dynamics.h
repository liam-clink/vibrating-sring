#pragma once
#include <omp.h>
#include <vector>

#include "Vector2D.h"
#include "Spring.h"

Vector2D Force(Vector2D& r_mass,
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

void Update(std::vector<Vector2D>& positions,
            std::vector<Vector2D>& velocities,
            std::vector<Spring>&   springs,
            std::vector<double>&   masses,
            double                 delta_time)
{
    int N = (int) positions.size();
    for (int i = 1; i < N-1; i++) positions[i] = velocities[i] * delta_time;
    for (int i = 1; i < N-1; i++)
    {
        Vector2D t_force = Force(positions[i],
                                 positions[i-1],
                                 springs[i-1],
                                 positions[i+1],
                                 springs[i]);
        velocities[i] += t_force * (delta_time / masses[i]);
    }
}

//
// ==========================================================================
//

void Update(std::vector<Vector2D>& positions,
            std::vector<Vector2D>& velocities,
            Spring&                springs,
            double                 masses,
            double                 delta_time,
            bool                   parallel)
{
    int N = (int) positions.size();
    if (parallel)   
    {
        #pragma omp parallel for
        for (int i = 1; i < N-1; i++) 
        {
            positions[i] += velocities[i-1] * delta_time;
        }

        #pragma omp parallel for
        for (int i = 1; i < N-1; i++)
        {
            Vector2D t_force = Force(positions[i],
                                     positions[i-1],
                                     springs,
                                     positions[i+1],
                                     springs);
            velocities[i-1] += t_force * (delta_time / masses);
        }
    }
    else 
    {
        for (int i = 1; i < N-1; i++) 
        {
            positions[i] += velocities[i-1] * delta_time;
        }

        for (int i = 1; i < N-1; i++)
        {
            Vector2D t_force = Force(positions[i],
                                     positions[i-1],
                                     springs,
                                     positions[i+1],
                                     springs);
            velocities[i-1] += t_force * (delta_time / masses);
        }
    }

}