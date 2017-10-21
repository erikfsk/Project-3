#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
#include "planet.h"
using namespace std;

class solarsystem
{
public:
    // Properties
    int nr_of_planets;
    planet* system_of_planets;

    // Initializers
    solarsystem(planet* planets_input ,int nr_of_planets_input);

    // Functions
    void solve_verlet(int n, double t_step);
    void Acceleration();
    void Acceleration_reset();
    void verlet_position(double t_step);
    void verlet_velocity(double t_step);
    bool clear_file();
    bool write_to_file();
};

#endif // SOLARSYSTEM_H
