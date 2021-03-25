#include <iostream>
#include <vector>
#include <math.h>
#include <omp.h>
#include <chrono>

#include "Spring.h"
#include "Vector2D.h"

#define Print(x) std::cout << x;

#define PARALLEL 1

Vector2D force(Vector2D&,Vector2D&,Spring&,Vector2D&,Spring&);
void update(std::vector<Vector2D>&,std::vector<Vector2D>&,std::vector<Spring>&,std::vector<double>&,double);
void update(std::vector<Vector2D>&,std::vector<Vector2D>&,Spring&,double,double);

int main()
{
    Print("Begin program\n");
    Print("For now we will assume that all springs and masses are the same.\n")
    Print('\n');

    // Input data from user
    // Will eventually make into a parameter file
    // Print("Enter the number of masses to simulate: ");
    int num_masses = 100000;
    // std::cin >> num_masses;

    // Print("Enter equilibrium length (meters) of spring: ");
    double length = 1.0;
    // std::cin >> length;

    // Print("Enter the spring constant (Newton meters): ")
    double spring_const = 10.0;
    // std::cin >> spring_const;

    // Print("Enter mass (kg): ");
    double mass = 2.0;
    // std::cin >> mass;

    // Print("Enter time of simulaton (sec): ");
    double time = 45.0;
    // std::cin >> time;

    // Print("Enter time step for simulation (sec): ")
    double dt = 0.001;
    // std::cin >> dt;

    // setup variables
    Print("Setting up variable.\n");
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

    Print("Running simulation.\n");
    double t = 0;
    auto start = std::chrono::system_clock::now();
    while(t < time)
    {
        update(positions, velocities, sp, mass, dt);
        t += dt;
    }
    auto elapsed = std::chrono::system_clock::now() - start;
    Print(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << std::endl);
    // for (auto pos : positions) Print(pos); Print('\n');
    // for (auto vel : velocities) Print(vel); Print('\n');

    positions. erase(positions. begin(), positions. end());
    velocities.erase(velocities.begin(), velocities.end());

    return 0;
}

//
// ==========================================================================
//
Vector2D force(Vector2D& r_mass, Vector2D& r_springLeft, Spring& sp_left, Vector2D& r_springRight, Spring& sp_right)
{
    Vector2D r_mass_left  = r_mass - r_springLeft;
    Vector2D r_mass_right = r_mass - r_springRight;

    double len_sp_left  = sqrt(vec_inner(r_mass_left , r_mass_left ));
    double len_sp_right = sqrt(vec_inner(r_mass_right, r_mass_right));

    Vector2D force_left  = r_mass_left  * (-sp_left. k() * (len_sp_left  - sp_left. L0()) / len_sp_left );
    Vector2D force_right = r_mass_right * (-sp_right.k() * (len_sp_right - sp_right.L0()) / len_sp_right);

    return force_left + force_right;
}

//
// ==========================================================================
//

void update(std::vector<Vector2D>& positions, std::vector<Vector2D>& velocities, std::vector<Spring>& springs, std::vector<double>& masses, double delta_time)
{
    // Print("Inside update\n");
    int N = (int) positions.size();
    for (int i = 1; i < N-1; i++) positions[i] = velocities[i] * delta_time;
    for (int i = 1; i < N-1; i++)
    {
        Vector2D t_force = force(positions[i], positions[i-1], springs[i-1], positions[i+1], springs[i]);
        // Print(t_force);
        velocities[i] += t_force * (delta_time / masses[i]);
    }
}

//
// ==========================================================================
//

void update(std::vector<Vector2D>& positions, std::vector<Vector2D>& velocities, Spring& springs, double masses, double delta_time)
{
    int N = (int) positions.size();
 #if PARALLEL   
    // #pragma omp parallel
    #pragma omp parallel for
#endif
    for (int i = 1; i < N-1; i++) 
    {
        positions[i] += velocities[i-1] * delta_time;
    }

#if PARALLEL
    // #pragma omp parallel
    #pragma omp parallel for
#endif
    for (int i = 1; i < N-1; i++)
    {
        Vector2D t_force = force(positions[i], positions[i-1], springs, positions[i+1], springs);
        velocities[i-1] += t_force * (delta_time / masses);
    }

}